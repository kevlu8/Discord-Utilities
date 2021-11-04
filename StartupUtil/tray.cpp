#ifdef UNICODE
#undef UNICODE
#define MULTIBYTE
#endif

#include <Windows.h>
#include <shellapi.h>

#include <cstdio>

#define RFU_TRAYICON			WM_APP + 1
#define RFU_TRAYMENU_APC		WM_APP + 2
#define RFU_TRAYMENU_CONSOLE	WM_APP + 3
#define RFU_TRAYMENU_EXIT		WM_APP + 4
#define RFU_TRAYMENU_VSYNC		WM_APP + 5
#define RFU_TRAYMENU_LOADSET	WM_APP + 6
#define RFU_TRAYMENU_GITHUB		WM_APP + 7
#define RFU_TRAYMENU_STUDIO		WM_APP + 8
#define RFU_TRAYMENU_CFU		WM_APP + 9
#define RFU_TRAYMENU_ADV_NBE	WM_APP + 10
#define RFU_TRAYMENU_ADV_SE		WM_APP + 11
#define RFU_TRAYMENU_ADV_QS		WM_APP + 12
#define RFU_TRAYMENU_CLIENT		WM_APP + 13

#define RFU_FCS_FIRST			WM_APP + 20
#define RFU_FCS_NONE			RFU_FCS_FIRST

#include "resource.h"
#include "settings.h"
#include "tray.h"

#define MULTIBYTE

HWND UI::Window = NULL;
int UI::AttachedProcessesCount = 0;
bool UI::IsConsoleOnly = false;

HANDLE WatchThread;
NOTIFYICONDATA NotifyIconData;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case RFU_TRAYICON:
	{
		if (lParam == WM_RBUTTONDOWN || lParam == WM_LBUTTONDOWN)
		{
			POINT position;
			GetCursorPos(&position);

			HMENU popup = CreatePopupMenu();

			char buffer[64];
			sprintf_s(buffer, "Attached Processes: %d", UI::AttachedProcessesCount);

			AppendMenu(popup, MF_STRING | MF_GRAYED, RFU_TRAYMENU_APC, buffer);
			AppendMenu(popup, MF_SEPARATOR, 0, NULL);

			//AppendMenu(popup, MF_STIRNG | (function ? MF_CHECKED : 0), RFU, "Name");
			AppendMenu(popup, MF_STRING | (Settings::Pause ? MF_CHECKED : 0), RFU_TRAYMENU_CLIENT, "Pause Donation");
			AppendMenu(popup, MF_STRING | (Settings::Exit ? MF_CHECKED : 0), RFU_TRAYMENU_STUDIO, "Exit Discord Utilities");

			HMENU submenu = CreatePopupMenu();
			AppendMenu(submenu, MF_STRING, RFU_FCS_NONE, "None");
			for (size_t i = 0; i < Settings::pauseTimes.size(); i++)
			{
				double value = Settings::pauseTimes[i];

				char name[16] = { 0 };
				if (static_cast<int>(value) == value)
					snprintf(name, sizeof(name), "%d", static_cast<int>(value));
				else
					snprintf(name, sizeof(name), "%.2f", value);

				AppendMenu(submenu, MF_STRING, RFU_FCS_NONE + i + 1, name);
			}
			CheckMenuRadioItem(submenu, RFU_FCS_FIRST, RFU_FCS_FIRST + Settings::pauseTimes.size(), RFU_FCS_FIRST + Settings::pauseSelection, MF_BYCOMMAND);
			AppendMenu(popup, MF_POPUP, (UINT_PTR)submenu, "Pause Donation");

			HMENU advanced = CreatePopupMenu();

			AppendMenu(popup, MF_SEPARATOR, 0, NULL);
			AppendMenu(popup, MF_STRING, RFU_TRAYMENU_CONSOLE, "Toggle Console");
			AppendMenu(popup, MF_STRING, RFU_TRAYMENU_GITHUB, "Visit GitHub");
			AppendMenu(popup, MF_STRING, RFU_TRAYMENU_EXIT, "Exit");

			SetForegroundWindow(hwnd); // to allow "clicking away"
			BOOL result = TrackPopupMenu(popup, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTALIGN, position.x, position.y, 0, hwnd, NULL);

			if (result != 0)
			{
				switch (result)
				{
				case RFU_TRAYMENU_CONSOLE:
					UI::ToggleConsole();
					break;

				case RFU_TRAYMENU_GITHUB:
					ShellExecuteA(NULL, "open", "https://github.com/kevlu8/DiscUtil", NULL, NULL, SW_SHOWNORMAL);
					break;

				default:
					if (result >= RFU_FCS_FIRST
						&& result <= RFU_FCS_FIRST + Settings::pauseTimes.size())
					{
						Settings::pauseSelection = result - RFU_FCS_FIRST;
						Settings::pauseTime = Settings::pauseSelection == 0 ? 0 : Settings::pauseTimes[Settings::pauseSelection - 1];
					}
				}
			}

			return 1;
		}

		break;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

bool IsConsoleVisible = false;

void UI::SetConsoleVisible(bool visible)
{
	IsConsoleVisible = visible;
	ShowWindow(GetConsoleWindow(), visible ? SW_SHOWNORMAL : SW_HIDE);
}

void UI::CreateHiddenConsole()
{
	AllocConsole();

	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	if (!UI::IsConsoleOnly)
	{
		HMENU menu = GetSystemMenu(GetConsoleWindow(), FALSE);
		EnableMenuItem(menu, SC_CLOSE, MF_GRAYED);
	}
	SetConsoleVisible(false);
}

bool UI::ToggleConsole()
{
	if (!GetConsoleWindow())
		UI::CreateHiddenConsole();

	SetConsoleVisible(!IsConsoleVisible);

	return IsConsoleVisible;
}

int UI::Start(HINSTANCE instance, LPTHREAD_START_ROUTINE watchthread)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(wcex);
	wcex.style = 0;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "RFUClass";
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);

	UI::Window = CreateWindow("RFUClass", "Roblox FPS Unlocker", 0, 0, 0, 0, 0, NULL, NULL, instance, NULL);
	if (!UI::Window)
		return 0;

	NotifyIconData.cbSize = sizeof(NotifyIconData);
	NotifyIconData.hWnd = UI::Window;
	NotifyIconData.uID = IDI_ICON1;
	NotifyIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	NotifyIconData.uCallbackMessage = RFU_TRAYICON;
	NotifyIconData.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON1));
	strcpy(NotifyIconData.szTip, "Discord Utilities");

	Shell_NotifyIcon(NIM_ADD, &NotifyIconData);

	WatchThread = CreateThread(NULL, 0, watchthread, NULL, NULL, NULL);

	BOOL ret;
	MSG msg;

	while ((ret = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (ret != -1)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



#ifdef MULTIBYTE
#undef MULTIBYTE
#define UNICODE
#endif