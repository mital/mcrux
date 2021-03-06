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
#include <string>

#include <jscore/MJSCoreString.h>


MJSCoreString::MJSCoreString(JSContextRef _ctx, const std::string & _str)
: MJSCoreObjectAbstract(_ctx, TYPE_JSSTRING),
  str(_str)
{
}

MJSCoreString::~MJSCoreString()
{
}

JSValueRef MJSCoreString::getJSValue()
{
	JSStringRef jsStr = JSStringCreateWithUTF8CString(str.c_str());
	return JSValueMakeString(ctx, jsStr);
}


JSObjectRef MJSCoreString::getJSObject()
{
	return ::JSValueToObject(ctx, getJSValue(), 0);
}

const char * MJSCoreString::toString()
{
	return str.c_str();
}