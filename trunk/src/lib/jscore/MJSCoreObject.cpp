/**
* copyright (C) 2009 Mital Vora. All rights reserved.
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


#include <stdafx.h>

#include "MJSCoreObject.h"


MJSCoreObject::MJSCoreObject(JSContextRef _ctx)
: ctx(_ctx)
{
	JSClassDefinition oNameSpace = kJSClassDefinitionEmpty;
	JSClassRef classRef = JSClassCreate(&oNameSpace);
	object = JSObjectMake(ctx, classRef, this);
}

MJSCoreObject::~MJSCoreObject()
{
}

void MJSCoreObject::setProperty(JSContextRef ctx,
								  JSObjectRef object,
								  JSStringRef nameStr,
								  JSValueRef jsProperty,
								  JSPropertyAttributes attributes,
								  JSValueRef * exception)
{
	JSObjectSetProperty(ctx, object, nameStr, jsProperty,attributes, exception);
}


JSValueRef MJSCoreObject::getJSValue()
{
	//return ::JSValueToObject(ctx,;
	return NULL;
}

void MJSCoreObject::setProperty(const char * name, MObject * obj)
{
	MJSCoreObject * jsObj = dynamic_cast<MJSCoreObject *> (obj);
	if(jsObj)
	{
		JSStringRef nameStr = JSStringCreateWithUTF8CString(name);
		MJSCoreObject::setProperty(ctx, object, nameStr, jsObj->getJSValue());
		JSStringRelease(nameStr);
	}
}

MObject * MJSCoreObject::getProperty(const char * name)
{
	MObject * obj = NULL;
	return obj;
}
