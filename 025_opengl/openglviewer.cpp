#include "openglviewer.h"
#include <QDebug>
#include <QTimer>
#include <QOpenGLFunctions>
#include <QPropertyAnimation>
#include <sys/time.h>

static double secondsSinceEpoch()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + tv.tv_usec / 1E6;
}


/* taken from glu.h and modified */


static void makeIdentity(GLfloat m[16])
{
    m[0+4*0] = 1; m[0+4*1] = 0; m[0+4*2] = 0; m[0+4*3] = 0;
    m[1+4*0] = 0; m[1+4*1] = 1; m[1+4*2] = 0; m[1+4*3] = 0;
    m[2+4*0] = 0; m[2+4*1] = 0; m[2+4*2] = 1; m[2+4*3] = 0;
    m[3+4*0] = 0; m[3+4*1] = 0; m[3+4*2] = 0; m[3+4*3] = 1;
}


static void normalize(GLfloat v[3])
{
    GLfloat r;
    r = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    if (r == 0.0) return;
    v[0] /= r;
    v[1] /= r;
    v[2] /= r;
}

static void cross(GLfloat v1[3], GLfloat v2[3], GLfloat result[3])
{
    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = v1[2]*v2[0] - v1[0]*v2[2];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];
}


static void perspective(GLfloat fov, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar) {
    const float PI = 3.14159265f;
    const float halfH = tan(fov / 180 * PI) * zNear;
    const float halfW = halfH * aspectRatio;
    glFrustum( -halfW, halfW, -halfH, halfH, zNear, zFar );
}

static void lookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez,
                   GLfloat centerx, GLfloat centery, GLfloat centerz,
                   GLfloat upx, GLfloat upy, GLfloat upz)
{
    float forward[3], side[3], up[3];
    GLfloat m[4][4];

    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;

    up[0] = upx;
    up[1] = upy;
    up[2] = upz;

    normalize(forward);

    /* Side = forward x up */
    cross(forward, up, side);
    normalize(side);

    /* Recompute up as: up = side x forward */
    cross(side, forward, up);

    makeIdentity(&m[0][0]);
    m[0][0] = side[0];
    m[1][0] = side[1];
    m[2][0] = side[2];

    m[0][1] = up[0];
    m[1][1] = up[1];
    m[2][1] = up[2];

    m[0][2] = -forward[0];
    m[1][2] = -forward[1];
    m[2][2] = -forward[2];

    glMultMatrixf(&m[0][0]);
    glTranslated(-eyex, -eyey, -eyez);
}

/* taken from glut.c */
static void doughnut(GLfloat r, GLfloat R, GLint nsides, GLint rings)
{
    int i, j;
    GLfloat theta, phi, theta1;
    GLfloat cosTheta, sinTheta;
    GLfloat cosTheta1, sinTheta1;
    GLfloat ringDelta, sideDelta;

    ringDelta = 2.0 * M_PI / rings;
    sideDelta = 2.0 * M_PI / nsides;

    theta = 0.0;
    cosTheta = 1.0;
    sinTheta = 0.0;
    for (i = rings - 1; i >= 0; i--) {
        theta1 = theta + ringDelta;
        cosTheta1 = cos(theta1);
        sinTheta1 = sin(theta1);
        glBegin(GL_QUAD_STRIP);
        phi = 0.0;
        for (j = nsides; j >= 0; j--) {
            GLfloat cosPhi, sinPhi, dist;

            phi += sideDelta;
            cosPhi = cos(phi);
            sinPhi = sin(phi);
            dist = R + r * cosPhi;

            glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
            glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, r * sinPhi);
            glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
            glVertex3f(cosTheta * dist, -sinTheta * dist,  r * sinPhi);
        }
        glEnd();
        theta = theta1;
        cosTheta = cosTheta1;
        sinTheta = sinTheta1;
    }
}



OpenGlViewer::OpenGlViewer(QWidget* parent)
    :QOpenGLWidget(parent)
{
    m_step1 = m_step2 = 0;

}

OpenGlViewer::~OpenGlViewer()
{
    if (timer) {
        delete timer;
    }
}

void OpenGlViewer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45, (float)w/h, 0.01, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    lookAt(0, 0, 9, 0, 0, 0, 0, 1, 0);

    if (!this->timer)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&OpenGlViewer::advance));
        timer->start(10);
    }
}


void OpenGlViewer::initializeGL()
{
    qInfo() << "initializeGL";
    //QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    //f->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
    GLfloat light_specular[] = { 1.0, 0.5, 0.5, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OpenGlViewer::paintGL()
{
    //qInfo() << "paintGL";
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0, -8 * m_step2, 0);
    glRotatef(angle1, 1, 0, 0);
    glRotatef(angle2, 0, 1, 0);
    glRotatef(angle3, 0, 0, 1);
    double f = 1.5;
    doughnut(0.25 + 1.5 * f * m_step1, 2 + 1.9 * f * m_step1, 24, 48);
    glPopMatrix();
}

void OpenGlViewer::advance() {
    if (t0 == 0)
    {
        t0 = secondsSinceEpoch();
        return;
    }
    double t1 = secondsSinceEpoch();
    double dt = t1 - t0;
    //qDebug() << "render: " << t0 << " " << t1 << " " << dt;
    t0 = t1;
    //qDebug() << "render: " << dt;
    angle1 += 79 * dt;
    angle2 += 49 * dt;
    angle3 += 91 * dt;
    update();
}


double OpenGlViewer::step1() const
{
    return m_step1;
}

void OpenGlViewer::setStep1(double step1)
{
    this->m_step1 = step1;
}

double OpenGlViewer::step2() const
{
    return m_step2;
}

void OpenGlViewer::setStep2(double step2)
{
    this->m_step2 = step2;
}

void OpenGlViewer::animate1(){
    auto animation = new QPropertyAnimation(this, "step1", this);
    animation->setDuration(1000);
    animation->setStartValue(m_step1);
    animation->setEndValue(1 - m_step1);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setEasingCurve(QEasingCurve::InOutElastic);
    animation->start();
    QObject::connect(animation, &QPropertyAnimation::finished, this, [=] {
        delete animation;
    });
}

void OpenGlViewer::animate2(){
    auto animation = new QPropertyAnimation(this, "step2", this);
    animation->setDuration(1000);
    animation->setStartValue(m_step2);
    animation->setEndValue(1 - m_step2);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
    QObject::connect(animation, &QPropertyAnimation::finished, this, [=] {
        delete animation;
    });
}
