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

#include <abstract/MCruxExport.h>

#include "jscore/MJSCoreObject.h"
#include "jscore/MJSCoreNumber.h"
#include "jscore/MJSCoreString.h"
#include "jscore/MJSCoreBool.h"


class MCRUX_API MJSCoreObjectFactory
{
private:
	static JSContextRef context;

public:
	static void Initialize(JSContextRef _context);

	static MJSCoreObjectAbstract * getMObject();
	static MJSCoreObjectAbstract * getMObject(JSObjectRef _object);
	static MJSCoreObjectAbstract * getMObject(double number);
	static MJSCoreObjectAbstract * getMObject(const std::string & _str);
	static MJSCoreObjectAbstract * getMObject(bool bValue);
	static MJSCoreObjectAbstract * getMObject(MCruxMethodCallback * _method);

	static MJSCoreObjectAbstract * getMObject(JSValueRef _value);
};
