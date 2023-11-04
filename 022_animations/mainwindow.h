#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGraphicsPixmapItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setupScene();
    void animate1();
    void animate2();
    void toggleMaximized();

private:
    Ui::MainWindow *ui;
    QVector<QGraphicsPixmapItem*> pictures;

    void  setPositionAnimated(QGraphicsItem *item, double x, double y);
    void  setScaleAnimated(QGraphicsItem *item, double scale);
    void  setRotationAnimated(QGraphicsItem *item, double angle);

};
#endif // MAINWINDOW_H
