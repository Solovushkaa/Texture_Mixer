#pragma once

#include <Windows.h>

#define OnMenuAction1 1
#define OnMenuAction2 2
#define OnMenuAction3 3
#define OnExitSoftware 4
#define OnButtonClick 5
#define OnReadField 6

#define OnSaveFile 7
#define OnLoadFile 8

#define TextBufferSize 10

char Buffer[TextBufferSize];
int readChars;

HWND hStaticControl;
HWND hEditControl;

wchar_t filename[260];
OPENFILENAME ofn;

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SetOpenFileParams(HWND hWnd);