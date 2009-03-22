#pragma once

#include <iostream>

using namespace std;

#include <JavaScriptCore/JSObjectRef.h>


class MCrux
{
	static JSStaticFunction mcruxDefaultFunctions[2];

	static JSValueRef someFunctionCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);
	static void initialize(JSContextRef ctx, JSObjectRef object);
	static void finalize(JSObjectRef object);

	JSClassDefinition MCruxNameSpace;

	void prepareMCruxClassDefinition();

	static string getStringValueFrom(JSStringRef str);

public:
	MCrux();
	~MCrux();

	JSObjectRef createJSWrapper(JSContextRef context);

};
