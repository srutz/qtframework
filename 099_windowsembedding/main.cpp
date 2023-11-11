#include "winmain.h"
#include "mainwindow.h"
#include "guiowner.h"
#include "guiworker.h"
#include "winmain.h"
#include "applicationstatus.h"


#include <QApplication>
#include <QDebug>
#include <windows.h>


int main(int argc, char *argv[])
{
#ifndef Q_OS_WIN
    qDebug() << "this application required windows, exiting.";
    return 1;
#endif

    ApplicationStatus::initialize();

    //GuiOwner guiOwner;
    //guiOwner.launch();



    QApplication a(argc, argv);
    MainWindow w;
    launchWindows();
    w.show();

    return a.exec();
}



