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
};



