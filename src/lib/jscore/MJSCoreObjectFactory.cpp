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



MJSCoreObjectFactory::MJSCoreObjectFactory()
{
}


MJSCoreObjectFactory::~MJSCoreObjectFactory()
{
}


MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSContextRef _context)
{
	return new MJSCoreObject(_context);
}



MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSContextRef _context, JSObjectRef _object)
{
	return new MJSCoreObject(_context, _object);
}


MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSContextRef _context, double number)
{
	return new MJSCoreNumber(_context, number);
}


MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSContextRef _context, const std::string & _str)
{
	return new MJSCoreString(_context, _str);
}

MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSContextRef _context, bool bValue)
{
	return new MJSCoreBool(_context, bValue);
}

MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSContextRef _context, MCruxMethodCallback * _method)
{
	return new MJSCoreMethod(_context, _method);
}

MJSCoreObjectAbstract * MJSCoreObjectFactory::getMObject(JSContextRef _context, JSValueRef _value)
{
	// TODO: handle custom JavaScript object.
	// TODO: handle for Method passing.
	MJSCoreObjectAbstract * mObj = NULL;

	if (_value)
	{
		if (JSValueIsNumber(_context, _value))
		{
			double number = JSValueToNumber(_context, _value, 0);
			mObj = getMObject(_context, number);
		}
		else if (JSValueIsString(_context, _value))
		{
			std::string str = getStringValueFrom(_context, _value);
			mObj = getMObject(_context, str);
		}
		else if (JSValueIsBoolean(_context, _value))
		{
			mObj = getMObject(_context, JSValueToBoolean(_context, _value));
		}
		else if (JSValueIsNull(_context, _value))
		{
			mObj = getMObject(_context, ::JSValueToObject(_context, _value, 0));
		}
		else
		{
			mObj = NULL;
		}
	}
	return mObj;
}
