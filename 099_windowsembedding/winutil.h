#ifndef WINUTIL_H
#define WINUTIL_H

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

class WinUtil
{
private:
    WinUtil() { }

public:
    static void dumpChildren(HWND window);
};

#endif // WINUTIL_H
