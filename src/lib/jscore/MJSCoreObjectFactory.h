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


#pragma once

#include "jscore/MJSCoreObject.h"
#include "jscore/MJSCoreNumber.h"
#include "jscore/MJSCoreString.h"
#include "jscore/MJSCoreBool.h"


class MJSCoreObjectFactory
{
public:
	MJSCoreObjectFactory();
	virtual ~MJSCoreObjectFactory();

	static MJSCoreObjectAbstract * getMObject(JSContextRef _context);
	static MJSCoreObjectAbstract * getMObject(JSContextRef _context, JSObjectRef _object);
	static MJSCoreObjectAbstract * getMObject(JSContextRef _context, double number);
	static MJSCoreObjectAbstract * getMObject(JSContextRef _context, const std::string & _str);
	static MJSCoreObjectAbstract * getMObject(JSContextRef _context, bool bValue);
	static MJSCoreObjectAbstract * getMObject(JSContextRef context, MCruxMethodCallback * method);

	static MJSCoreObjectAbstract * getMObject(JSContextRef _context, JSValueRef _value);
};
