#pragma once

#include <iostream>

using namespace std;

#include <WebKit.h>

#include "delegates/MCruxWebUIDelegate.h"
#include "delegates/MCruxFrameLoadDelegate.h"


class MCruxWebView
{
	IWebView* webView;
	HWND hWebViewWindow;

	bool initWithHostWindow(HWND hWnd) const;
	bool loadPage(const wstring & defaultPageText) const;
	bool storeViewWindowHandle();

public:
	MCruxWebView();
	~MCruxWebView();

	bool createWebView();
	bool setFrameLoadDelegate(MCruxFrameLoadDelegate * frameLoadDelegate);
	bool setWebUIDelegate(MCruxWebUIDelegate * webUIDelegate);
	bool loadPageInWindow(HWND hWnd, const wstring & defaultPageText);
};
