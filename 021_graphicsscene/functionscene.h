#ifndef FUNCTIONSCENE_H
#define FUNCTIONSCENE_H

#include <QWidget>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <cmath>

class FunctionScene : public QGraphicsView
{
    Q_OBJECT

public:
    FunctionScene(QWidget* parent = nullptr);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QGraphicsScene* scene;
    const double scaleFactor = 25;

    void rebuild();
    void plotAxes();
    void plotFunction();
    double formula(double x);
};



#endif // FUNCTIONSCENE_H
