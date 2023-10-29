#ifndef MYPDFVIEW_H
#define MYPDFVIEW_H

#include <QWidget>
#include <QPdfView>
#include <QPdfDocument>


class MyPdfView : public QPdfView
{
    Q_OBJECT
public:
    explicit MyPdfView(QWidget *parent = nullptr);

public slots:
    void showDocument(const QString &filename);

signals:

};

#endif // MYPDFVIEW_H
