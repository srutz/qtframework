#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTextStream>
#include <QString>
#include <QTimer>
#include <QRegularExpression>

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
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //ui->graphicsView->setFixedSize(600, 600);
    //adjustSize();
    //setupScene();

    QObject::connect(scene, &QGraphicsScene::selectionChanged, scene, [=] () {
        auto selectedItems = scene->selectedItems();
        QString s;
        QTextStream ts(&s);
        int i = 0;
        for (auto item : selectedItems) {
            if (i > 0) {
                ts << ", ";
            }
            ts << item->data(0).toString();
            i++;
        }
        ui->statusbar->showMessage(s, 4500);
    });

    QTimer::singleShot(100, this, [=]() {
        scene->setSceneRect(QRectF(0, 0, view->viewport()->rect().width(), view->viewport()->rect().height()));
        setupScene();
    });

    QObject::connect(ui->actionReset, &QAction::triggered, this, &MainWindow::setupScene);
    QObject::connect(ui->actionAnimate1, &QAction::triggered, this, &MainWindow::animate1);
    QObject::connect(ui->actionAnimate2, &QAction::triggered, this, &MainWindow::animate2);
    QObject::connect(ui->actionScale, &QAction::triggered, this, &MainWindow::toggleMaximized);
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
        "sq_pexels-vedran-miletic-2313396.jpg",
        "sq_pexels-yana-kangal-17579752.jpg",
    };

    static auto re1 = QRegularExpression("^sq_pexels-");

    pictures.clear();
    for (auto &image : images) {
        QPixmap pixmap(":/images/" + image);
        pixmap = pixmap.scaled(200, 200);
        QGraphicsPixmapItem *picture = new QGraphicsPixmapItem(pixmap);
        picture->setFlag(QGraphicsItem::ItemIsSelectable, true);
        picture->setPos(0, 0);
        QString shortname = image;
        shortname.replace(re1, "");
        picture->setData(0, QVariant(shortname));
        scene->addItem(picture);
        pictures.push_back(picture);
    }
}

void  MainWindow::setPositionAnimated(QGraphicsItem *item, double x, double y)
{
    auto animatedItem = new AnimatedGraphicsItem();
    animatedItem->setItem(item);
    auto animation = new QPropertyAnimation(animatedItem, "pos", this);
    animation->setDuration(400);
    animation->setStartValue(item->pos());
    animation->setEndValue(QPointF(x, y));
    animation->setEasingCurve(QEasingCurve::InOutElastic);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
    QObject::connect(animation, &QPropertyAnimation::finished, this, [=] {
       delete animation;
       delete animatedItem;
    });
}

void  MainWindow::setScaleAnimated(QGraphicsItem *item, double scale)
{
    auto animatedItem = new AnimatedGraphicsItem();
    animatedItem->setItem(item);
    auto animation = new QPropertyAnimation(animatedItem, "scale", this);
    animation->setDuration(400);
    animation->setStartValue(item->scale());
    animation->setEndValue(scale);
    animation->setEasingCurve(QEasingCurve::InOutElastic);
    animation->start();
    QObject::connect(animation, &QPropertyAnimation::finished, this, [=] {
       delete animation;
       delete animatedItem;
    });
}

void  MainWindow::setRotationAnimated(QGraphicsItem *item, double rotation)
{
    auto animatedItem = new AnimatedGraphicsItem();
    animatedItem->setItem(item);
    auto animation = new QPropertyAnimation(animatedItem, "rotation", this);
    animation->setDuration(400);
    animation->setStartValue(item->rotation());
    animation->setEndValue(rotation);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
    QObject::connect(animation, &QPropertyAnimation::finished, this, [=] {
       delete animation;
       delete animatedItem;
    });
}


void MainWindow::animate1()
{
    qInfo()<< "animate1";
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
                picture->setZValue(index);
                setPositionAnimated(picture, x * w, y * h);
            }
        }
    }
}

void MainWindow::animate2()
{
    qInfo()<< "animate2";
    auto f = pictures[0];
    pictures.pop_front();
    pictures.push_back(f);

    for (int i = 0; i < pictures.size(); i++) {
        auto picture = pictures[i];
        //picture->setPos(x * w, y * h);
        picture->setZValue(i);
        setPositionAnimated(picture, 10 + i * 40, 10 + i * 40);
    }
}


void MainWindow::toggleMaximized()
{
    //auto items= ui->graphicsView->scene()->selectedItems();
    auto items = this->pictures;
    int i = 0;
    for (auto item : items) {
        QTimer::singleShot(10 + 75 * (i / 3), Qt::TimerType::CoarseTimer, this, [=] {
            setRotationAnimated(item, item->rotation() + 450);
        });
        i++;
    }

}
