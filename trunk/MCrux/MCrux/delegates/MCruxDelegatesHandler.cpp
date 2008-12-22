#include <stdafx.h>
#include <comdef.h>

#include "MCruxDelegatesHandler.h"

MCruxDelegatesHandler::MCruxDelegatesHandler()
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
