#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "winmain.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
        SetWindowTextW(mainWindow, L"set from qt");
        LONG style = GetWindowLong((HWND)winId(), GWL_STYLE);
        style = style & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU | WS_CHILD);
        SetWindowLong((HWND)winId(), GWL_STYLE, style);
        SetParent((HWND) this->winId(), mainWindow);
        MoveWindow((HWND)this->winId(), 0, 0, 100, 100, true);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

