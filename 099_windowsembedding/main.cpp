#include "winmain.h"
#include "mainwindow.h"
#include "guiowner.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    GuiOwner guiOwner;
    guiOwner.launch();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
