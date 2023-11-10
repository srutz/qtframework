#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    float f1 = 1E8;
    float f2 = f1 + 1;

    qInfo () << f1;
    qInfo () << f2;
    qInfo () << (f1 == f2);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
