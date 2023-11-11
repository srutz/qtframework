#include <QWidget>
#include <Windows.h>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>
#include "winmain.h"

class EmbeddedWidget : public QWidget
{
public:
    explicit EmbeddedWidget(HWND parentHwnd, bool dummy)
    {
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::SubWindow);
        SetParent((HWND)winId(), parentHwnd);

        LONG style = GetWindowLong((HWND)winId(), GWL_STYLE);
        style = style & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU | WS_CHILD);
        SetWindowLong((HWND)winId(), GWL_STYLE, style);

        /* set size and pos here or from within windows code */
        MoveWindow((HWND)winId(), 0, 0, 200, 200, true);

        auto b1 = new QPushButton();
        b1->setText("click me");

        auto layout = new QHBoxLayout(this);
        auto label = new QLabel(this);
        //layout->addWidget(label);
        layout->addWidget(b1);

        connect(b1, &QPushButton::clicked, this, [=]() {
            SetWindowTextW(mainWindow, L"set from qt");
        });

        this->setLayout(layout);
        qInfo() << "constructed. embedded widget";
    }
    
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override {
        MSG *msg = static_cast<MSG *>(message);
        /* handle windows messages here */
        return QWidget::nativeEvent(eventType, message, result);
    }

    bool event(QEvent *e) {
        switch(e->type()) {
        case QEvent::Polish:
            break;
        case QEvent::WindowBlocked:
            //if (hwnd)
            //    EnableWindow(hwnd, false);
            break;
        case QEvent::WindowUnblocked:
            //if (hwnd)
            //    EnableWindow(hwnd, true);
            break;
        default:
            break;
        }
        return QWidget::event(e);
    }

    void showEvent(QShowEvent *e) override {
        QWidget::showEvent(e);
        qInfo() << "showEvent";
        //if (hwnd)
        //    SetWindowPos(hwnd, HWND_TOP, 0, 0, width(), height(), SWP_SHOWWINDOW);
    }

    void focusInEvent(QFocusEvent *e) override{
        QWidget::focusInEvent(e);
        //if (hwnd)
        //    ::SetFocus(hwnd);
    }

    void resizeEvent(QResizeEvent *e) override {
        QWidget::resizeEvent(e);
        //if (hwnd)
        //    SetWindowPos(hwnd, HWND_TOP, 0, 0, width(), height(), 0);
    }

    void paintEvent(QPaintEvent *e) override {
        QWidget::paintEvent(e);
        qInfo() << "paintEvent";
    }

};



