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

#ifndef _MCRUXWINDOW_H_
#define _MCRUXWINDOW_H_

#include <map>
#include <iostream>

using namespace std;

#include "MCruxWindowConfiguration.h"
#include "MCruxWebView.h"

#include "plugin/MCruxPluginManager.h"

#include "delegates/MCruxDelegatesHandler.h"
#include "delegates/MCruxWebUIDelegate.h"
#include "delegates/MCruxWebFrameLoadDelegate.h"

class MCruxWindowManager;

class MCruxWindow
{
	HINSTANCE hInstance;
	HWND hWnd;
	const MCruxWindowConfiguration * config;

	// webView
	MCruxWebView webView;

	// delegates
	MCruxWebUIDelegate webUIDelegate;
	MCruxWebFrameLoadDelegate webFrameLoadDelegate;
	MCruxDelegatesHandler delegatesHandler;

	static TCHAR * getWindowClassName();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static map<HWND, MCruxWindow *> mcruxWindows;
	static map<IWebView *, MCruxWindow *> mcruxWindowsFromViews;

public:
	MCruxWindow(const MCruxWindowConfiguration * _config,
		MCruxPluginManager * pluginManager,
		MCruxWindowManager * windowManager);
	~MCruxWindow();

	int ShowWindow() const;
	int HideWindow() const;
	int UpdateWindow() const;
	void resize() const;
	MCruxWebView * getMCruxWebView();

	static void initWindowClass(HINSTANCE hInstance);
	static void unInitWindowClass(HINSTANCE hInstance);
	static MCruxWindow * getMCruxWindowFrom(IWebView * webView);
};

#endif // _MCRUXWINDOW_H_