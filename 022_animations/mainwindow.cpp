#include <QDebug>
#include <QPropertyAnimation>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(600, 600);
    adjustSize();

    setupScene();

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
        "sq_pexels-mehmet-turgut-kirkgoz-16596877.jpg",
        "sq_pexels-roman-odintsov-12715260.jpg",
        "sq_pexels-sami-aksu-11325507.jpg",
        "sq_pexels-yana-kangal-17579752.jpg",
    };

    pictures.clear();
    for (auto &image : images) {
        QPixmap pixmap(":/images/" + image);
        pixmap = pixmap.scaled(200, 200);
        QGraphicsPixmapItem *picture = new QGraphicsPixmapItem(pixmap);

        //picture->setScale(0.5);
        scene->addItem(picture);
        //picture->setOffset(-2500, -2500);
        pictures.push_back(picture);
    }
}

void  MainWindow::setPositionAnimated(QGraphicsItem *item, double x, double y)
{
    //auto a1 = new QPropertyAnimation(item, "x", this);
}


void MainWindow::animate()
{
    qInfo()<< "animate";
    int cols = 2;
    int rows = std::ceil((double) pictures.size() / cols);
    int w = 220;
    int h = 220;
    int gap = 24;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            int offset = y * cols + x;
            if (offset < pictures.size()) {
                auto picture = pictures[offset];
                //setPositionAnimated(picture, x + w, y + h);
                picture->setPos(x * w, y * h);
            }
        }
    }
}
