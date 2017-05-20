// ImgStream.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ImgStream.h"
#include "AviFile.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

/////////////////////////////////////////////////////////////
/// Create the Movie File Object
///
CAviFile	avi("Output.Avi", mmioFOURCC('M','S','V','C'), 1);	// Use MSVC codec with 1 FPS

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

HDC			hBackDC=NULL;
HBITMAP		hBackBitmap=NULL;
HBITMAP		hBackOldBitmap=NULL;
UINT_PTR	nTimerID=0;

LPVOID		pBits=NULL;
static int	nCount=0;
static bool bFailed = false;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_IMGSTREAM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	//CoInitialize(NULL);

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_IMGSTREAM);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

//	CoUninitialize();

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_IMGSTREAM);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_IMGSTREAM;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED|WS_VISIBLE|WS_SYSMENU,
      CW_USEDEFAULT, CW_USEDEFAULT, 320, 240, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
		{
			HDC hdc=GetDC(hWnd);
			hBackDC=CreateCompatibleDC(hdc);

			BITMAPINFO	bmpInfo;

			ZeroMemory(&bmpInfo,sizeof(bmpInfo));
			bmpInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
			bmpInfo.bmiHeader.biBitCount=32;
			bmpInfo.bmiHeader.biCompression=BI_RGB;
			bmpInfo.bmiHeader.biSizeImage=320*240*4;
			bmpInfo.bmiHeader.biPlanes=1;
			bmpInfo.bmiHeader.biHeight=240;
			bmpInfo.bmiHeader.biWidth=320;

			hBackBitmap=CreateDIBSection(hBackDC,&bmpInfo,DIB_RGB_COLORS,&pBits,NULL,NULL);
			if(hBackBitmap==NULL)
			{
				MessageBox(NULL,"Unable to create bitmap","Error",MB_OK);
				return -1;
			}

			ReleaseDC(hWnd,hdc);
			nTimerID=SetTimer(hWnd,1000,1000,NULL);
			break;
		}
	case WM_PAINT:
		{
			RECT	rect;
			GetClientRect(hWnd,&rect);
			hBackOldBitmap=(HBITMAP)SelectObject(hBackDC,hBackBitmap);

			char str[10];
			sprintf(str,"%d",nCount++);
			DrawText(hBackDC, str, (int)strlen(str), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			hdc = BeginPaint(hWnd, &ps);
			BitBlt(hdc,0,0,rect.right,rect.bottom,hBackDC,0,0,SRCCOPY);
			EndPaint(hWnd, &ps);

			SelectObject(hBackDC,hBackOldBitmap);
			GdiFlush();

			if(FAILED(avi.AppendNewFrame(hBackBitmap)))	//avi.AppendNewFrame(320, 240, pBits, 32)))
			{
				bFailed = true;
				MessageBox(hWnd, avi.GetLastErrorMessage(), _T("Error Occured"), MB_OK | MB_ICONERROR);
				DestroyWindow(hWnd);
			}

			if(nCount>=20)		// Exit after 20 Frames
				DestroyWindow(hWnd);
			break;
		}
	case WM_TIMER:
		{
			if(!bFailed)
				InvalidateRect(hWnd,NULL,false);
			break;
		}
	case WM_ERASEBKGND:
		{
			return true;
		}
	case WM_DESTROY:
		{
			if(nTimerID)
			{
				KillTimer(hWnd,nTimerID);
				nTimerID=0;
			}
			if(hBackDC)
			{
				DeleteDC(hBackDC);
				hBackDC=NULL;
			}
			if(hBackBitmap)
			{
				DeleteObject(hBackBitmap);
				hBackBitmap=NULL;
			}
			PostQuitMessage(0);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
