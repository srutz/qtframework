#include <QtWebView/QtWebView>
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QtWebView::initialize();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
