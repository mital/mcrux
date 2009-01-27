#pragma once

#include "MCruxFrameLoadDelegate.h"
#include "MCruxWebUIDelegate.h"


class MCruxView
{
	IWebView* webView;
	MCruxFrameLoadDelegate * mcruxFrameLoadDelegate;
	MCruxWebUIDelegate* mcruxWebUIDelegate;
	HWND viewWindow;
	BSTR methodBStr;

	bool createWebView();
	bool setFrameLoadDelegate();
	bool initWithHostWindow(HWND hWnd);
	bool loadDefaultHTML() const;
	bool storeViewWindowHandle();
public:

	MCruxView(HWND hWnd);
	~MCruxView();

	HWND getViewWindow() const;
	void loadURL(BSTR urlBStr);
};
