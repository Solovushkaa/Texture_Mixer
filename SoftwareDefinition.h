#pragma once

#include <Windows.h>

#define ChangeConf 2
#define MixTexture 3

#define ClearString 4
#define OnLoadFile 5

#define TextBufferSize 100

wchar_t Buffer[TextBufferSize];
unsigned int confSize;

HWND hStaticControl;
HWND hEditControl;

OPENFILENAME ofn;
wchar_t filename[260];

HFONT hFont25 = CreateFont(
	25, 0, 0, 0, 0, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
	OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
	DEFAULT_PITCH | FF_DONTCARE, L"Calibri"
);

HFONT hFont30 = CreateFont(
	22, 0, 0, 0, 0, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
	OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
	DEFAULT_PITCH | FF_DONTCARE, L"Calibri"
);

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SetOpenFileParams(HWND hWnd);