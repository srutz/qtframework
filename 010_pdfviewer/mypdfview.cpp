#include "mypdfview.h"

MyPdfView::MyPdfView(QWidget *parent)
    : QPdfView{parent}
{
    this->setPageMode(QPdfView::PageMode::MultiPage);
}

void MyPdfView::showDocument(const QString &filename)
{
    QPdfDocument *document = new QPdfDocument(this);
    document->load(filename);
    this->setDocument(document);
}
