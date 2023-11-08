#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

wchar_t szClassName[] = L"HelloWin";


int WINAPI XWinMain(
    HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;               // Handle für das Fenster
    MSG messages;            // Nachrichtenstruktur
    WNDCLASSEX wincl;        // Datenstruktur für die Fensterklasse

    /* windows class registration */
    // Fensterklasse konfigurieren
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
    ShowWindow(hwnd, nCmdShow);
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
    switch (message)
    {
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_CREATE:
      //MessageBox(hwnd, "Hello, World!", "Greetings", MB_OK);
      break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}



void launchWindows()
{
    HINSTANCE hInstance = GetModuleHandleA(nullptr);
    XWinMain(hInstance, 0, (LPSTR) "", SW_SHOW);
}

