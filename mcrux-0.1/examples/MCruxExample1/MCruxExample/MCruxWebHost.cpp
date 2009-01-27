#include "StdAfx.h"
#include "MCruxWebHost.h"
#include "MCruxView.h"


MCruxWebHost::MCruxWebHost(MCruxView * _mcruxView, AddressBar * _addressBar)
: m_refCount(1),
  mcruxView(_mcruxView),
  addressBar(_addressBar)
{
}


MCruxWebHost::~MCruxWebHost()
{
}

HRESULT STDMETHODCALLTYPE MCruxWebHost::QueryInterface(REFIID riid, void** ppvObject)
{
    *ppvObject = 0;
    if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebFrameLoadDelegate*>(this);
    else if (IsEqualGUID(riid, IID_IWebFrameLoadDelegate))
        *ppvObject = static_cast<IWebFrameLoadDelegate*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG STDMETHODCALLTYPE MCruxWebHost::AddRef(void)
{
    return ++m_refCount;
}

ULONG STDMETHODCALLTYPE MCruxWebHost::Release(void)
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebFrameLoadDelegate
HRESULT STDMETHODCALLTYPE MCruxWebHost::didStartProvisionalLoadForFrame(IWebView* webView, IWebFrame* frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didReceiveServerRedirectForProvisionalLoadForFrame(IWebView *webView, IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didFailProvisionalLoadWithError(IWebView *webView, IWebError *error, IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didCommitLoadForFrame(IWebView *webView, IWebFrame *frame)
{ 
	return updateAddressBar(webView);
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didReceiveTitle(IWebView *webView, BSTR title, IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didReceiveIcon(IWebView *webView, OLE_HANDLE hBitmap, IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didFinishLoadForFrame(IWebView* webView, IWebFrame* frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didFailLoadWithError(IWebView *webView, IWebError *error, IWebFrame *forFrame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didChangeLocationWithinPageForFrame(IWebView *webView, IWebFrame *frame)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE MCruxWebHost::willPerformClientRedirectToURL(
	IWebView *webView,
    BSTR url,
    double delaySeconds,
    DATE fireDate,
    IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::didCancelClientRedirectForFrame(IWebView *webView, IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::willCloseFrame(IWebView *webView, IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxWebHost::windowScriptObjectAvailable(
    IWebView *webView,
    JSContextRef context,
    JSObjectRef windowScriptObject)
{
	return S_OK;
}

HRESULT MCruxWebHost::updateAddressBar(IWebView* webView)
{
    BSTR frameURL = mcruxView->getFrameURL(webView);
	addressBar->setText(frameURL);
	//SendMessage(hURLBarWnd, (UINT)WM_SETTEXT, 0, (LPARAM)frameURL);

    //IWebFrame* mainFrame = 0;
    //IWebDataSource* dataSource = 0;
    //IWebMutableURLRequest* request = 0;
    //BSTR frameURL = 0;

    //HRESULT hr = S_OK;

    //hr = webView->mainFrame(&mainFrame);
    //if (FAILED(hr))
    //    goto exit;

    //hr = mainFrame->dataSource(&dataSource);
    //if (FAILED(hr) || !dataSource)
    //    hr = mainFrame->provisionalDataSource(&dataSource);
    //if (FAILED(hr) || !dataSource)
    //    goto exit;

    //hr = dataSource->request(&request);
    //if (FAILED(hr) || !request)
    //    goto exit;

    //hr = request->mainDocumentURL(&frameURL);
    //if (FAILED(hr))
    //    goto exit;


//exit:
//    if (mainFrame)
//        mainFrame->Release();
//    if (dataSource)
//        dataSource->Release();
//    if (request)
//        request->Release();
//    SysFreeString(frameURL);
    return 0;
}



