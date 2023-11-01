#ifndef FUNCTIONPLOTTER_H
#define FUNCTIONPLOTTER_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class FunctionPlotter : public QWidget
{
    Q_OBJECT
public:
    explicit FunctionPlotter(QWidget *parent = nullptr);

signals:


protected:
    void paintEvent(QPaintEvent* event) override;

private:
    const double scaleFactor = 20.0;  // Zum Zoomen und zur Skalenanpassung

    void plotAxes(QPainter* painter);
    void plotFunction(QPainter* painter);

    double formula(double x);

};

#endif // FUNCTIONPLOTTER_H
