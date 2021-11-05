#include <windows.h>
#include <iostream>
#include "tray.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    UI::Start(hInstance);
    return 0;
}