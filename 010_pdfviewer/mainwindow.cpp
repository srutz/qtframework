
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mypdfview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fileChooser(nullptr)
{
    ui->setupUi(this);
    fileChooser = new QFileDialog(this);
    fileChooser->setNameFilter("PDF (*.pdf)");
    QObject::connect(fileChooser, &QFileDialog::fileSelected, this, &MainWindow::openPDF);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::choosePDF()
{
    fileChooser->show();
}

void MainWindow::openPDF(const QString &filename)
{
    qInfo() << "opening pdf \"" << filename << "\"";

    auto *pdfView = this->findChild<MyPdfView*>("pdfView");
    pdfView->showDocument(filename);
}

