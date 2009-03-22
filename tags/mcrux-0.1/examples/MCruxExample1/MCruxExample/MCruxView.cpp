#include "StdAfx.h"
#include "MCruxView.h"

#include "Resources.h"
#include "MCruxException.h"


MCruxView::MCruxView(HWND hContainerWindow, AddressBar * _addressBar)
: gViewWindow(0),
  gWebView(0),
  gWebHost(0),
  addressBar(_addressBar)
{
    HRESULT hr = CoCreateInstance(CLSID_WebView, 0, CLSCTX_ALL, IID_IWebView, (void**)&gWebView);
    if (FAILED(hr))
	{
		throw MCruxException("WebView creation falied.");
	}

	gWebHost = new MCruxWebHost(this, addressBar);
    gWebHost->AddRef();
    hr = gWebView->setFrameLoadDelegate(gWebHost);
    if (FAILED(hr))
	{
		throw MCruxException("WebView::setFrameLoadDelegate failed.");
	}

    hr = gWebView->setHostWindow((OLE_HANDLE) hContainerWindow);
    if (FAILED(hr))
	{
		throw MCruxException("WebView::setHostWindow failed.");
	}

    RECT clientRect;
    GetClientRect(hContainerWindow, &clientRect);
    hr = gWebView->initWithFrame(clientRect, 0, 0);
    if (FAILED(hr))
	{
		throw MCruxException("WebView::initWithFrame failed.");
	}

    IWebFrame* frame;
    hr = gWebView->mainFrame(&frame);
    if (FAILED(hr))
	{
		throw MCruxException("WebView::mainFrame failed.");
	}
 
    static BSTR defaultHTML = 0;
    if (!defaultHTML)
	{
		defaultHTML = SysAllocString(TEXT("<html><head><title>meta http-equiv - Redirect</title><meta http-equiv=\"REFRESH\" content=\"4;url=http://www.google.com/\" /></head><body><h1>Goodbye cruel world!</h1><p>Using meta http-equiv to end my life in 4 seconds...</p></body></html>"));
		//defaultHTML = SysAllocString(TEXT("<html><head><title>Javascript redirect - Redirect</title>\n <script type=\"text/javascript\">\n <!-- \n function euthanasia ()\n {\n window.location = \"http://www.google.com/\" \n }\n  setTimeout(euthanasia, 4000);\n  //-->\n </script></head><body><h1>Goodbye cruel world!</h1><p>Using Javascript to end my life in 4 seconds...</p></body></html>"));
		//defaultHTML = SysAllocString(TEXT("<html><head><title>Hyperlink redirect - Redirect</title></head><body><h1>Goodbye cruel world!</h1><p><a href=\"http://www.google.com/\">Using Javascript to end my life by clicking here.</a></p></body></html>"));
	}
    frame->loadHTMLString(defaultHTML, 0);
    frame->Release();

    IWebViewPrivate* viewExt;
    hr = gWebView->QueryInterface(IID_IWebViewPrivate, (void**)&viewExt);
    if (FAILED(hr))
	{
		throw MCruxException("WebView::QueryInterface for IWebViewPrivate failed.");
	}
    hr = viewExt->viewWindow((OLE_HANDLE*) &gViewWindow);
    viewExt->Release();
    if (FAILED(hr) || !gViewWindow)
	{
		throw MCruxException("IWebViewPrivate::ViewWindow failed");
	}
}

MCruxView::~MCruxView()
{
	if(gWebView)
	{
		gWebView->Release();
	}
}


void MCruxView::resize(RECT rcClient)
{
    MoveWindow(gViewWindow, 0, URLBAR_HEIGHT, rcClient.right, rcClient.bottom - URLBAR_HEIGHT, TRUE);
}


void MCruxView::showWindow(int nCmdShow)
{
	ShowWindow(gViewWindow, nCmdShow);
    UpdateWindow(gViewWindow);
}

void MCruxView::loadURL(BSTR urlBStr)
{
    IWebFrame* frame = 0;
    IWebMutableURLRequest* request = 0;
    BSTR methodBStr = SysAllocString(TEXT("GET"));

	if (urlBStr
		&& urlBStr[0]
		&& (PathFileExists(urlBStr) || PathIsUNC(urlBStr)))
	{
        TCHAR fileURL[INTERNET_MAX_URL_LENGTH];
        DWORD fileURLLength = sizeof(fileURL)/sizeof(fileURL[0]);
        if (SUCCEEDED(UrlCreateFromPath(urlBStr, fileURL, &fileURLLength, 0)))
		{
            urlBStr = fileURL;
		}
    }

    HRESULT hr = gWebView->mainFrame(&frame);
    if (FAILED(hr))
	{
        goto exit;
	}

    hr = CoCreateInstance(CLSID_WebMutableURLRequest, 0, CLSCTX_ALL, IID_IWebMutableURLRequest, (void**)&request);
    if (FAILED(hr))
        goto exit;

    hr = request->initWithURL(urlBStr, WebURLRequestUseProtocolCachePolicy, 30);
    if (FAILED(hr))
        goto exit;

    hr = request->setHTTPMethod(methodBStr);
    if (FAILED(hr))
        goto exit;

    hr = frame->loadRequest(request);
    if (FAILED(hr))
        goto exit;

    SetFocus(gViewWindow);

exit:
    if (frame)
        frame->Release();
    if (request)
        request->Release();
}

BSTR MCruxView::getFrameURL(IWebView* webView)
{
    IWebFrame* mainFrame = 0;
    IWebDataSource* dataSource = 0;
    IWebMutableURLRequest* request = 0;
    BSTR frameURL = 0;

    HRESULT hr = webView->mainFrame(&mainFrame);
	if (SUCCEEDED(hr))
	{
		hr = mainFrame->dataSource(&dataSource);
		if (FAILED(hr) || !dataSource)
			hr = mainFrame->provisionalDataSource(&dataSource);
		if (FAILED(hr) || !dataSource)
			goto exit;

		hr = dataSource->request(&request);
		if (FAILED(hr) || !request)
			goto exit;

		hr = request->mainDocumentURL(&frameURL);
		if (FAILED(hr))
			goto exit;
        mainFrame->Release();
	}
exit:
    if (dataSource)
        dataSource->Release();
    if (request)
        request->Release();
	return frameURL;
}