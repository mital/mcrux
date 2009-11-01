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


#ifndef _MCRUXPLUGINMANAGER_H_
#define _MCRUXPLUGINMANAGER_H_

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#include <WebKit/WebKit.h>

#include <mcrux/MCrux.h>
#include "MCruxJSObject.h"

class MCruxWindow;

typedef MObject * (*GetPluginFunctionPtr)(JSContextRef ctx);

class MCruxPluginManager
{
	bool pluginDllsLoaded;
	list<wstring> pluginNames;
	map<string, MObject *> plugins;

	bool AddPlugin(const wstring & pluginName, JSContextRef ctx);
	void loadExtensionPlugins(JSContextRef ctx);

	MObject * getMCruxJSObject(JSContextRef ctx);
public:

	MCruxPluginManager(const list<wstring> extensionPluginNames);

	~MCruxPluginManager();

	HRESULT injectPlugins(IWebView *webView,
        JSContextRef context,
        JSObjectRef windowScriptObject);
};

#endif // _MCRUXPLUGINMANAGER_H_