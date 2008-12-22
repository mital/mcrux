#include "StdAfx.h"
#include "MCruxObject.h"

CMCruxObject::CMCruxObject()
: webView(),
  webUIDelegate(),
  webFrameLoadDelegate(),
  delegatesHandler()
{
}

CMCruxObject::~CMCruxObject()
{
}


STDMETHODIMP CMCruxObject::createWebView(LONG* hParent, BSTR* page)
{
	::MessageBoxA(0, "CMCruxObject::createWebView called", "test", MB_OK);
	if (!webView.createWebView())
	{
		return E_FAIL;
	}

	if(!webView.setWebUIDelegate(&webUIDelegate))
	{
		return E_FAIL;
	}
	webUIDelegate.setUIHandler(&delegatesHandler);

	if(!webView.setFrameLoadDelegate(&webFrameLoadDelegate))
	{
		return E_FAIL;
	}
	webFrameLoadDelegate.setFrameLoadHandler(&delegatesHandler);

	if (!webView.loadPageInWindow((HWND) LongToHandle(*hParent), *page))
	{
		return E_FAIL;
	}
	return S_OK;
}
