#include <QResizeEvent>
#include "functionscene.h"

FunctionScene::FunctionScene(QWidget *parent) : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    rebuild();
}

void FunctionScene::rebuild()
{
    scene->clear();
    plotAxes();
    plotFunction();
}

void FunctionScene::plotAxes()
{
    double w = 1000;
    double h = 1000;
    qInfo() << w << "," << h;

    scene->addLine(-w, 0, w, 0);
    scene->addLine(0, -h, 0, h);

    for (int i = -w / scaleFactor; i < w / scaleFactor; i += 2) {
        scene->addLine(i*scaleFactor, -5, i*scaleFactor, 5);
        if (i != 0)
            scene->addText(QString::number(i))->setPos(i*scaleFactor, 0);
    }
    for (int i = -h / scaleFactor; i < h / scaleFactor; i += 2) {
        scene->addLine(-5, i*scaleFactor, 5, i*scaleFactor);
        if (i != 0)
            scene->addText(QString::number(-i))->setPos(0, i*scaleFactor);
    }
}

double FunctionScene::formula(double x)
{
    return 8 * std::sin(x);
}

void FunctionScene::plotFunction()
{
    double step = 0.1;
    double w = 1000;
    for (double x = -w / scaleFactor; x < w / scaleFactor; x += step) {
        double y1 = formula(x) * scaleFactor;
        double y2 = formula(x + step) * scaleFactor;
        scene->addLine(x*scaleFactor, -y1, (x + step) * scaleFactor, -y2);
    }
}


void FunctionScene::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event); // base class handler
    auto parent = this->parentWidget();
    double scale = std::min(parent->width(), parent->height()) / 1000.0;

    qInfo() << "resize" << event->size() << ", scale=" << scale;

    this->setTransform(QTransform::fromScale(scale, scale));

}
