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

#include "windowsnative/MCruxWindow.h"

#include "MCruxJSObject.h"

#include <jscore/MJSCoreObject.h>
#include <jscore/MJSCoreObjectFactory.h>


MCruxPluginManager::MCruxPluginManager(const list<wstring> extensionPluginNames)
: pluginDllsLoaded(false)
{
	for(list<wstring>::const_iterator oIter = extensionPluginNames.begin();
		oIter != extensionPluginNames.end();
		oIter++)
	{
		pluginNames.push_back(*oIter);
	}
}

MCruxPluginManager::~MCruxPluginManager()
{
}


bool MCruxPluginManager::AddPlugin(const wstring & pluginName, JSContextRef ctx)
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
	MObject * pluginObject = myFunction(ctx);
	if (pluginObject)
	{
		// TODO: get the name of the plugin from mcruxspec file.
		std::string strName = ((MJSCoreObject*)pluginObject)->getClassName();
		plugins[strName] = pluginObject;
		return true;
	}
	return false;
	
}

void MCruxPluginManager::loadExtensionPlugins(JSContextRef ctx)
{
	if(!pluginDllsLoaded)
	{
		// TODO: search for the dlls from specific path and add those as extension plugins.
		// might have to take the path also from user so "const list<string>"  will be changed to "const list<pair<string, string> >"
		for (list<wstring>::const_iterator
			oIter = pluginNames.begin();
			oIter != pluginNames.end();
		oIter++)
		{
			AddPlugin(*oIter, ctx);
		}
		pluginDllsLoaded = true;
	}
}


MObject* MCruxPluginManager::getMCruxJSObject(JSContextRef ctx)
{
	MCruxJSObject * mcruxObject = new MCruxJSObject(ctx);

	for(map<string, MObject*>::iterator oIter = plugins.begin();
		oIter != plugins.end();
		oIter++)
	{
		mcruxObject->setProperty(oIter->first, oIter->second);
	}
	return mcruxObject;
}

HRESULT MCruxPluginManager::injectPlugins(IWebView *webView,
										  JSContextRef context,
										  JSObjectRef windowScriptObject)
{
	loadExtensionPlugins(context);

	MJSCoreObjectFactory::Initialize(context);
	MJSCoreObject * globalObject = new MJSCoreObject(context, JSContextGetGlobalObject(context));

	MObject * mcruxObject = getMCruxJSObject(context);
	std::string strName = ((MJSCoreObject*)mcruxObject)->getClassName();
	globalObject->setProperty(strName, mcruxObject);

	return S_OK;

	//MCruxWindow * mcruxWindow = MCruxWindow::getMCruxWindowFrom(webView);
	//MCruxWebView * mcruxWebView = mcruxWindow->getMCruxWebView();

	// TODO: inject a new object called currentWindow
	// this object will be responsible for handling various events of currentwindow.
}