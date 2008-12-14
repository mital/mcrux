#pragma once


#include <JavaScriptCore/JSObjectRef.h>


class MCrux
{
	static JSStaticFunction mcruxDefaultFunctions[2];

	static JSValueRef someFunctionCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);
	static void initializeMCrux(JSContextRef ctx, JSObjectRef object);
	static void finalizeMCrux(JSObjectRef object);

	JSClassDefinition MCruxNameSpace;

public:
	MCrux();
	~MCrux();

	JSObjectRef createJSWrapper(JSContextRef context);

};
