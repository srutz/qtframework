#ifndef WINMAIN_H
#define WINMAIN_H

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

extern HWND mainWindow;

void launchWindows();
void windowEventPump();

#endif // WINMAIN_H
