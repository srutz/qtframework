#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    //QApplication::setStyle(QStyleFactory::create("Universal"));
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    //QApplication::setStyle(QStyleFactory::create("Universal"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("db1");
    db.setUserName("sr");
    db.setPassword("abc");
    bool ok = db.open();
    qInfo() << "database connection status " << ok;

    MainWindow w;
    w.show();
    return a.exec();
}
