#pragma once

#include <map>
#include <iostream>

using namespace std;

#include "MCruxWindowConfiguration.h"
#include "MCruxWebView.h"

#include "plugin/MCruxPluginManager.h"

#include "delegates/MCruxDelegatesHandler.h"
#include "delegates/MCruxWebUIDelegate.h"
#include "delegates/MCruxWebFrameLoadDelegate.h"


class MCruxWindow
{
	HINSTANCE hInstance;
	HWND hWnd;
	const MCruxWindowConfiguration * config;

	// webView
	MCruxWebView webView;

	//// plugin Manager
	MCruxPluginManager * pluginManager;

	// delegates
	MCruxWebUIDelegate webUIDelegate;
	MCruxWebFrameLoadDelegate webFrameLoadDelegate;
	MCruxDelegatesHandler delegatesHandler;

	static TCHAR * getWindowClassName();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static map<HWND, MCruxWindow *> mcruxWindows;

public:
	MCruxWindow(HINSTANCE _hInstance, const MCruxWindowConfiguration * _config);
	~MCruxWindow();

	int ShowWindow() const;
	int HideWindow() const;
	int UpdateWindow() const;
	void resize() const;


	static void initWindowClass(HINSTANCE hInstance);
	static void unInitWindowClass(HINSTANCE hInstance);
};
