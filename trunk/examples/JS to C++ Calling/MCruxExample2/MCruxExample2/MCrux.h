#pragma once


#include <JavaScriptCore/JSObjectRef.h>

JSStaticFunction mcruxDefaultFunctions[];


class MCrux
{
public:
	MCrux();
	~MCrux();

	JSObjectRef createJSWrapper(JSContextRef context);

	static JSValueRef someFunctionCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);

	static void initializeMCrux(JSContextRef ctx, JSObjectRef object);
	static void finalizeMCrux(JSObjectRef object);

};


static JSClassDefinition MCruxNameSpace = {0,
0,
"mcrux",
0,
0,
mcruxDefaultFunctions,
MCrux::initializeMCrux, // function that will be called the first time this class is created
MCrux::finalizeMCrux, // function that will be called to tear down this class
0, 
0,
0,
0,
0, 
0,
0,
0,
0,
};


