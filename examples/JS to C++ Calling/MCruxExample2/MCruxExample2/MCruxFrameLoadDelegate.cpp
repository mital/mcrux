#include "StdAfx.h"
#include "MCruxFrameLoadDelegate.h"

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>

MCruxFrameLoadDelegate::MCruxFrameLoadDelegate()
: m_refCount(1) 
{
}

MCruxFrameLoadDelegate::~MCruxFrameLoadDelegate()
{
}

HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::QueryInterface(REFIID riid, void** ppvObject)
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

ULONG STDMETHODCALLTYPE MCruxFrameLoadDelegate::AddRef(void)
{
    return ++m_refCount;
}

ULONG STDMETHODCALLTYPE MCruxFrameLoadDelegate::Release(void)
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}


HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didStartProvisionalLoadForFrame( 
        IWebView* webView, IWebFrame* frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didReceiveServerRedirectForProvisionalLoadForFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return S_OK;
}
   
HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didFailProvisionalLoadWithError( 
        IWebView *webView,
        IWebError *error,
        IWebFrame *frame)
{
	return S_OK;
}

    
HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didCommitLoadForFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didReceiveTitle( 
        IWebView *webView,
        BSTR title,
        IWebFrame *frame)
{
	return S_OK;
}

    
HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didReceiveIcon( 
        IWebView *webView,
        OLE_HANDLE hBitmap,
        IWebFrame *frame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didFinishLoadForFrame( 
        IWebView* webView,
        IWebFrame* frame)
{
	return S_OK;
}

    
HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didFailLoadWithError( 
        IWebView *webView,
        IWebError *error,
        IWebFrame *forFrame)
{
	return S_OK;
}
    
HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didChangeLocationWithinPageForFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::willPerformClientRedirectToURL( 
        IWebView *webView,
        BSTR url,
        double delaySeconds,
        DATE fireDate,
        IWebFrame *frame)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::didCancelClientRedirectForFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::willCloseFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE MCruxFrameLoadDelegate::windowScriptObjectAvailable( 
        IWebView *webView,
        JSContextRef context,
        JSObjectRef windowScriptObject)
{
	
	JSObjectRef obj = mcrux.createJSWrapper(context);
	JSObjectRef globalObject = JSContextGetGlobalObject(context);
	JSStringRef fnPropName= JSStringCreateWithUTF8CString("mcrux");
	//JSChar name = JSChar("mcrux");
	JSObjectSetProperty(context, globalObject,
		fnPropName,
		obj, 0, 0);
	
	//JSValueRef fnCtorValue = JSObjectGetProperty(context, globalObject,
	//	fnPropName, 0);
	//JSStringRelease(fnPropName);
	//if (!fnCtorValue)
	//{
	//	return JSValueMakeUndefined(jsContext);

	//	context JSContextGetGlobalObject
	//}
  	::MessageBoxA(0, "windowscript object avalilable called", "test", MB_OK);
	return S_OK;
}

