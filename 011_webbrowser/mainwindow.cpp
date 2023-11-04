#include <QVBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    webView = new QWebEngineView();

    auto layout = new QVBoxLayout();
    layout->addWidget(webView);
    ui->widget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::heise()
{
    webView->load(QUrl("https://www.heise.de"));
}

void MainWindow::gfu()
{
    webView->load(QUrl("https://www.gfu.net"));
}

void MainWindow::google()
{
    webView->load(QUrl("https://www.google.de"));
}
