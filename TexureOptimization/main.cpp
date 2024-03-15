#include <SFML/Graphics.hpp>
#include "SoftwareDefinition.h"
#include "resource.h"

#include "ImageOperation.h"
//#include <Windows.h>
//#include <fstream>
#include <string>
#include "SearchFun.h"

//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
//{
//	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
//		LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
//		L"MainWndClassW", SoftwareMainProcedure);
//
//	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
//	MSG SoftwareMainMassage = { 0 };
//
//	CreateWindow(L"MainWndClassW", L"First C++ window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 512, 512, NULL, NULL, NULL, NULL);
//
//	while (GetMessage(&SoftwareMainMassage, NULL, NULL, NULL))
//	{
//		
//		TranslateMessage(&SoftwareMainMassage);
//		DispatchMessage(&SoftwareMainMassage);
//	}
//}
//
//WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
//{
//	WNDCLASS NWC = { 0 };
//	NWC.hCursor = Cursor;
//	NWC.hIcon = Icon;
//	NWC.hInstance = hInst;
//	NWC.lpszClassName = Name;
//	NWC.hbrBackground = BGColor;
//	NWC.lpfnWndProc = Procedure;
//
//	return NWC;
//}
//
//LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
//{
//	switch (msg)
//	{
//	case WM_COMMAND:
//		switch (wp)
//		{
//		case OnMenuAction1:
//			MessageBoxA(hWnd, "Menu 1 was clicked", "Menu worked", MB_OK);
//			break;
//		case OnSaveFile:
//			if (GetSaveFileName(&ofn)) {/*SaveData(filename);*/} //тут сохранение в файл
//			break;
//		case OnLoadFile:
//			if (GetOpenFileName(&ofn)) { SearchFilesInFolder(ofn.lpstrFile);/*LoadData(filename);*/ } //тут открытие файла
//			break;
//		case OnExitSoftware:
//			PostQuitMessage(0);
//			break;
//		case OnButtonClick:
//			SetWindowTextA(hEditControl, "");
//		case OnReadField:
//			readChars = GetWindowTextA(hEditControl, Buffer, TextBufferSize);
//			SetWindowTextA(hStaticControl, Buffer);
//			SetWindowTextA(hStaticControl, ("Symdols read: " + std::to_string(readChars)).c_str());
//			break;
//
//		default: break;
//		}
//		break;
//	case WM_CREATE:
//		MainWndAddMenus(hWnd);
//		MainWndAddWidgets(hWnd);
//		SetOpenFileParams(hWnd);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	default: return DefWindowProc(hWnd, msg, wp, lp);
//	}
//}
//
//void MainWndAddMenus(HWND hWnd)
//{
//	HMENU RootMenu = CreateMenu();
//	HMENU SubMenu = CreateMenu();
//
//	AppendMenu(SubMenu, MF_STRING, OnMenuAction1, L"Menu 1");
//	AppendMenu(SubMenu, MF_STRING, OnSaveFile, L"Save");
//	AppendMenu(SubMenu, MF_STRING, OnLoadFile, L"Load");
//
//	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
//
//	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");
//
//	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
//
//	SetMenu(hWnd, RootMenu);
//}
//
//void MainWndAddWidgets(HWND hWnd)
//{
//	hStaticControl = CreateWindowA("static", "Hello World", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 490, 20, hWnd, NULL, NULL, NULL);
//
//	hEditControl = CreateWindowA("edit", "This is edit control", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_MULTILINE | WS_VSCROLL, 5, 30, 490, 60, hWnd, NULL, NULL, NULL);
//
//	CreateWindowA("button", "Click", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 100, 490, 20, hWnd, (HMENU)OnButtonClick, NULL, NULL);
//
//	CreateWindowA("button", "Read", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 140, 490, 20, hWnd, (HMENU)OnReadField, NULL, NULL);
//}
//
//void SetOpenFileParams(HWND hWnd)
//{
//	ZeroMemory(&ofn, sizeof(ofn));
//	ofn.lStructSize = sizeof(ofn);
//	ofn.hwndOwner = hWnd;
//	ofn.lpstrFile = filename;
//	ofn.nMaxFile = sizeof(filename);
//	ofn.lpstrFilter = L"All Files\0*.*\0\0";
//	ofn.lpstrFileTitle = NULL;
//	ofn.nMaxFileTitle = 0;
//	ofn.lpstrInitialDir = L"C:\\Users\\gm131\\OneDrive\\Рабочий стол\\MY3DASSETS";
//	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
//}

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "test");
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { window.close(); }
		}
		sf::Texture R_texture, G_texture, B_texture;
		std::string R_ImageFile = "C:\\Users\\gm131\\OneDrive\\Рабочий стол\\MY3DASSETS\\Sockets_ASSET\\SSSR_Socket-1_Material_Metallic.png";
		std::string G_ImageFile = "C:\\Users\\gm131\\OneDrive\\Рабочий стол\\MY3DASSETS\\Sockets_ASSET\\SSSR_Socket-1_Material_Roughness.png";
		std::string B_ImageFile = "C:\\Users\\gm131\\OneDrive\\Рабочий стол\\MY3DASSETS\\Sockets_ASSET\\1_thickness.png";


		R_texture.loadFromFile(R_ImageFile);
		G_texture.loadFromFile(G_ImageFile);
		B_texture.loadFromFile(B_ImageFile);

		sf::Sprite sprite;

		sf::Texture mixtexture;
		mixtexture.create(256, 256);
		MixLayers(mixtexture, R_texture, G_texture, B_texture);
		sprite.setTexture(mixtexture);

		window.clear();
		window.draw(sprite);
		window.display();

		sf::Image image = mixtexture.copyToImage();
		image.saveToFile("C:\\Users\\gm131\\OneDrive\\Рабочий стол\\test.png");

		system("pause");
	}
	return 0;
}