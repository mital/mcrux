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
#include "MCruxJSObject.h"
#include "MCruxPluginManager.h"


MCruxPluginManager::MCruxPluginManager(const list<string> extensionPluginNames)
{
	AddMCruxDefaultPlugins();
	AddExtensionPlugins(extensionPluginNames);
}

MCruxPluginManager::~MCruxPluginManager()
{
}


void MCruxPluginManager::AddMCruxDefaultPlugins()
{
	plugins.push_back(new CMCruxJSObject());
}

void MCruxPluginManager::AddExtensionPlugins(const list<string> extensionPluginNames)
{
	// TODO: search for the dlls from specific path and add those as extension plugins.
	// might have to take the path also from user so "const list<string>"  will be changed to "const list<pair<string, string> >"
}


HRESULT MCruxPluginManager::injectPlugins(IWebView *webView,
										  JSContextRef context,
										  JSObjectRef windowScriptObject)

{
	::MessageBoxA(0, "inject plugins called", "test", MB_OK);
	for(list<MCruxPluginClass *>::const_iterator
		oIter = plugins.begin();
		oIter != plugins.end();
	oIter++)
	{
		(*oIter)->injectPlugin(context);
	}

	return S_OK;
}