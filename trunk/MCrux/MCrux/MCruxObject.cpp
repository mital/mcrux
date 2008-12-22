#include "StdAfx.h"
#include "MCruxObject.h"

CMCruxObject::CMCruxObject()
{
}

CMCruxObject::~CMCruxObject()
{
}


STDMETHODIMP CMCruxObject::createWebView(LONG* hParent)
{
	::MessageBoxA(0, "CMCruxObject::createWebView called", "test", MB_OK);
	if (!webView.createWebView())
	{
		return E_FAIL;
	}

	if (!webView.loadPageInWindow((HWND) LongToHandle(*hParent), _T("<html><body>Hi</body></html>")))
	{
		return E_FAIL;
	}
	return S_OK;
}
