/**
 * copyright (C) 2008 Mital Vora. All rights reserved.
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

#include "StdAfx.h"
#include "MCruxJSObject.h"

#include <list>
using namespace std;

CMCruxJSObject::CMCruxJSObject()
{
	//list<JSStaticFunction> mylist(5);
	//JSStaticFunction *myfunc;
	//myfunc = new JSStaticFunction[5];
}

CMCruxJSObject::~CMCruxJSObject()
{
}

//void MCruxJSObject::prepareMCruxClassDefinition()
//{
//	static JSStaticFunction mcruxDefaultFunctions[]
//		= {
//			{"someFunction", MCruxJSObject::someFunction, 0},
//			{0, 0, 0}
//		};
//
//	MCruxNameSpace.version = 0;
//	MCruxNameSpace.attributes = 0;
//	MCruxNameSpace.className = "mcrux";
//	MCruxNameSpace.parentClass = 0;
//	MCruxNameSpace.staticValues = 0;
//	MCruxNameSpace.staticFunctions = mcruxDefaultFunctions;
//	MCruxNameSpace.initialize = mcruxInitialize;
//	MCruxNameSpace.finalize = mcruxFinalize;
//	MCruxNameSpace.hasProperty = 0;
//	MCruxNameSpace.getProperty = 0;
//	MCruxNameSpace.setProperty = 0;
//	MCruxNameSpace.deleteProperty = 0;
//	MCruxNameSpace.getPropertyNames = 0;
//	MCruxNameSpace.callAsFunction = 0;
//	MCruxNameSpace.callAsConstructor = 0;
//	MCruxNameSpace.hasInstance = 0;
//	MCruxNameSpace.convertToType = 0;
//}

//
//JSObjectRef MCruxJSObject::createJSWrapper(JSContextRef context)
//{
//	JSClassRef mcruxRef = JSClassCreate(&MCruxNameSpace);
//	return JSObjectMake(context, mcruxRef, this);
//}
