/**
 * copyright (C) 2008 Mital Vora. All rights reserved.
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

#ifndef _MCRUXWEBVIEW_H_
#define _MCRUXWEBVIEW_H_

#include <iostream>

using namespace std;

#ifdef WIN32
#include <WebKit/WebKit.h>

#include "delegates/MCruxWebUIDelegate.h"
#include "delegates/MCruxWebFrameLoadDelegate.h"

#else // for linux
#include <QtGui>

class QWebView;
class MCruxQTWindow;
#endif

class MCruxWebView
{
#ifdef WIN32
	HWND hParentWindow;
	IWebView* webView;
	HWND hWebViewWindow;
	const BSTR httpGetMethod;
	bool initWithHostWindow(HWND hWnd);

#else // for linux
  QWebView* webView;
  MCruxQTWindow * parentWindow;
#endif

	bool loadPage(const wstring & defaultPageText) const;
	bool storeViewWindowHandle();

public:
	MCruxWebView(
#ifndef WIN32 // for linux
      MCruxQTWindow * _parentWindow
#endif
      );
#ifndef WIN32 // for linux
	virtual
#endif
    ~MCruxWebView();

	bool createWebView();
	bool navigateTo(const wstring & url);

#ifdef WIN32
	bool setFrameLoadDelegate(MCruxWebFrameLoadDelegate * frameLoadDelegate);
	bool setWebUIDelegate(MCruxWebUIDelegate * webUIDelegate);

	void resizeSubView() const;
	bool loadPageInWindow(HWND hWnd, const wstring & defaultPageText);
	bool loadURLInWindow(HWND hWnd, const wstring & url);
	bool loadURLRequestInWindow(HWND hWnd, IWebURLRequest *request);

	bool navigateTo(IWebURLRequest *request);
	IWebView * getWebView();

#else // for linux

  QWebView * getWebView() const
  {
    return webView;
  }
#endif
};

#endif // _MCRUXWEBVIEW_H_
