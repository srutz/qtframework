#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    auto functionScene = new FunctionScene(this);

    auto layout = new QVBoxLayout(ui->mainWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(functionScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

