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
#include <jscore/MJSCoreObjectArray.h>
#include <jscore/MJSCoreObjectFactory.h>


MJSCoreObjectArray::MJSCoreObjectArray(JSContextRef _ctx, const std::vector<MJSCoreObject *>& files)
: MJSCoreObjectAbstract(_ctx, TYPE_JSOBJECT_ARRAY)
{
	JSObjectRef * fileJSStrings = new JSObjectRef[files.size()];
	for (size_t i=0; i < files.size(); i++)
	{
		fileJSStrings[i] = files[i]->getJSObject();
	}

	object = JSObjectMakeArray(ctx, files.size(), fileJSStrings, NULL);
}


MJSCoreObjectArray::~MJSCoreObjectArray()
{
}


JSValueRef MJSCoreObjectArray::getJSValue()
{
	return object;
}


JSObjectRef MJSCoreObjectArray::getJSObject()
{
	return object;
}


const char * MJSCoreObjectArray::toString()
{
	std::string str;
	return str.c_str();
}