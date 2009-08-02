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

#include "JSStringUtils.h"
#include "MJSCoreUtils.h"
#include "MJSCoreObject.h"
#include "MJSCoreObjectFactory.h"


MJSCoreObject::MJSCoreObject(JSContextRef _ctx)
: MJSCoreObjectAbstract(_ctx, TYPE_JSOBJECT)
{
	JSClassDefinition oNameSpace = kJSClassDefinitionEmpty;
	JSClassRef classRef = JSClassCreate(&oNameSpace);
	object = JSObjectMake(ctx, classRef, this);
}

MJSCoreObject::MJSCoreObject(JSContextRef _ctx, JSObjectRef _object)
: MJSCoreObjectAbstract(_ctx),
  object(_object)
{
}

MJSCoreObject::~MJSCoreObject()
{
}

void MJSCoreObject::getPropertyNames(set<string> & properties)
{
	JSPropertyNameArrayRef names = JSObjectCopyPropertyNames(ctx, object);
	JSPropertyNameArrayRetain(names);

	size_t count = JSPropertyNameArrayGetCount(names);
	for (size_t index = 0; index < count; index++)
	{
		JSStringRef name = JSPropertyNameArrayGetNameAtIndex(names, index);
		properties.insert(getStringValueFrom(ctx, name));
		free(name);
	}

	JSPropertyNameArrayRelease(names);
}


void MJSCoreObject::setProperty(const std::string & name, MObject * obj)
{
	MJSCoreObjectAbstract * mJSObj = dynamic_cast<MJSCoreObjectAbstract *> (obj);
	if(mJSObj)
	{
		JSStringRef nameStr = JSStringCreateWithUTF8CString(name.c_str());
		MJSCoreObjectAbstract::setProperty(ctx, this->getJSObject(), nameStr, mJSObj->getJSValue());
		JSStringRelease(nameStr);
	}
}

MObject * MJSCoreObject::getProperty(const std::string & name)
{
	JSStringRef sName = JSStringCreateWithUTF8CString(name.c_str());
	JSValueRef oProperty = JSObjectGetProperty(ctx, object, sName, NULL);
	JSStringRelease(sName);

	MObject * obj = NULL;

	if(oProperty)
	{
		obj = MJSCoreObjectFactory::getMObject(ctx, oProperty);
	}
	return obj;
}

bool MJSCoreObject::hasProperty(const std::string & name)
{
	set<string> properties;
	getPropertyNames(properties);
	set<string>::iterator iter = properties.find(name);
	if(iter == properties.end())
	{
		return false;
	}
	return true;
}


JSValueRef MJSCoreObject::getJSValue()
{
	return object;
}


JSObjectRef MJSCoreObject::getJSObject()
{
	return object;
}
