#include "StdAfx.h"
#include "MCruxWebView.h"

MCruxWebView::MCruxWebView()
: webView(NULL),
  hWebViewWindow(NULL)
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


bool MCruxWebView::setFrameLoadDelegate(MCruxFrameLoadDelegate * frameLoadDelegate)
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

bool MCruxWebView::initWithHostWindow(HWND hWnd) const
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