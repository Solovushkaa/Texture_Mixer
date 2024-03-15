#include <SFML/Graphics.hpp>
#include "SoftwareDefinition.h"
#include "ImageOperation.h"
#include <string>
#include "SearchFunctions.h"
#include <Windows.h>
#include <list>
#include "resource.h"
#include <codecvt>

#pragma warning(disable : 4996)

std::wstring* RGBA_paths = nullptr;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	std::wifstream config_file(L"config_file.txt");							//
	config_file.imbue(std::locale(config_file.getloc(),						//
		new std::codecvt_utf16<wchar_t, 1114111UL, std::little_endian>));	//
	config_file >> conf[0] >> conf[1] >> conf[2] >> conf[3];				//
	config_file.close();													//

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
		LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClassW", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMassage = { 0 };

	CreateWindow(L"MainWndClassW", L"Texture Mixer", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, 200, 200, 635, 385, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMassage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMassage);
		DispatchMessage(&SoftwareMainMassage);
	}
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };
	NWC.hCursor = Cursor;
	NWC.hIcon = Icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnLoadFile:
			if (GetOpenFileName(&ofn))
			{
				RGBA_paths = SearchFilesInFolder(ofn.lpstrFile);
				SetWindowTextW(hStaticControl, L"File open");
			}
			break;
		case ChangeConf: //изменить конфиг
		{
			int sz = GetWindowTextW(hEditControl, Buffer, TextBufferSize);
			if (sz != 0)
			{
				std::wstring Buff = (L"");
				for (unsigned int i = 0; i < sz; ++i)
				{
					if (Buffer[i] == ' ')
					{
						Buff[i] = '\n';
						Buff += Buffer[i];
					}
					else { Buff += Buffer[i]; }
				}
				std::wistringstream in(Buff);

				in >> conf[0] >> conf[1] >> conf[2];
		
				HANDLE File = CreateFile2(L"config_file.txt", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, CREATE_ALWAYS, NULL);
				WriteFile(File, Buff.c_str(), 2*Buff.size(), NULL, NULL);
				SetWindowTextW(hStaticControl, L"Config changed");
			}
		}
			break;
		case ClearString: // отчистка поля текста
			SetWindowTextA(hEditControl, "");
			break;
		case MixTexture: // смешивание текстур
		{
			if (RGBA_paths != nullptr)
			{
				sf::Texture R_texture, G_texture, B_texture;

				char red[260]; WideCharToMultiByte(1251, 0, RGBA_paths[0].c_str(), -1, red, 256, NULL, NULL);
				R_texture.loadFromFile(red);
				char green[260]; WideCharToMultiByte(1251, 0, RGBA_paths[1].c_str(), -1, green, 256, NULL, NULL);
				G_texture.loadFromFile(green);
				char blue[260]; WideCharToMultiByte(1251, 0, RGBA_paths[2].c_str(), -1, blue, 256, NULL, NULL);
				B_texture.loadFromFile(blue);

				sf::Texture mixTexture;
				mixTexture.create(R_texture.getSize().x, R_texture.getSize().y);

				MixLayersRGB(mixTexture, R_texture, G_texture, B_texture);

				sf::Sprite sprite;
				sprite.setTexture(mixTexture);

				sf::RenderWindow window(sf::VideoMode(mixTexture.getSize().x, mixTexture.getSize().y), "Preview");
				//window.setFramerateLimit(1);
				window.draw(sprite);
				window.display();
				sf::sleep(sf::seconds(2));

				sf::Image image = mixTexture.copyToImage();

				std::wstring SavepathW = PathAdjustment(ofn.lpstrFile) + conf[0][0] + conf[0][1] + conf[1][0] + conf[1][1] + conf[2][0] + conf[2][1] + L".png";
				char Savepath[260]; WideCharToMultiByte(1251, 0, SavepathW.c_str(), -1, Savepath, 256, NULL, NULL);
				image.saveToFile(Savepath);
				window.close();
				SetWindowTextW(hStaticControl, L"Mixed");
			}
			break;
		}
		default: break;
		}
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		SetOpenFileParams(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: 
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU RootMenu2 = CreateMenu();
	HMENU SubMenu = CreateMenu();

	AppendMenu(SubMenu, MF_STRING, OnLoadFile, L"Load");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");

	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	// создание окон
	hStaticControl = CreateWindowA("static", "Config", WS_VISIBLE | WS_CHILD, 5, 5, 200, 30, hWnd, NULL, NULL, NULL);

	hEditControl = CreateWindow(L"edit", (conf[0] + L' ' + conf[1] + L' ' + conf[2] + L' ' + conf[3]).c_str(), WS_VISIBLE | WS_CHILD | ES_MULTILINE, 5, 35, 490, 85, hWnd, NULL, NULL, NULL);

	HWND hFileSControl = CreateWindow(L"static", L"• Меню “File” – открывает доступ к подменю “Load”", WS_VISIBLE | WS_CHILD, 5, 165, 590, 20, hWnd, NULL, NULL, NULL);
	HWND hLoadSControl = CreateWindow(L"static", L"• Подменю “Load” – используется для выбора папки с помощью выбора файла", WS_VISIBLE | WS_CHILD, 5, 195, 590, 20, hWnd, NULL, NULL, NULL);
	HWND hClearSControl = CreateWindow(L"static", L"• Кнопка “Clear” – отчищает поле для ввода конфигурации", WS_VISIBLE | WS_CHILD, 5, 225, 590, 20, hWnd, NULL, NULL, NULL);
	HWND hChangeSControl = CreateWindow(L"static", L"• Кнопка “Change preset” – изменяет конфигурацию поиска текстур", WS_VISIBLE | WS_CHILD, 5, 255, 590, 20, hWnd, NULL, NULL, NULL);
	HWND hMixSControl = CreateWindow(L"static", L"• Кнопка “Mix” – смешивает текстуры", WS_VISIBLE | WS_CHILD, 5, 285, 590, 20, hWnd, NULL, NULL, NULL);


	HWND hClearControl = CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 436, 5, 60, 25, hWnd, (HMENU)ClearString, NULL, NULL);

	HWND hChangeControl = CreateWindowA("button", "Change preset", WS_VISIBLE | WS_CHILD | ES_CENTER, 498, 35, 120, 40, hWnd, (HMENU)ChangeConf, NULL, NULL);

	HWND hMixControl = CreateWindowA("button", "Mix", WS_VISIBLE | WS_CHILD | ES_CENTER, 498, 80, 120, 40, hWnd, (HMENU)MixTexture, NULL, NULL);

	// Установка шрифта
	SendMessage(hStaticControl, WM_SETFONT, (WPARAM)hFont25, TRUE);
	SendMessage(hEditControl, WM_SETFONT, (WPARAM)hFont30, TRUE);

	SendMessage(hFileSControl, WM_SETFONT, (WPARAM)hFont30, TRUE);
	SendMessage(hLoadSControl, WM_SETFONT, (WPARAM)hFont30, TRUE);
	SendMessage(hClearSControl, WM_SETFONT, (WPARAM)hFont30, TRUE);
	SendMessage(hChangeSControl, WM_SETFONT, (WPARAM)hFont30, TRUE);
	SendMessage(hMixSControl, WM_SETFONT, (WPARAM)hFont30, TRUE);

	SendMessage(hClearControl, WM_SETFONT, (WPARAM)hFont30, TRUE);
	SendMessage(hChangeControl, WM_SETFONT, (WPARAM)hFont30, TRUE);
	SendMessage(hMixControl, WM_SETFONT, (WPARAM)hFont30, TRUE);
}

void SetOpenFileParams(HWND hWnd)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = L"All Files\0*.*\0\0";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = L"C:\\Users\\gm131\\OneDrive\\Рабочий стол\\MY3DASSETS";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}