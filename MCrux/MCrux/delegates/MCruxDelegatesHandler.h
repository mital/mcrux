#pragma once

#include "IMCruxWebUIDelegateHandler.h"
#include "IMCruxWebFrameLoadDelegateHandler.h"

class MCruxDelegatesHandler
	: public IMCruxWebUIDelegateHandler,
	public IMCruxWebFrameLoadDelegateHandler
{
public:

	MCruxDelegatesHandler();
	virtual ~MCruxDelegatesHandler();

	HRESULT STDMETHODCALLTYPE runJavaScriptAlertPanelWithMessage( 
		/* [in] */ IWebView *sender,
		/* [in] */ BSTR message);
};