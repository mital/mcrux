#include "StdAfx.h"
#include "MCrux.h"

JSStaticFunction mcruxDefaultFunctions[] = { {"someFunction", MCrux::someFunctionCallback, 0}, {0, 0, 0} };

MCrux::MCrux()
{
}

MCrux::~MCrux()
{
}


JSObjectRef MCrux::createJSWrapper(JSContextRef context)
{
	JSClassRef mcruxRef = JSClassCreate(&MCruxNameSpace);
	return JSObjectMake(context, mcruxRef, this);
}

JSValueRef MCrux::someFunctionCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	::MessageBoxA(0, "someFunctionCallback called", "test", MB_OK);
	return 0;
}

void MCrux::initializeMCrux(JSContextRef ctx, JSObjectRef object)
{
	::MessageBoxA(0, "initializeMCrux called", "test", MB_OK);
}

void MCrux::finalizeMCrux(JSObjectRef object)
{
	::MessageBoxA(0, "finalizeMCrux called", "test", MB_OK);
}
