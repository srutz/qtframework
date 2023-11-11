
#include "winmain.h"
#include "winutil.h"
#include "applicationstatus.h"
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <string>


#define ID_ACTION_EXIT 1001


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void setupMenu(HWND);

wchar_t szClassName[] = L"HelloWin";

HWND mainWindow = 0;

int WINAPI XWinMain(
    HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;
    WNDCLASSEX wincl;

    /* windows class registration */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    if (!RegisterClassEx(&wincl))
        return 0;

    /* create window instance */
    hwnd = CreateWindowEx(
        0,                   // extended wm styles
        szClassName,
        L"Hello Windows",
        WS_OVERLAPPEDWINDOW, // standard
        CW_USEDEFAULT,       // position
        CW_USEDEFAULT,       // position
        544,                 // width
        375,                 // height
        HWND_DESKTOP,        // desktop parent
        NULL,
        hThisInstance,
        NULL
        );
    mainWindow = hwnd;
    qDebug() << "assigned mainwindow to " << mainWindow;

    setupMenu(hwnd);

    ShowWindow(hwnd, nCmdShow);
}

void windowEventPump() {

    MSG messages;
    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages); // Übersetzt virtuelle Tastenanschläge
        DispatchMessage(&messages);  // Sendet die Nachricht an WindowProcedure
    }
    return messages.wParam;
}

/* winproc */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND child;
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CREATE:
    {
        QString q("hello windows ");
        QTextStream ts(&q);
        ts << mainWindow;
        ts << " " << hwnd;
        auto ws = q.toStdWString();
        auto raw = ws.c_str();
        child = CreateWindowEx(0, L"STATIC",  raw, WS_CHILD | WS_VISIBLE,
                               10, 10, 200, 20, hwnd, (HMENU)1, NULL, NULL);
        //MessageBox(hwnd, "Hello, World!", "Greetings", MB_OK);

        auto as = ApplicationStatus::getInstance();
        as->eventOccured(ApplicationEvent::WIN_WM_CREATED);
    }
    break;
    case WM_PAINT:
        break;
    case WM_SHOWWINDOW:
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case ID_ACTION_EXIT:
            WinUtil::dumpChildren(hwnd);
            //MessageBox(hwnd, L"action exit", L"Confirm", MB_OK);
            break;
        }

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}


void setupMenu(HWND parentWindow) {
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hFileMenu, L"&File");
    AppendMenu(hFileMenu, MF_STRING, ID_ACTION_EXIT, L"E&xit");
    SetMenu(parentWindow, hMenu);
}



void launchWindows()
{
    HINSTANCE hInstance = GetModuleHandleA(nullptr);
    XWinMain(hInstance, 0, (LPSTR) "", SW_SHOW);
}

