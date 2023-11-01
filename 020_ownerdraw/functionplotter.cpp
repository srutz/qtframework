#include <cmath>
#include "functionplotter.h"

FunctionPlotter::FunctionPlotter(QWidget *parent)
    : QWidget{parent}
{

}



void FunctionPlotter::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    plotAxes(&painter);
    plotFunction(&painter);
}


void FunctionPlotter::plotAxes(QPainter* painter)
{
    const int w = width();
    const int h = height();

    // Achsen
    painter->drawLine(0, h/2, w, h/2);
    painter->drawLine(w/2, 0, w/2, h);

    // Skalenbeschriftung
    for (int i = w/2 % int(scaleFactor); i < w; i += scaleFactor) {
        painter->drawLine(i, h/2 - 5, i, h/2 + 5);
        painter->drawText(i, h/2 + 20, QString::number((i - w/2) / scaleFactor));
    }

    for (int i = h/2 % int(scaleFactor); i < h; i += scaleFactor) {
        painter->drawLine(w/2 - 5, i, w/2 + 5, i);
        painter->drawText(w/2 + 10, i, QString::number((h/2 - i) / scaleFactor));
    }
}

void FunctionPlotter::plotFunction(QPainter* painter)
{
    const int w = width();
    const int h = height();

    // Beispiel: f(x) = sin(x)
    QPainterPath path;
    bool start = true;

    for (int i = 0; i < w; ++i) {
        double x = (i - w / 2) / scaleFactor;
        double y = formula(x) * scaleFactor;
        if (start) {
            path.moveTo(i, h/2 - y);
            start = false;
        } else {
            path.lineTo(i, h/2 - y);
        }
    }

    painter->drawPath(path);
}

double FunctionPlotter::formula(double x)
{
    return 8 * std::sin(x);
}
