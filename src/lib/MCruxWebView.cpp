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
#ifdef WIN32
#include <shlwapi.h>
#include <wininet.h>

#include <WebKit/WebKitCOMAPI.h>

#else // for linux

#include <QtWebKit/QWebView>
#include "window/MCruxQTWindow.h"
#endif

#include "MCruxWebView.h"


MCruxWebView::MCruxWebView(
#ifndef WIN32
    MCruxQTWindow * _parentWindow
#endif
    )
: webView(NULL)
#ifdef WIN32
  ,hParentWindow(NULL),
  hWebViewWindow(NULL),
  httpGetMethod(SysAllocString(TEXT("GET")))
#else // for linux
  ,parentWindow(_parentWindow)
#endif
{
}

MCruxWebView::~MCruxWebView()
{
}

bool MCruxWebView::createWebView()
{
#ifdef WIN32
  if(webView)
  {
    webView->Release();
    webView = NULL;
  }
  hWebViewWindow = NULL;

  HRESULT hr = WebKitCreateInstance(CLSID_WebView, 0, IID_IWebView, (void**)&webView);
  if (SUCCEEDED(hr))
  {
    return true;
  }
#else // for linux

  webView = new QWebView(parentWindow);
  parentWindow->setCentralWidget(webView);
  //webView->show();
#endif
  return false;
}


#ifdef WIN32
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
#endif

bool MCruxWebView::loadPage(const wstring & defaultPageText) const
{
#ifdef WIN32
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
#endif
  return false;
}


bool MCruxWebView::storeViewWindowHandle()
{
#ifdef WIN32
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
#endif
  return false;
}
#ifdef WIN32
void MCruxWebView::resizeSubView() const
{
  RECT rcClient;
  GetClientRect(hParentWindow, &rcClient);
  MoveWindow(hWebViewWindow, 0, 0, rcClient.right, rcClient.bottom, TRUE);
}
#endif



#ifdef WIN32
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

bool MCruxWebView::loadURLRequestInWindow(HWND hWnd, IWebURLRequest *request)
{
#ifdef WIN32
  if(initWithHostWindow(hWnd)
      && storeViewWindowHandle())
  {
    return true;
  }
#endif
  return false;
}
#endif

bool MCruxWebView::navigateTo(const wstring & url)
{
#ifdef WIN32
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

  hr = WebKitCreateInstance(CLSID_WebMutableURLRequest,
      0,
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
#else
  string strurl(url.begin(), url.end());
  webView->load(QUrl(strurl.c_str()));
#endif
  return true;
}


#ifdef WIN32
bool MCruxWebView::navigateTo(IWebURLRequest *request)
{
  IWebFrame* frame = 0;
  HRESULT hr = webView->mainFrame(&frame);
  if (SUCCEEDED(hr))
  {
    hr = frame->loadRequest(request);
    if (SUCCEEDED(hr))
    {
      SetFocus(hWebViewWindow);
      request->Release();
    }
    frame->Release();
    return true;
  }
  return false;
}

IWebView * MCruxWebView::getWebView()
{
  return webView;
}
#endif
