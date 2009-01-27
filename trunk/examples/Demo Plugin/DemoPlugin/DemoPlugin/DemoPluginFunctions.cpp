#include "stdafx.h"

#include <JavaScriptCore/JSObjectRef.h>

JSValueRef MyDemoPluginMethod(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	::MessageBoxA(0, "MyDemoPluginMethod called", "test", MB_OK);
	return 0;
}