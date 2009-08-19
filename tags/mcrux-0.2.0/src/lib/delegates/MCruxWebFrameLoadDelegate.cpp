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
#include "MCruxWebFrameLoadDelegate.h"

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
//#include <JavaScriptCore/RetainPtr.h>

MCruxWebFrameLoadDelegate::MCruxWebFrameLoadDelegate()
: m_refCount(1),
  handler(NULL)
{
}

MCruxWebFrameLoadDelegate::~MCruxWebFrameLoadDelegate()
{
}


void MCruxWebFrameLoadDelegate::setFrameLoadHandler(IMCruxWebFrameLoadDelegateHandler* _handler)
{
	handler = _handler;
}


HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::QueryInterface(REFIID riid, void** ppvObject)
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

ULONG STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::AddRef(void)
{
    return ++m_refCount;
}

ULONG STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::Release(void)
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}


HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didStartProvisionalLoadForFrame( 
        IWebView* webView, IWebFrame* frame)
{
	return handler->didStartProvisionalLoadForFrame(webView, frame);
}
    
HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didReceiveServerRedirectForProvisionalLoadForFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return handler->didReceiveServerRedirectForProvisionalLoadForFrame(webView, frame);
}
   
HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didFailProvisionalLoadWithError( 
        IWebView *webView,
        IWebError *error,
        IWebFrame *frame)
{
	return handler->didFailProvisionalLoadWithError(webView, error, frame);
}

    
HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didCommitLoadForFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return handler->didCommitLoadForFrame(webView, frame);
}
    
HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didReceiveTitle( 
        IWebView *webView,
        BSTR title,
        IWebFrame *frame)
{
	return handler->didReceiveTitle(webView, title, frame);
}

    
HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didReceiveIcon( 
        IWebView *webView,
        OLE_HANDLE hBitmap,
        IWebFrame *frame)
{
	return handler->didReceiveIcon(webView, hBitmap, frame);
}
    
HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didFinishLoadForFrame( 
        IWebView* webView,
        IWebFrame* frame)
{
	return handler->didFinishLoadForFrame(webView, frame);
}

    
HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didFailLoadWithError( 
        IWebView *webView,
        IWebError *error,
        IWebFrame *forFrame)
{
	return handler->didFailLoadWithError(webView, error, forFrame);
}
    
HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didChangeLocationWithinPageForFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return handler->didChangeLocationWithinPageForFrame(webView, frame);
}


HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::willPerformClientRedirectToURL( 
        IWebView *webView,
        BSTR url,
        double delaySeconds,
        DATE fireDate,
        IWebFrame *frame)
{
	return handler->willPerformClientRedirectToURL(webView, url, delaySeconds, fireDate, frame);
}


HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didCancelClientRedirectForFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return handler->didCancelClientRedirectForFrame(webView, frame);
}


HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::willCloseFrame( 
        IWebView *webView,
        IWebFrame *frame)
{
	return handler->willCloseFrame(webView, frame);
}


HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::windowScriptObjectAvailable( 
        IWebView *webView,
        JSContextRef context,
        JSObjectRef windowScriptObject)
{
	return handler->windowScriptObjectAvailable(webView, context, windowScriptObject);
}


HRESULT STDMETHODCALLTYPE MCruxWebFrameLoadDelegate::didClearWindowObject(
        IWebView *webView,
        JSContextRef context,
        JSObjectRef windowScriptObject,
        IWebFrame *frame)
{
	return handler->didClearWindowObject(webView, context, windowScriptObject, frame);
}
