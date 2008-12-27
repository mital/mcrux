#pragma once

#include "WebKit.h"
#include "MCruxWebHost.h"
#include "AddressBar.h"


class MCruxView
{
	HWND gViewWindow;
	IWebView* gWebView;
	MCruxWebHost* gWebHost;
	AddressBar* addressBar;

public:
	MCruxView(HWND hContainerWindow, AddressBar * _addressBar);

	~MCruxView();

	void resize(RECT rcClient);

	void showWindow(int nCmdShow);

	void loadURL(BSTR urlBStr);

	BSTR getFrameURL(IWebView* webView);
};
