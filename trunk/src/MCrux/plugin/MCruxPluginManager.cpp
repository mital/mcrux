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
#include <JavaScriptCore/JSStringRef.h>

#include "windowsnative/MCruxWindow.h"

#include "MCruxJSObject.h"


MCruxPluginManager::MCruxPluginManager(const list<wstring> extensionPluginNames)
: mcruxObject(NULL)
{
	AddMCruxDefaultPlugins();
	AddExtensionPlugins(extensionPluginNames);
}

MCruxPluginManager::~MCruxPluginManager()
{
}


void MCruxPluginManager::AddMCruxDefaultPlugins()
{
	plugins.push_back(new MCruxJSObject());
}

bool MCruxPluginManager::AddPlugin(const wstring & pluginName)
{
	wstring pluginDll = TEXT("plugins/");
	pluginDll += pluginName;
	pluginDll += TEXT(".dll");
	HINSTANCE hHookDll = ::LoadLibrary(pluginDll.c_str());
	if( hHookDll==NULL || hHookDll == INVALID_HANDLE_VALUE)
	{
		//throw std::exception("Failed to load library");
		return false;
	}
	GetPluginFunctionPtr myFunction = (GetPluginFunctionPtr) ::GetProcAddress(hHookDll, "getMCruxPlugin");
	if (myFunction == NULL)
	{
		//throw(std::exception("Entry point not found"));
		return false;
	}
	plugins.push_back(myFunction());
	return true;
}

void MCruxPluginManager::AddExtensionPlugins(const list<wstring> extensionPluginNames)
{
	// TODO: search for the dlls from specific path and add those as extension plugins.
	// might have to take the path also from user so "const list<string>"  will be changed to "const list<pair<string, string> >"
	for (list<wstring>::const_iterator
		oIter = extensionPluginNames.begin();
		oIter != extensionPluginNames.end();
	oIter++)
	{
		AddPlugin(*oIter);
	}

}


HRESULT MCruxPluginManager::injectPlugins(IWebView *webView,
										  JSContextRef context,
										  JSObjectRef windowScriptObject)
{
	//MCruxWindow * mcruxWindow = MCruxWindow::getMCruxWindowFrom(webView);
	//MCruxWebView * mcruxWebView = mcruxWindow->getMCruxWebView();

	JSObjectRef globalObject = JSContextGetGlobalObject(context);
	JSStringRef name = JSStringCreateWithUTF8CString("mcrux");
	JSObjectSetProperty(context,
		globalObject,
		name,
		getMCruxJSObject(webView, context), 0, 0);

	// TODO: inject a new object called currentWindow
	// this object will be responsible for handling various events of currentwindow.

	return S_OK;
}


JSObjectRef MCruxPluginManager::getMCruxJSObject(IWebView* webView, JSContextRef context)
{
	if(!mcruxObject)
	{
		mcruxObject = JSObjectMake(context, NULL, NULL);
		for(list<MCruxPlugin *>::const_iterator
			oIter = plugins.begin();
			oIter != plugins.end();
		oIter++)
		{
			(*oIter)->injectPlugin(context, webView, mcruxObject);
		}
	}
	return mcruxObject;
}
