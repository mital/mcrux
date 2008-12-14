#include "StdAfx.h"
#include "MCrux.h"

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>


JSStaticFunction MCrux::mcruxDefaultFunctions[]
	= {
		{"someFunction", MCrux::someFunctionCallback, 0},
		{0, 0, 0}
	};

MCrux::MCrux()
{
	prepareMCruxClassDefinition();
}

MCrux::~MCrux()
{
}


void MCrux::prepareMCruxClassDefinition()
{
	MCruxNameSpace.version = 0;
	MCruxNameSpace.attributes = 0;
	MCruxNameSpace.className = "mcrux";
	MCruxNameSpace.parentClass = 0;
	MCruxNameSpace.staticValues = 0;
	MCruxNameSpace.staticFunctions = mcruxDefaultFunctions;
	MCruxNameSpace.initialize = initialize;
	MCruxNameSpace.finalize = finalize;
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


JSObjectRef MCrux::createJSWrapper(JSContextRef context)
{
	JSClassRef mcruxRef = JSClassCreate(&MCruxNameSpace);
	return JSObjectMake(context, mcruxRef, this);
}


JSValueRef MCrux::someFunctionCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	::MessageBoxA(0, "someFunctionCallback called", "test", MB_OK);
	JSStringRef myString = JSValueToStringCopy(ctx, arguments[0], 0);
	
	string str = getStringValueFrom(myString);
	::MessageBoxA(0, str.c_str(), "test", MB_OK);

	JSStringRef myRetString = JSStringCreateWithUTF8CString(":My Returned Value From Function:");
	JSValueRef retRef = JSValueMakeString(ctx, myRetString);
	JSStringRelease(myRetString);
	return retRef;
}


void MCrux::initialize(JSContextRef ctx, JSObjectRef object)
{
	::MessageBoxA(0, "initialize called", "test", MB_OK);
}

void MCrux::finalize(JSObjectRef object)
{
	::MessageBoxA(0, "finalize called", "test", MB_OK);
}


string MCrux::getStringValueFrom(JSStringRef str)
{
	size_t length = JSStringGetMaximumUTF8CStringSize(str);
	char* buffer = new char[length];
	JSStringGetUTF8CString(str, buffer, length);
	string stdStr = buffer;
	delete[] buffer;
	return stdStr;
}