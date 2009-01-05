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

#include "MCrux.h"
#include "Resource.h"
#include "MCruxWebView.h"
#include "MCruxPluginManager.h"

#include "delegates/MCruxDelegatesHandler.h"
#include "delegates/MCruxWebUIDelegate.h"
#include "delegates/MCruxWebFrameLoadDelegate.h"

class CMCruxObject
	: public IMCrux,
	  public CComObjectRootEx<CComSingleThreadModel>,
	  public CComCoClass<CMCruxObject, &CLSID_MCruxObject>
{
	// webView
	MCruxWebView webView;

	// plugin Manager
	MCruxPluginManager * pluginManager;

	// delegates
	MCruxWebUIDelegate webUIDelegate;
	MCruxWebFrameLoadDelegate webFrameLoadDelegate;
	MCruxDelegatesHandler delegatesHandler;

public:

	BEGIN_COM_MAP(CMCruxObject)
		COM_INTERFACE_ENTRY(IMCrux)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_MCRUXOBJECT)

	CMCruxObject();

	virtual ~CMCruxObject();

	virtual HRESULT STDMETHODCALLTYPE
		createWebView(LONG* hParent, BSTR* page);

	virtual HRESULT STDMETHODCALLTYPE
		navigateTo(BSTR* url);

};

OBJECT_ENTRY_AUTO(__uuidof(MCruxObject), CMCruxObject)
