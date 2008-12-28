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
