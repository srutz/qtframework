#include <QUrl>
#include <QtQuickWidgets/QQuickWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto url = QUrl::fromLocalFile("/home/sr/work/qt/qtframework/015_qtandqml/logoshapes.qml");
    ui->quickWidget->setResizeMode(QQuickWidget::ResizeMode::SizeViewToRootObject);
    ui->quickWidget->setResizeMode(QQuickWidget::ResizeMode::SizeRootObjectToView);
    ui->quickWidget->setSource(url);
}

MainWindow::~MainWindow()
{
    delete ui;
}

