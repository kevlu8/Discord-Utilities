#include <windows.h>
#include <iostream>
#include "tray.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ShellExecuteA(NULL, "open", "./DiscUtil.exe", NULL, NULL, SW_HIDE);
    UI::Start(hInstance);
    return 0;
}