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

#include <stdafx.h>
#include <comdef.h>

#include "MCruxDelegatesHandler.h"
#include "windowsnative/MCruxWindowManager.h"

MCruxDelegatesHandler::MCruxDelegatesHandler()
	: pluginManager(NULL),
	windowManager(NULL)
{
}


MCruxDelegatesHandler::~MCruxDelegatesHandler()
{
}


HRESULT STDMETHODCALLTYPE MCruxDelegatesHandler::runJavaScriptAlertPanelWithMessage( 
		IWebView *sender, BSTR message)
{
	::MessageBoxA(0, (CHAR*)_bstr_t(message), "test", MB_OK);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE MCruxDelegatesHandler::windowScriptObjectAvailable( 
        IWebView *webView,
        JSContextRef context,
        JSObjectRef windowScriptObject)
{
	return pluginManager->injectPlugins(webView, context, windowScriptObject);
}


void MCruxDelegatesHandler::setPluginManager(MCruxPluginManager * _pluginManager)
{
	pluginManager = _pluginManager;
}

void MCruxDelegatesHandler::setWindowManager(MCruxWindowManager * _windowManager)
{
	windowManager = _windowManager;
}


HRESULT STDMETHODCALLTYPE MCruxDelegatesHandler::didClearWindowObject(
        IWebView *webView,
        JSContextRef context,
        JSObjectRef windowScriptObject,
        IWebFrame *frame)
{
	::MessageBoxA(0, "did clear", "test", MB_OK);
	return pluginManager->injectPlugins(webView, context, windowScriptObject);

	//return S_OK;
}

HRESULT STDMETHODCALLTYPE MCruxDelegatesHandler::createWebViewWithRequest( 
		/* [in] */ IWebView *sender,
		/* [in] */ IWebURLRequest *request,
		/* [retval][out] */ IWebView **newWebView)
{
	::MessageBoxA(0, "create webview with request called", "test", MB_OK);
	if(windowManager)
	{
		*newWebView = windowManager->createWindow(request);
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE MCruxDelegatesHandler::webViewShow(
		/* [in] */ IWebView *sender)
{
	//windowManager->showWindow(sender);
	return E_NOTIMPL;
}