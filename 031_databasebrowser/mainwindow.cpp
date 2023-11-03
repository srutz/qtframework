#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setSizes({ 600, 50 });

    auto model = new QSqlQueryModel(ui->tableView);
    ui->tableView->setModel(model);

    QObject::connect(ui->actionExit, &QAction::triggered, this, [] {
        QApplication::exit(0);
    });

    QObject::connect(ui->executeButton, &QPushButton::clicked, this, [=] {
        QString sql = ui->textEdit->toPlainText().trimmed();
        qInfo() << "query" << sql;
        QSqlQuery query(sql);

        auto model = dynamic_cast<QSqlQueryModel*>(ui->tableView->model());
        model->setQuery(std::move(query));
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

