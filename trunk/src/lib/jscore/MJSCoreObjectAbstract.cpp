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
#include <jscore/MJSCoreUtils.h>
#include <jscore/MJSCoreObjectAbstract.h>


MJSCoreObjectAbstract::MJSCoreObjectAbstract(JSContextRef _ctx, JSOBJECTTYPE_en _type)
: ctx(_ctx),
  type(_type)
{
}


MJSCoreObjectAbstract::~MJSCoreObjectAbstract()
{
}

void MJSCoreObjectAbstract::setProperty(JSContextRef ctx,
								  JSObjectRef object,
								  JSStringRef nameStr,
								  JSValueRef jsProperty,
								  JSPropertyAttributes attributes,
								  JSValueRef * exception)
{
	JSObjectSetProperty(ctx, object, nameStr, jsProperty,attributes, exception);
}


bool MJSCoreObjectAbstract::isObject() const
{
	return type == TYPE_JSOBJECT;
}


bool MJSCoreObjectAbstract::isMethod() const
{
	return type == TYPE_JSMETHOD;
}


bool MJSCoreObjectAbstract::isNumber() const
{
	return type == TYPE_JSNUMBER;
}


bool MJSCoreObjectAbstract::isString() const
{
	return type == TYPE_JSSTRING;
}


bool MJSCoreObjectAbstract::isBool() const
{
	return type == TYPE_JSBOOL;
}