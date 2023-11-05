#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QwtDial>
#include <QwtSlider>
#include <QwtKnob>
#include <QwtPlot>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum EntryId {
    ID_KNOB = 100, ID_SLIDER = 101, ID_DIAL = 102, ID_PLOT = 103
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showEntry(EntryId);


private:
    Ui::MainWindow *ui;

    QWidget* makeDial();
    QWidget* makeSlider();
    QWidget* makeKnob();
    QWidget* makePlot();

    void showWidget(QWidget*);
};
#endif // MAINWINDOW_H
