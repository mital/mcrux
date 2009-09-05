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

#ifndef _MJSCOREOBJECTABSTRACT_H_
#define _MJSCOREOBJECTABSTRACT_H_

#include <vector>

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSStringRef.h>

#include "abstract/MObject.h"
#include "abstract/MObjectArray.h"

enum JSOBJECTTYPE_en
{
	TYPE_JSUNDEFINED = -1,
	TYPE_JSOBJECT = 1,
	TYPE_JSMETHOD,
	TYPE_JSNUMBER,
	TYPE_JSSTRING,
	TYPE_JSBOOL,
	TYPE_JSOBJECT_ARRAY,
};

class MCRUX_API MJSCoreObjectAbstract
	: public MObject
{
protected:
	const JSOBJECTTYPE_en type;
	JSContextRef ctx;

	static void setProperty(JSContextRef ctx,
		JSObjectRef object,
		JSStringRef nameStr,
		JSValueRef jsProperty,
		JSPropertyAttributes attributes = NULL,
		JSValueRef * exception = NULL);

public:

	MJSCoreObjectAbstract(JSContextRef _ctx, const JSOBJECTTYPE_en _type = TYPE_JSUNDEFINED);
	virtual ~MJSCoreObjectAbstract();

	virtual JSValueRef getJSValue()=0;
	virtual JSObjectRef getJSObject()=0;
	virtual const char * toString()=0;

	bool isObject() const;
	bool isMethod() const;
	bool isNumber() const;
	bool isString() const;
	bool isBool() const;
};

#endif // _MJSCOREOBJECTABSTRACT_H_