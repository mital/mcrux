#include "StdAfx.h"
#include "Resource.h"
#include <tchar.h>

#include "MCruxWindow.h"

MCruxWindow::MCruxWindow(HINSTANCE _hInstance, const MCruxWindowConfiguration * _config)
	: hInstance(_hInstance),
	  hWnd(NULL),
	  config(_config)
{
	hWnd = CreateWindow(MCruxWindow::getWindowClassName(),
		config->getWindowTitle(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
}

MCruxWindow::~MCruxWindow()
{
}

int MCruxWindow::ShowWindow() const
{
	return ::ShowWindow(hWnd, SW_SHOW);
}


int MCruxWindow::HideWindow() const
{
	return ::ShowWindow(hWnd, SW_HIDE);
}


int MCruxWindow::UpdateWindow() const
{
	return ::UpdateWindow(hWnd);
}


TCHAR * MCruxWindow::getWindowClassName()
{
	static TCHAR windowClassName[MAX_LOADSTRING] = _T("MCruxWindowClass");
	return windowClassName;
}


void MCruxWindow::initWindowClass(HINSTANCE hInstance)
{
	static bool bInit = false;
	if (!bInit)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= MCruxWindow::WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MCRUX_ICON));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= MCruxWindow::getWindowClassName();
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		RegisterClassEx(&wcex);
		
		bInit = true;
	}
}


void MCruxWindow::unInitWindowClass(HINSTANCE hInstance)
{
	UnregisterClass(MCruxWindow::getWindowClassName(), hInstance);
}


LRESULT CALLBACK MCruxWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		//switch (wmId)
		//{
		//case IDM_ABOUT:
		//	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		//	break;
		//case IDM_EXIT:
		//	DestroyWindow(hWnd);
		//	break;
		//default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		//}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

