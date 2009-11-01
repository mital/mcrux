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

#ifndef _MCRUXWIN32WINDOW_H_
#define _MCRUXWIN32WINDOW_H_

#include <abstract/MCruxWindow.h>
#include <window/MCruxWindowConfiguration.h>

#include "MCruxWebView.h"
#include "plugin/MCruxPluginManager.h"
#include "delegates/MCruxDelegatesHandler.h"
#include "delegates/MCruxWebUIDelegate.h"
#include "delegates/MCruxWebFrameLoadDelegate.h"

class MCruxWindowManager;

class MCruxWin32Window : public MCruxWindow
{
private:
	HINSTANCE hInstance;
	HWND hWnd;

	// webView
	MCruxWebView webView;

	// delegates
	MCruxWebUIDelegate webUIDelegate;
	MCruxWebFrameLoadDelegate webFrameLoadDelegate;
	MCruxDelegatesHandler delegatesHandler;

public:

	MCruxWin32Window(const MCruxWindowConfiguration * _config,
		MCruxPluginManager * pluginManager,
		MCruxWindowManager * windowManager);
	~MCruxWin32Window();

	virtual int ShowWindow() const;
	virtual int HideWindow() const;
	virtual int UpdateWindow() const;
	virtual void resize() const;

	MCruxWebView * getMCruxWebView();
	static void initWindowClass(HINSTANCE hInstance);
	static void unInitWindowClass(HINSTANCE hInstance);
	static MCruxWin32Window * getMCruxWindowFrom(IWebView * webView);

private:

	static TCHAR * getWindowClassName();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static map<HWND, MCruxWin32Window *> mcruxWindows;
	static map<IWebView *, MCruxWin32Window *> mcruxWindowsFromViews;

};

#endif // _MCRUXWIN32WINDOW_H_