#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "winmain.h"
#include "embeddedwidget.h"
#include "applicationstatus.h"

#include <QWindow>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
        QWindow *window = windowHandle();
        window->setFlags(Qt::FramelessWindowHint);
        SetWindowTextW(mainWindow, L"set from qt");
        LONG style = GetWindowLong((HWND)winId(), GWL_STYLE);
        style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU | WS_CHILD);
        //style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
        //style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
        qInfo() << style;
        SetWindowLong((HWND)winId(), GWL_STYLE, style);
        SetParent((HWND) this->winId(), mainWindow);
        MoveWindow((HWND)this->winId(), 0, 0, 100, 100, true);
    });

    //connect(ApplicationStatus::getInstance(), &ApplicationStatus::eventOccured, this, [=](ApplicationEvent event) {
    //    setupEmbeddedWidget();
    //});
    //QTimer::singleShot(2500, Qt::TimerType::CoarseTimer, [=]() {
    //    setupEmbeddedWidget();
    //});


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupEmbeddedWidget()
{
    qInfo () << "running on main window: " << mainWindow;
    auto embeddedWidget = new EmbeddedWidget(mainWindow, true);
    embeddedWidget->setStyleSheet("background-color: orange;");
    embeddedWidget->resize(200, 200);
    embeddedWidget->move(0, 0);
    embeddedWidget->show();
}

void MainWindow::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    setupEmbeddedWidget();
}
