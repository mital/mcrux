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

#ifndef _IMCRUXWEBFRAMELOADDELEGATEHANDLER_H_
#define _IMCRUXWEBFRAMELOADDELEGATEHANDLER_H_

#ifdef WIN32
#include "../win32/stdafx.h"
#endif

#include <WebKit/WebKit.h>


class IMCruxWebFrameLoadDelegateHandler
{
public:
	IMCruxWebFrameLoadDelegateHandler() { }
	virtual ~IMCruxWebFrameLoadDelegateHandler() { }

    // IWebFrameLoadDelegate
    virtual HRESULT STDMETHODCALLTYPE didStartProvisionalLoadForFrame( 
        /* [in] */ IWebView* webView,
		/* [in] */ IWebFrame* frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didReceiveServerRedirectForProvisionalLoadForFrame( 
        /* [in] */ IWebView *webView,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didFailProvisionalLoadWithError( 
        /* [in] */ IWebView *webView,
        /* [in] */ IWebError *error,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didCommitLoadForFrame( 
        /* [in] */ IWebView *webView,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didReceiveTitle( 
        /* [in] */ IWebView *webView,
        /* [in] */ BSTR title,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didReceiveIcon( 
        /* [in] */ IWebView *webView,
        /* [in] */ OLE_HANDLE hBitmap,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didFinishLoadForFrame( 
        /* [in] */ IWebView* webView,
        /* [in] */ IWebFrame* frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didFailLoadWithError( 
        /* [in] */ IWebView *webView,
        /* [in] */ IWebError *error,
        /* [in] */ IWebFrame *forFrame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didChangeLocationWithinPageForFrame( 
        /* [in] */ IWebView *webView,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }

    virtual HRESULT STDMETHODCALLTYPE willPerformClientRedirectToURL( 
        /* [in] */ IWebView *webView,
        /* [in] */ BSTR url,
        /* [in] */ double delaySeconds,
        /* [in] */ DATE fireDate,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE didCancelClientRedirectForFrame( 
        /* [in] */ IWebView *webView,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual HRESULT STDMETHODCALLTYPE willCloseFrame( 
        /* [in] */ IWebView *webView,
        /* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
    
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE windowScriptObjectAvailable( 
        /* [in] */ IWebView *webView,
        /* [in] */ JSContextRef context,
        /* [in] */ JSObjectRef windowScriptObject) { return E_NOTIMPL; }

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE didClearWindowObject( 
        /* [in] */ IWebView *webView,
        /* [in] */ JSContextRef context,
        /* [in] */ JSObjectRef windowScriptObject,
		/* [in] */ IWebFrame *frame) { return E_NOTIMPL; }
};

#endif // _IMCRUXWEBFRAMELOADDELEGATEHANDLER_H_