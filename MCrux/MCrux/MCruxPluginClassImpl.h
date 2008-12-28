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


#pragma once

#include <list>
#include <iostream>

using namespace std;

#include <JavaScriptCore/JSContextRef.h>


#define BEGIN_MCRUX_FUNCTION_MAP(className) \
	JSStaticFunction MCruxPluginClassImpl<className>::m_staticFuncs[] \
	= { 


#define MCRUX_FUNCTION_MAP_ENTRY(name, callAsFunction, attributes) \
	{ name, callAsFunction, attributes },

#define END_MCRUX_FUNCTION_MAP() \
	{ 0, 0, 0 }\
	};


template <class T>
class MCruxPluginClassImpl
{
protected:

	static JSStaticFunction m_staticFuncs[];

public:

	HRESULT getStaticFunctions(LONG * staticFuncs)
	{
		staticFuncs = (void*) m_staticFuncs;
		return S_OK;
	}
};
