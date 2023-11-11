#include "winutil.h"
#include <QDebug>

static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);

static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
    wchar_t class_name[1000];
    wchar_t title[1000];
    GetClassNameW(hwnd, class_name, sizeof(class_name));
    GetWindowTextW(hwnd, title, sizeof(title));
    RECT r;
    GetWindowRect(hwnd, &r);
    qInfo() << "child " << hwnd
            << ", class=" << QString::fromWCharArray(class_name)
            << ", title" << QString::fromWCharArray(title)
            << ", left=" << r.left
            << ", top=" << r.top
            << ", right=" << r.right
            << ", bottom=" << r.bottom
        ;
    EnumChildWindows(hwnd, EnumChildProc, 0);
    return TRUE;

}

void WinUtil::dumpChildren(HWND window)
{
    EnumChildWindows(window, EnumChildProc, 0);
}
