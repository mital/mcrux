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


#include "stdafx.h"
#include "MCruxPlugin.h"
#include "windowsnative/MCruxWindow.h"

#include <JavaScriptCore/JSStringRef.h>

IWebView * MCruxPlugin::webView = NULL;

MCruxPlugin::MCruxPlugin()
{
}

MCruxPlugin::~MCruxPlugin()
{
}


bool MCruxPlugin::injectPlugin(JSContextRef ctx, IWebView * _webView, JSObjectRef parentObject)
{
	MCruxPlugin::webView = _webView;
	JSClassDefinition pluginNameSpace;// = kJSClassDefinitionEmpty;

	pluginNameSpace.version = 0;
	pluginNameSpace.attributes = 0;
	pluginNameSpace.className = getName();
	pluginNameSpace.parentClass = 0;
	pluginNameSpace.staticValues = 0;
	pluginNameSpace.staticFunctions = getStaticFunctions();
	pluginNameSpace.initialize = 0;
	pluginNameSpace.finalize = 0;
	pluginNameSpace.hasProperty = 0;
	pluginNameSpace.getProperty = 0;
	pluginNameSpace.setProperty = 0;
	pluginNameSpace.deleteProperty = 0;
	pluginNameSpace.getPropertyNames = 0;
	pluginNameSpace.callAsFunction = 0;
	pluginNameSpace.callAsConstructor = getConstructor();
	pluginNameSpace.hasInstance = 0;
	pluginNameSpace.convertToType = 0;

	JSClassRef pluginRef = JSClassCreate(&pluginNameSpace);
	JSObjectRef pluginObj = JSObjectMake(ctx, pluginRef, this);
	JSStringRef fnPropName = JSStringCreateWithUTF8CString(getName());
	JSObjectSetProperty(ctx,
		parentObject,
		fnPropName,
		pluginObj, 0, 0);

	return true;
}

JSObjectCallAsConstructorCallback MCruxPlugin::getConstructor() const
{
	return 0;
}

JSStaticFunction * MCruxPlugin::getStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {	{0, 0, 0} };
	return JSDefaultFunctions;
}


JSObjectRef MCruxPlugin::createJSObject(JSContextRef ctx)
{
	JSClassDefinition pluginNameSpace;// = kJSClassDefinitionEmpty;

	pluginNameSpace.version = 0;
	pluginNameSpace.attributes = 0;
	pluginNameSpace.className = 0;
	pluginNameSpace.parentClass = 0;
	pluginNameSpace.staticValues = 0;
	pluginNameSpace.staticFunctions = getJSObjectFunctions();
	pluginNameSpace.initialize = 0;
	pluginNameSpace.finalize = 0;
	pluginNameSpace.hasProperty = 0;
	pluginNameSpace.getProperty = 0;
	pluginNameSpace.setProperty = 0;
	pluginNameSpace.deleteProperty = 0;
	pluginNameSpace.getPropertyNames = 0;
	pluginNameSpace.callAsFunction = 0;
	pluginNameSpace.callAsConstructor = 0;
	pluginNameSpace.hasInstance = 0;
	pluginNameSpace.convertToType = 0;

	JSClassRef pluginRef = JSClassCreate(&pluginNameSpace);
	return JSObjectMake(ctx, pluginRef, this);
}

JSStaticFunction * MCruxPlugin::getJSObjectFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {	{0, 0, 0} };
	return JSDefaultFunctions;
}