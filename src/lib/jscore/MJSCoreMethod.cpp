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
#include "MJSCoreMethod.h"
#include <abstract/MObjectContainer.h>


MJSCoreMethod::MJSCoreMethod(JSContextRef _ctx, MCruxMethodCallback * _method)
: MJSCoreObjectAbstract(_ctx, TYPE_JSMETHOD),
  method(_method)
{
}


MJSCoreMethod::~MJSCoreMethod()
{
}


JSValueRef MJSCoreMethod::getJSValue()
{
	return toJSValue(ctx, this);
}


JSObjectRef MJSCoreMethod::getJSObject()
{
	return ::JSValueToObject(ctx, getJSValue(), 0);
}

MCruxMethodCallback * MJSCoreMethod::getMethod()
{
	return method;
}

MJSCoreObjectAbstract * MJSCoreMethod::invoke(const MObjectArray& args)
{
	MObjectContainer resultContainer;
	method->Run(args, resultContainer);
	return dynamic_cast<MJSCoreObjectAbstract *>(resultContainer.get());
}