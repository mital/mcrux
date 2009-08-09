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

#include "MJSCoreUtils.h"
#include "MJSCoreObjectFactory.h"
#include "JSStringUtils.h"

JSContextRef MJSCoreObjectFactory::context = NULL;

void MJSCoreObjectFactory::Initialize(JSContextRef _context)
{
	context = _context;
}


MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject()
{
	if (context)
	{
		return new MJSCoreObject(context);
	}
	return NULL;
}



MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSObjectRef _object)
{
	if (context)
	{
		return new MJSCoreObject(context, _object);
	}
	return NULL;
}


MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(double number)
{
	if (context)
	{
		return new MJSCoreNumber(context, number);
	}
	return NULL;
	
}


MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(const std::string & _str)
{
	if (context)
	{
		return new MJSCoreString(context, _str);
	}
	return NULL;
}

MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(bool bValue)
{
	if (context)
	{
		return new MJSCoreBool(context, bValue);
	}
	return NULL;
}

MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(MCruxMethodCallback * _method)
{
	if (context)
	{
		return new MJSCoreMethod(context, _method);
	}
	return NULL;
}

MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(const std::vector<MJSCoreObject *>& files)
{
	if (context)
	{
		return new MJSCoreObjectArray(context, files);
	}
	return NULL;
}

MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSValueRef _value)
{
	// TODO: handle custom JavaScript object.
	// TODO: handle for Method passing.
	MJSCoreObjectAbstract * mObj = NULL;

	if (context && _value)
	{
		if (JSValueIsNumber(context, _value))
		{
			double number = JSValueToNumber(context, _value, 0);
			mObj = getMObject(number);
		}
		else if (JSValueIsString(context, _value))
		{
			std::string str = getStringValueFrom(context, _value);
			mObj = getMObject(str);
		}
		else if (JSValueIsBoolean(context, _value))
		{
			mObj = getMObject(JSValueToBoolean(context, _value));
		}
		else if (JSValueIsNull(context, _value))
		{
			mObj = getMObject(JSValueToObject(context, _value, 0));
		}
		else
		{
			mObj = NULL;
		}
	}
	return mObj;
}
