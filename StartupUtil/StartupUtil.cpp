#include <windows.h>
#include <iostream>
#include "tray.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int e;
    std::cout << "e";
    UI::start(hInstance);
    std::cin >> e;
    return 0;
}