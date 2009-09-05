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

#ifndef _MCRUXDELEGATEHANDLER_H_
#define _MCRUXDELEGATEHANDLER_H_

#include "plugin/MCruxPluginManager.h"
#include "IMCruxWebUIDelegateHandler.h"
#include "IMCruxWebFrameLoadDelegateHandler.h"

class MCruxWindowManager;

class MCruxDelegatesHandler
	: public IMCruxWebUIDelegateHandler,
	public IMCruxWebFrameLoadDelegateHandler
{
	MCruxPluginManager * pluginManager;
	MCruxWindowManager * windowManager;
public:

	MCruxDelegatesHandler();
	virtual ~MCruxDelegatesHandler();

	HRESULT STDMETHODCALLTYPE runJavaScriptAlertPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message);

	HRESULT STDMETHODCALLTYPE didClearWindowObject( 
        /* [in] */ IWebView *webView,
        /* [in] */ JSContextRef context,
        /* [in] */ JSObjectRef windowScriptObject,
        /* [in] */ IWebFrame *frame);

	HRESULT STDMETHODCALLTYPE createWebViewWithRequest( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebURLRequest *request,
		/* [retval][out] */ IWebView **newWebView);

	HRESULT STDMETHODCALLTYPE webViewShow(
		/* [in] */ IWebView *sender);

	void setPluginManager(MCruxPluginManager * _pluginManager);

	void setWindowManager(MCruxWindowManager * _windowManager);
};

#endif // _MCRUXDELEGATEHANDLER_H_