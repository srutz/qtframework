#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionExit, &QAction::triggered, this, [] {
        QApplication::exit(0);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

