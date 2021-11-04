#pragma once

#include <Windows.h>
#include <shellapi.h>

namespace UI
{
	void CreateHiddenConsole();
	void SetConsoleVisible(bool visible);
	bool ToggleConsole();
	int Start(HINSTANCE instance, LPTHREAD_START_ROUTINE watchthread);

	extern HWND Window;
	extern int AttachedProcessesCount;
	extern bool IsConsoleOnly;

	int start(HINSTANCE hInstance) {
		NOTIFYICONDATA NotifyIconData;
		NotifyIconData.cbSize = sizeof(NotifyIconData);
		NotifyIconData.hWnd = UI::Window;
		NotifyIconData.uID = IDI_ICON1;
		NotifyIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		//NotifyIconData.uCallbackMessage = RFU_TRAYICON;
		NotifyIconData.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		//NotifyIconData.szTip = L"Discord Utilities";
		strcpy(NotifyIconData.szTip, "Discord Utilities - Thanks for being a CPU Donator!");

		Shell_NotifyIcon(NIM_ADD, &NotifyIconData);
	}
}