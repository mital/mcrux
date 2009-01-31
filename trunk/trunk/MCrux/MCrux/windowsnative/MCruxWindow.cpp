#include "StdAfx.h"
#include "Resource.h"
#include <tchar.h>

#include "MCruxWindow.h"

MCruxWindow::MCruxWindow(HINSTANCE _hInstance, const MCruxWindowConfiguration * _config)
	: hInstance(_hInstance),
	  hWnd(NULL),
	  config(_config),
	  webView(),
	  pluginManager(NULL),
	  webUIDelegate(),
	  webFrameLoadDelegate(),
	  delegatesHandler()
{
	// creating the pluginManager
	list <wstring> plugins;
	plugins.push_back(TEXT("FileSystem"));
	plugins.push_back(TEXT("SQLiteDatabase"));
	if(!pluginManager)
	{
		pluginManager = new MCruxPluginManager(plugins);
	}

	delegatesHandler.setPluginManager(pluginManager);

	hWnd = CreateWindow(MCruxWindow::getWindowClassName(),
		config->getWindowTitle(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!webView.createWebView())
	{
		::MessageBoxA(0, "createWebView Failed", "error", MB_OK);
		return;
	}

	if(!webView.setWebUIDelegate(&webUIDelegate))
	{
		::MessageBoxA(0, "setWebUIDelegate Failed", "error", MB_OK);
		return;
	}
	webUIDelegate.setUIHandler(&delegatesHandler);

	if(!webView.setFrameLoadDelegate(&webFrameLoadDelegate))
	{
		::MessageBoxA(0, "setFrameLoadDelegate Failed", "error", MB_OK);
		return;
	}
	webFrameLoadDelegate.setFrameLoadHandler(&delegatesHandler);

	wstring defaultPage = _T("<html><head><title>Hi !</title>\n <script type=\"text/javascript\">\n //<!-- \n alert(\"Just wanted to say you Hi MCrux User !\"); \n mcrux.someFunction(); \n //-->\n </script></head><body><h1>hi!</h1></body></html>");
	//if (!webView.loadPageInWindow(hWnd, defaultPage))
	if (!webView.loadURLInWindow(hWnd, config->getURL()))
	{
		::MessageBoxA(0, "Loadpageinwindow Failed", "error", MB_OK);
		return;
	}
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

