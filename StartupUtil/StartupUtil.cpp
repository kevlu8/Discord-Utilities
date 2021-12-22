#include <windows.h>
#include <iostream>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ShellExecuteA(NULL, "open", "DiscUtil.exe", "--startup", NULL, SW_HIDE);
    return 0;
}