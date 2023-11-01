#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto functionPlotter = new FunctionPlotter(this);


    auto layout = new QVBoxLayout(ui->mainWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(functionPlotter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

