


#include "stdafx.h"
#include "tetris.h"
#include "resource.h"
#include "tetrisGraph.h"



char  szMainWindowTitle[]  = "Tetris Ver:";

HINSTANCE hInst;

// =====================================
// WinMain function
// =====================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)  
{

	MSG  msg;
	HWND hwnd;
	hInst = hInstance;
	HBITMAP hBmp   = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP_BACK));
	HBRUSH hBrush  = CreatePatternBrush(hBmp);
	Tetris::setBmp1(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPf1)));
	Tetris::setBmp2(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPf2)));
	Tetris::setBmp3(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPf3)));
	Tetris::setBmp4(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPf4)));
	Tetris::setBmp5(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPf5)));
	Tetris::setBmp6(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPf6)));
	Tetris::setBmp7(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPf7)));
	Tetris::setBmpback(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP_BACK2)));


	if(!Register(hInstance, hBrush))
		return FALSE;

	hwnd = CreateWindow(
		szMainClassName,     // the window class name
		strcat(szMainWindowTitle, VERSION),   // the window title
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		140, 80, SCREEN_RESOLUTION_WIDTH, SCREEN_RESOLUTION_LENGTH,
		0,                   // the parent window identifier
		0,                   // the menu identifier
		hInstance,           // the application identifier
		NULL);               

	if(!hwnd)
		return FALSE;


	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	

	hwnd_button=CreateWindow("button", "Begin",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		410, 370,
		90, 60,
		hwnd,
		(HMENU) IDB_BUTTON1,
		hInstance, NULL);
	

	CreateWindow("button", "Left",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	  410, 470,
		90, 60,
		hwnd,
		(HMENU)IDB_BUTTONL,
		hInstance, NULL);
	CreateWindow("button", "Down",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		510, 470,
		90, 60,
		hwnd,
		(HMENU)IDB_BUTTOND,
		hInstance, NULL);
	CreateWindow("button", "Right",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		610, 470,
		90, 60,
		hwnd,
		(HMENU)IDB_BUTTONR,
		hInstance, NULL);
	CreateWindow("button", "Povorot",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		610, 370,
		90, 60,
		hwnd,
		(HMENU)IDB_BUTTONP,
		hInstance, NULL);
	CreateWindow("button", "Up",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		510, 370,
		90, 60,
		hwnd,
		(HMENU)IDB_BUTTONU,
		hInstance, NULL);

	while(GetMessage(&msg, 0, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteObject(hBmp);
	DeleteObject(hBrush);
	Tetris::deleteBmp1();
	Tetris::deleteBmp2();
	Tetris::deleteBmp3();
	Tetris::deleteBmp4();
	Tetris::deleteBmp5();
	Tetris::deleteBmp6();
	Tetris::deleteBmp7();
	Tetris::deleteBmpback();

	return msg.wParam;
}






