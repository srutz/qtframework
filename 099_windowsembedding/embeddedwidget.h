i#include <QtWidgets>
#include <Windows.h>

class EmbeddedWidget : public QWidget
{
public:
    EmbeddedWidget(HWND parentHwnd) {

        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        SetParent((HWND)winId(), parentHwnd);

        LONG style = GetWindowLong((HWND)winId(), GWL_STYLE);
        style = style & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
        SetWindowLong((HWND)winId(), GWL_STYLE, style);
	/* set size and pos here or from within windows code */
    }
    
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override {
        MSG *msg = static_cast<MSG *>(message);
	/* handle windows messages here */
        return QWidget::nativeEvent(eventType, message, result);
    }
};

