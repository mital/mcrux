#include "StdAfx.h"
#include "MCrux.h"

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>


JSStaticFunction MCrux::mcruxDefaultFunctions[] = { {"someFunction", MCrux::someFunctionCallback, 0}, {0, 0, 0} };

MCrux::MCrux()
{
	MCruxNameSpace.version = 0;
	MCruxNameSpace.attributes = 0;
	MCruxNameSpace.className = "mcrux";
	MCruxNameSpace.parentClass = 0;
	MCruxNameSpace.staticValues = 0;
	MCruxNameSpace.staticFunctions = mcruxDefaultFunctions;
	MCruxNameSpace.initialize = initializeMCrux;
	MCruxNameSpace.finalize = finalizeMCrux;
	MCruxNameSpace.hasProperty = 0;
	MCruxNameSpace.getProperty = 0;
	MCruxNameSpace.setProperty = 0;
	MCruxNameSpace.deleteProperty = 0;
	MCruxNameSpace.getPropertyNames = 0;
	MCruxNameSpace.callAsFunction = 0;
	MCruxNameSpace.callAsConstructor = 0;
	MCruxNameSpace.hasInstance = 0;
	MCruxNameSpace.convertToType = 0;
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
	return (JSValueRef)JSStringCreateWithUTF8CString(":My Returned Value From Function:");
}

void MCrux::initializeMCrux(JSContextRef ctx, JSObjectRef object)
{
	::MessageBoxA(0, "initializeMCrux called", "test", MB_OK);
}

void MCrux::finalizeMCrux(JSObjectRef object)
{
	::MessageBoxA(0, "finalizeMCrux called", "test", MB_OK);
}
