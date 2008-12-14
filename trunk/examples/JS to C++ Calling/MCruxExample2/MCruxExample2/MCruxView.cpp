#include "StdAfx.h"

#include <wininet.h>
#include <shlwapi.h>

#include "MCruxView.h"
#include "MCruxException.h"

MCruxView::MCruxView(HWND hWnd)
: webView(NULL),
  mcruxFrameLoadDelegate(NULL),
  mcruxWebUIDelegate(NULL),
  viewWindow(NULL),
  methodBStr(SysAllocString(TEXT("GET")))

{
	if(createWebView())
	{
		if(setFrameLoadDelegate())
		{
			if (initWithHostWindow(hWnd))
			{
				if(loadDefaultHTML())
				{
					if(!storeViewWindowHandle())
					{
						throw MCruxException("storeViewWindowHandle falied");
					}
				}
				else
				{
					throw MCruxException("loadDefaultHTML falied");
				}
			}
			else
			{
				throw MCruxException("initWithHostWindow falied");
			}
		}
		else
		{
			throw MCruxException("setFrameLoadDelegate falied");
		}
	}
	else
	{
		throw MCruxException("createWebView falied");
	}
}

MCruxView::~MCruxView()
{
}


bool MCruxView::createWebView()
{
	HRESULT hr = CoCreateInstance(CLSID_WebView, 0, CLSCTX_ALL, IID_IWebView, (void**)&webView);
	if (SUCCEEDED(hr))
	{
      return true;
	}
	return false;
}

bool MCruxView::setFrameLoadDelegate()
{
	mcruxFrameLoadDelegate = new MCruxFrameLoadDelegate();
	mcruxFrameLoadDelegate->AddRef();
	HRESULT hr = webView->setFrameLoadDelegate(mcruxFrameLoadDelegate);
	if (FAILED(hr))
	{
		return false;
	}
	mcruxWebUIDelegate = new MCruxWebUIDelegate();
	mcruxWebUIDelegate->AddRef();
	hr = webView->setUIDelegate(mcruxWebUIDelegate);
	if(FAILED(hr))
	{
		return false;
	}
	return true;
}

bool MCruxView::initWithHostWindow(HWND hWnd)
{
	HRESULT hr = webView->setHostWindow((OLE_HANDLE) hWnd);
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
	return false;
}

bool MCruxView::loadDefaultHTML() const
{
	IWebFrame* frame;
	HRESULT hr = webView->mainFrame(&frame);
	if (SUCCEEDED(hr))
	{
		static BSTR defaultHTML = 0;
		if (!defaultHTML)
		{
			defaultHTML = SysAllocString(TEXT("<html><head><title>Mcrux Example2: JavaScript to C++ static calls</title>\n <script type=\"text/javascript\">\n //<!-- \n \n alert(\"Hello World!\"); \n var myString = \"My String In JavaScript\"; \n alert(mcrux); \n var ret = mcrux.someFunction(myString); \n alert(\"Hello World! after returned from someFunction()\"); \n alert(ret); \n  //-->\n </script></head><body><h1>hi!</h1></body></html>"));
		}
		frame->loadHTMLString(defaultHTML, 0);
		frame->Release();
		return true;
	}
	return false;
}

bool MCruxView::storeViewWindowHandle()
{
	IWebViewPrivate* viewExt;
	HRESULT hr = webView->QueryInterface(IID_IWebViewPrivate, (void**)&viewExt);
	if (FAILED(hr))
	{
		return false;
	}
	hr = viewExt->viewWindow((OLE_HANDLE*) &viewWindow);
	viewExt->Release();
	if (FAILED(hr) || !viewWindow)
	{
		return false;
	}
	return true;
}

HWND MCruxView::getViewWindow() const
{
	return viewWindow;
}

void MCruxView::loadURL(BSTR urlBStr)
{
    IWebFrame* frame = 0;
    IWebMutableURLRequest* request = 0;

    if (urlBStr && urlBStr[0] && (PathFileExists(urlBStr) || PathIsUNC(urlBStr)))
	{
        TCHAR fileURL[INTERNET_MAX_URL_LENGTH];
        DWORD fileURLLength = sizeof(fileURL)/sizeof(fileURL[0]);
        if (SUCCEEDED(UrlCreateFromPath(urlBStr, fileURL, &fileURLLength, 0)))
            urlBStr = fileURL;
    }

	//webView->windowScriptObject(

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

    hr = request->initWithURL(urlBStr, WebURLRequestUseProtocolCachePolicy, 0);
    if (FAILED(hr))
        goto exit;

    hr = request->setHTTPMethod(methodBStr);
    if (FAILED(hr))
        goto exit;

    hr = frame->loadRequest(request);
    if (FAILED(hr))
        goto exit;

    SetFocus(viewWindow);

exit:
    if (frame)
        frame->Release();
    if (request)
        request->Release();
}
