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

#pragma once

#include "plugin/MCruxPluginManager.h"
#include "IMCruxWebUIDelegateHandler.h"
#include "IMCruxWebFrameLoadDelegateHandler.h"

class MCruxDelegatesHandler
	: public IMCruxWebUIDelegateHandler,
	public IMCruxWebFrameLoadDelegateHandler
{
	MCruxPluginManager * pluginManager;
public:

	MCruxDelegatesHandler();
	virtual ~MCruxDelegatesHandler();

	HRESULT STDMETHODCALLTYPE runJavaScriptAlertPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message);

	HRESULT STDMETHODCALLTYPE windowScriptObjectAvailable( 
		/* [in] */ IWebView *webView,
		/* [in] */ JSContextRef context,
		/* [in] */ JSObjectRef windowScriptObject);

	void setPluginManager(MCruxPluginManager * _pluginManager);
};