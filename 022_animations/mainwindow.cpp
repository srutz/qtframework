#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animatedgraphicsitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto scene = new QGraphicsScene(ui->graphicsView);
    auto view = this->ui->graphicsView;
    view->setScene(scene);
    //ui->graphicsView->setFixedSize(600, 600);
    //adjustSize();
    //setupScene();

    QTimer::singleShot(100, this, [=]() {
        scene->setSceneRect(QRectF(0, 0, view->viewport()->rect().width(), view->viewport()->rect().height()));
        setupScene();
    });

    QObject::connect(ui->actionReset, &QAction::triggered, this, &MainWindow::setupScene);
    QObject::connect(ui->actionAnimate, &QAction::triggered, this, &MainWindow::animate);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupScene()
{
    qInfo()<< "setupScene";
    auto view = this->ui->graphicsView;
    auto scene = view->scene();
    scene->clear();

    QVector<QString> images = {
        "sq_pexels-george-desipris-792381.jpg",
        "sq_pexels-george-lebada-567540.jpg",
        "sq_pexels-mehmet-turgut-kirkgoz-16596877.jpg",
        "sq_pexels-pixabay-259554.jpg",
        "sq_pexels-rajesh-balouria-1322599.jpg",
        "sq_pexels-roman-odintsov-12715260.jpg",
        "sq_pexels-sami-aksu-11325507.jpg",
        "sq_pexels-vedran-miletić-2313396.jpg",
        "sq_pexels-yana-kangal-17579752.jpg",

    };

    pictures.clear();
    for (auto &image : images) {
        QPixmap pixmap(":/images/" + image);
        pixmap = pixmap.scaled(200, 200);
        QGraphicsPixmapItem *picture = new QGraphicsPixmapItem(pixmap);
        picture->setPos(0, 0);
        scene->addItem(picture);
        pictures.push_back(picture);
    }
}

void  MainWindow::setPositionAnimated(QGraphicsItem *item, double x, double y)
{
    //qInfo() << "pos animation " << item << x << y;
    auto animatedItem = new AnimatedGraphicsItem();
    animatedItem->setItem(item);
    auto animation = new QPropertyAnimation(animatedItem, "pos", this);
    animation->setDuration(400);
    animation->setEndValue(QPointF(x, y));
    animation->setEasingCurve(QEasingCurve::InOutElastic);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
}


void MainWindow::animate()
{
    qInfo()<< "animate";
    int cols = 3;
    int rows = std::ceil((double) pictures.size() / cols);
    int w = 220;
    int h = 220;

    auto f = pictures[0];
    pictures.pop_front();
    pictures.push_back(f);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            int index = y * cols + x;
            if (index < pictures.size()) {
                auto picture = pictures[index];
                //picture->setPos(x * w, y * h);
                setPositionAnimated(picture, x * w, y * h);
            }
        }
    }
}
