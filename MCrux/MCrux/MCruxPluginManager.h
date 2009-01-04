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

#include <list>
#include <iostream>

using namespace std;

#include <WebKit.h>

#include "MCrux.h"
#include "MCruxPlugin.h"


class MCruxPluginManager
{
	list<MCruxPlugin *> plugins;

	void AddMCruxDefaultPlugins();

	void AddExtensionPlugins(const list<string> extensionPluginNames);

public:

	MCruxPluginManager(const list<string> extensionPluginNames);

	~MCruxPluginManager();

	HRESULT injectPlugins(IWebView *webView,
        JSContextRef context,
        JSObjectRef windowScriptObject);
};
