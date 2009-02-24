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

#include "StdAfx.h"
#include <shlwapi.h>
#include <wininet.h>

#include "MCruxWebView.h"


MCruxWebView::MCruxWebView()
: hParentWindow(NULL),
  webView(NULL),
  hWebViewWindow(NULL),
  httpGetMethod(SysAllocString(TEXT("GET")))
{
}

MCruxWebView::~MCruxWebView()
{
}

bool MCruxWebView::createWebView()
{
	if(webView)
	{
		webView->Release();
		webView = NULL;
	}
	hWebViewWindow = NULL;

	HRESULT hr = CoCreateInstance(CLSID_WebView, 0, CLSCTX_ALL, IID_IWebView, (void**)&webView);
	if (SUCCEEDED(hr))
	{
      return true;
	}
	return false;
}


bool MCruxWebView::setFrameLoadDelegate(MCruxWebFrameLoadDelegate * frameLoadDelegate)
{
	if(webView)
	{
		HRESULT hr = webView->setFrameLoadDelegate(frameLoadDelegate);
		if (SUCCEEDED(hr))
		{
			return true;
		}
	}
	return false;
}

bool MCruxWebView::setWebUIDelegate(MCruxWebUIDelegate * webUIDelegate)
{
	if(webView)
	{
		HRESULT hr = webView->setUIDelegate(webUIDelegate);
		if(SUCCEEDED(hr))
		{
			return true;
		}
	}
	return false;
}

bool MCruxWebView::initWithHostWindow(HWND hWnd)
{
	if(webView)
	{
		HRESULT hr = webView->setHostWindow((OLE_HANDLE) HandleToLong(hWnd));
		if (SUCCEEDED(hr))
		{
			RECT clientRect;
			GetClientRect(hWnd, &clientRect);
			hr = webView->initWithFrame(clientRect, 0, 0);
			if (SUCCEEDED(hr))
			{
				hParentWindow = hWnd;
				return true;
			}
		}
	}
	return false;
}

bool MCruxWebView::loadPage(const wstring & defaultPageText) const
{
	if(webView)
	{
		IWebFrame* frame;
		HRESULT hr = webView->mainFrame(&frame);
		if (SUCCEEDED(hr))
		{
			BSTR page = SysAllocString(defaultPageText.c_str());
			frame->loadHTMLString(page, 0);
			frame->Release();
			return true;
		}
	}
	return false;
}


bool MCruxWebView::storeViewWindowHandle()
{
	if(webView)
	{
		IWebViewPrivate* viewExt;
		HRESULT hr = webView->QueryInterface(IID_IWebViewPrivate, (void**)&viewExt);
		if (SUCCEEDED(hr))
		{
			hr = viewExt->viewWindow((OLE_HANDLE*) &hWebViewWindow);
			viewExt->Release();
			if (SUCCEEDED(hr))
			{
				return true;
			}
		}

	}
	return false;
}

void MCruxWebView::resizeSubView() const
{
    RECT rcClient;
    GetClientRect(hParentWindow, &rcClient);
	MoveWindow(hWebViewWindow, 0, 0, rcClient.right, rcClient.bottom, TRUE);
}


bool MCruxWebView::loadPageInWindow(HWND hWnd, const wstring & defaultPageText)
{
	if(initWithHostWindow(hWnd)
		&& loadPage(defaultPageText)
		&& storeViewWindowHandle())
	{
		return true;
	}
	return false;
}

bool MCruxWebView::loadURLInWindow(HWND hWnd, const wstring & url)
{
	if(initWithHostWindow(hWnd)
		&& navigateTo(url)
		&& storeViewWindowHandle())
	{
		return true;
	}
	return false;
}

bool MCruxWebView::navigateTo(const wstring & url)
{
	wstring navigateURL = url;
	IWebFrame* frame = 0;
	IWebMutableURLRequest* request = 0;

	if ((PathFileExists(navigateURL.c_str()) || PathIsUNC(navigateURL.c_str())))
	{
		TCHAR fileURL[INTERNET_MAX_URL_LENGTH];
		DWORD fileURLLength = sizeof(fileURL)/sizeof(fileURL[0]);
		if (SUCCEEDED(UrlCreateFromPath(navigateURL.c_str(), fileURL, &fileURLLength, 0)))
		{
			wstring wfileURL = fileURL;
			navigateURL = wfileURL;
		}
	}

	HRESULT hr = webView->mainFrame(&frame);
	if (FAILED(hr))
		goto exit;

	hr = CoCreateInstance(CLSID_WebMutableURLRequest,
		0,
		CLSCTX_ALL,
		IID_IWebMutableURLRequest,
		(void**)&request);
	if (FAILED(hr))
		goto exit;

	hr = request->initWithURL(::SysAllocString(navigateURL.c_str()), WebURLRequestUseProtocolCachePolicy, 0);
	if (FAILED(hr))
		goto exit;

	hr = request->setHTTPMethod(httpGetMethod);
	if (FAILED(hr))
		goto exit;

	hr = frame->loadRequest(request);
	if (FAILED(hr))
		goto exit;

	SetFocus(hWebViewWindow);

exit:
	if (frame)
		frame->Release();
	if (request)
		request->Release();
	return true;
}

IWebView * MCruxWebView::getWebView()
{
	return webView;
}