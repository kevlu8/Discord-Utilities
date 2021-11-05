#pragma once

#include <Windows.h>
#include <shellapi.h>
#include "resource.h"

#undef IDI_ICON1
#define TESTICON 101

namespace UI {
	void CreateHiddenConsole();
	void SetConsoleVisible(bool visible);
	bool ToggleConsole();

	extern HWND Window;
	extern int AttachedProcessesCount;
	extern bool IsConsoleOnly;

	int Start(HINSTANCE hInstance);
}