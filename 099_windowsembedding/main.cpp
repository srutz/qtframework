#include "winmain.h"
#include "mainwindow.h"
#include "guiowner.h"
#include "embeddedwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    GuiOwner guiOwner;
    guiOwner.launch();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qInfo () << "running on main window: " << mainWindow;
    auto embeddedWidget = new EmbeddedWidget(mainWindow, true);
    embeddedWidget->setStyleSheet("background-color: oraange;");
    embeddedWidget->resize(200, 200);


    return a.exec();
}
