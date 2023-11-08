#include <QWidget>
#include <Windows.h>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>

class EmbeddedWidget : public QWidget
{
public:
    explicit EmbeddedWidget(HWND parentHwnd, bool dummy)
    {
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        SetParent((HWND)winId(), parentHwnd);

        LONG style = GetWindowLong((HWND)winId(), GWL_STYLE);
        style = style & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU | WS_CHILD);
        SetWindowLong((HWND)winId(), GWL_STYLE, style);

        /* set size and pos here or from within windows code */
        MoveWindow((HWND)winId(), 0, 0, 200, 200, true);

        auto layout = new QHBoxLayout(this);
        auto label = new QLabel(this);
        layout->addWidget(label);
        this->setLayout(layout);
        qInfo() << "constructed. embedded widget";
    }
    
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override {
        MSG *msg = static_cast<MSG *>(message);
        /* handle windows messages here */
        return QWidget::nativeEvent(eventType, message, result);
    }
};



