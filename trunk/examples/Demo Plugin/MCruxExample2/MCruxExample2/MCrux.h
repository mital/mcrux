#pragma once

#include <iostream>

using namespace std;

#include <JavaScriptCore/JSObjectRef.h>

#include "MCruxPluginHandler.h"


class MCrux
{
	static void mcruxInitialize(JSContextRef ctx, JSObjectRef object);
	static void mcruxFinalize(JSObjectRef object);

	//JSStaticFunction mcruxDefaultFunctions[2];
	static JSValueRef initialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);

	JSClassDefinition MCruxNameSpace;
	void prepareMCruxClassDefinition();

	static string getStringValueFrom(JSStringRef str);

	MCruxPluginHandler mcruxPluginHandler;
	
public:
	MCrux();
	~MCrux();

	JSObjectRef createJSWrapper(JSContextRef context);

	MCruxPluginHandler* getPluginHandler();
};
