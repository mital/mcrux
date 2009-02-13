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

#include "StdAfx.h"
#include "MCruxJSObject.h"

#include <list>
using namespace std;

MCruxJSObject::MCruxJSObject()
: MCruxPlugin()
{
}

MCruxJSObject::~MCruxJSObject()
{
}


string MCruxJSObject::getName() const
{
	static string name = "mcrux";
	return name;
}

JSStaticFunction * MCruxJSObject::getStaticFunctions() const
{
	static JSStaticFunction mcruxJSDefaultFunctions[]
	= {
		{"someFunction", MCruxJSObject::someFunction, 0},
		{"callJavaScriptFunction", MCruxJSObject::callJavaScriptFunction, 0},
		{0, 0, 0}
	};
	return mcruxJSDefaultFunctions;
}

JSObjectCallAsConstructorCallback MCruxJSObject::getConstructor() const
{
	return MCruxJSObject::ConstructorCallback;
}

JSValueRef MCruxJSObject::someFunction(JSContextRef ctx,
									   JSObjectRef function,
									   JSObjectRef thisObject,
									   size_t argumentCount,
									   const JSValueRef arguments[],
									   JSValueRef *exception)
{
	::MessageBoxA(0, "MCruxJSObject someFunction called", "test", MB_OK);
	return JSValueMakeNull(ctx);
}



JSValueRef MCruxJSObject::callJavaScriptFunction(JSContextRef ctx,
												 JSObjectRef function,
												 JSObjectRef thisObject,
												 size_t argumentCount,
												 const JSValueRef arguments[],
												 JSValueRef *exception)
{
	::MessageBoxA(0, "MCruxJSObject callJavaScriptFunction called", "test", MB_OK);

	if (argumentCount == 2)
	{
		JSStringRef myJSMethodName = JSValueToStringCopy(ctx, arguments[0], 0);
		JSObjectRef global = JSContextGetGlobalObject(ctx);
		JSValueRef myJSMethod = JSObjectGetProperty(ctx, global, myJSMethodName, 0);
		if(JSValueIsObject(ctx, myJSMethod) == false)
		{
			return JSValueMakeNull(ctx);
		}
		JSObjectRef function = JSValueToObject(ctx, myJSMethod, 0);
		JSValueRef result = JSObjectCallAsFunction (ctx, function, global, 0, 0, 0);

		JSObjectRef funcPassed = JSValueToObject(ctx, arguments[1], 0);
		JSValueRef result1 = JSObjectCallAsFunction (ctx, funcPassed, global, 0, 0, 0);
	}
	return JSValueMakeNull(ctx);
}
