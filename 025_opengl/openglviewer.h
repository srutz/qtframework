#ifndef OPENGLVIEWER_H
#define OPENGLVIEWER_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QMatrix4x4>
#include <QTimer>

class OpenGlViewer : public QOpenGLWidget
{
    Q_OBJECT
    Q_PROPERTY(double step1 READ step1 WRITE setStep1)
    Q_PROPERTY(double step2 READ step2 WRITE setStep2)
public:
    explicit OpenGlViewer(QWidget* parent = nullptr);
    ~OpenGlViewer();
    void resizeGL(int w, int h);
    void initializeGL();
    void paintGL();
    void advance();

    double step1() const;
    void setStep1(double);

    double step2() const;
    void setStep2(double);

public slots:
    void animate1();
    void animate2();

private:
    //QMatrix4x4 projection;
    double t0 = 0;
    double angle1 = 0;
    double angle2 = 0;
    double angle3 = 0;
    QTimer *timer = nullptr;

    double m_step1;
    double m_step2;
};

#endif // OPENGLVIEWER_H
