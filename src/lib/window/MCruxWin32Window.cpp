/**
 * copyright (C) 2009 Mital Vora. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of MCrux nor the names of its contributors may be 
 *     used to endorse or promote products derived from this software 
 *     without specific prior written permission.
 *
 * @author: Mital Vora.
 **/
#include "Resource.h"
#include <tchar.h>

#include "MCruxWin32Window.h"

map<HWND, MCruxWin32Window *> MCruxWin32Window::mcruxWindows;
map<IWebView *, MCruxWin32Window *> MCruxWin32Window::mcruxWindowsFromViews;


MCruxWin32Window::MCruxWin32Window(const MCruxWindowConfiguration * _config,
						 MCruxPluginManager * pluginManager,
						 MCruxWindowManager * windowManager)
	: MCruxWindow(_config),
	  hInstance(GetModuleHandle(NULL)),
	  hWnd(NULL),
	  webView(),
	  webUIDelegate(),
	  webFrameLoadDelegate(),
	  delegatesHandler()
{
	hWnd = CreateWindow(MCruxWin32Window::getWindowClassName(),
		config->getWindowTitle().c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, config->getWidth(), config->getHeight(), NULL, NULL, hInstance, NULL);

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

	delegatesHandler.setPluginManager(pluginManager);
	delegatesHandler.setWindowManager(windowManager);

	IWebURLRequest * request = config->getRequest();
	if(request)
	{
		if(!webView.loadURLRequestInWindow(hWnd, request))
		{
			::MessageBoxA(0, "loadURLRequestInWindow Failed", "error", MB_OK);
			return;
		}
	}
	else
	{
		if (!webView.loadURLInWindow(hWnd, config->getURL()))
		{
			::MessageBoxA(0, "Loadpageinwindow Failed", "error", MB_OK);
			return;
		}
	}
	MCruxWin32Window::mcruxWindows[hWnd] = this;
	MCruxWin32Window::mcruxWindowsFromViews[webView.getWebView()] = this;
}


MCruxWin32Window::~MCruxWin32Window()
{
	if(MCruxWin32Window::mcruxWindows[hWnd])
	{
		MCruxWin32Window::mcruxWindows.erase(MCruxWin32Window::mcruxWindows.find(hWnd));
	}
	delete config;
}

int MCruxWin32Window::ShowWindow() const
{
	return ::ShowWindow(hWnd, SW_SHOW);
}


int MCruxWin32Window::HideWindow() const
{
	return ::ShowWindow(hWnd, SW_HIDE);
}


int MCruxWin32Window::UpdateWindow() const
{
	return ::UpdateWindow(hWnd);
}


void MCruxWin32Window::resize() const
{
	webView.resizeSubView();
}


TCHAR * MCruxWin32Window::getWindowClassName()
{
	static TCHAR windowClassName[MAX_LOADSTRING] = _T("MCruxWindowClass");
	return windowClassName;
}


void MCruxWin32Window::initWindowClass(HINSTANCE hInstance)
{
	static bool bInit = false;
	if (!bInit)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= MCruxWin32Window::WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MCRUX_ICON));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= MCruxWin32Window::getWindowClassName();
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		RegisterClassEx(&wcex);

		bInit = true;
	}
}


void MCruxWin32Window::unInitWindowClass(HINSTANCE hInstance)
{
	UnregisterClass(MCruxWin32Window::getWindowClassName(), hInstance);
}


LRESULT CALLBACK MCruxWin32Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
    case WM_SIZE:
		if(MCruxWin32Window::mcruxWindows[hWnd])
		{
			MCruxWin32Window::mcruxWindows[hWnd]->resize();
		}
        break; 
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

MCruxWebView * MCruxWin32Window::getMCruxWebView()
{
	return &webView;
}


MCruxWin32Window * MCruxWin32Window::getMCruxWindowFrom(IWebView * webView)
{
	return MCruxWin32Window::mcruxWindowsFromViews[webView];
}