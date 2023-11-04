#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebView/QtWebView>
#include <QtWebEngineWidgets/QWebEngineView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void heise();
    void gfu();
    void google();

private:
    Ui::MainWindow *ui;
    QWebEngineView *webView;

};
#endif // MAINWINDOW_H
