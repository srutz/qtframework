#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QBarSeries>
#include "electionresult.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QMap<QString,ElectionResult> *electionMap;

    Ui::MainWindow *ui;
    QChart *chart;

    QBarSeries* fillChart(const QString &area);
};
#endif // MAINWINDOW_H
