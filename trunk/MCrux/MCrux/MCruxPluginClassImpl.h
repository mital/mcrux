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

#include <assert.h>

#include <list>
#include <iostream>

using namespace std;

#include <JavaScriptCore/JSContextRef.h>

#include "MCrux.h"


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
	: public IMCruxPlugin
{
private:

	long m_lRefCount;

	static JSStaticFunction m_staticFuncs[];

public:

	virtual HRESULT STDMETHODCALLTYPE
		getStaticFunctions(LONG * staticFuncs)
	{
		staticFuncs = (LONG*) m_staticFuncs;
		return S_OK;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return InterlockedIncrement (&m_lRefCount); 
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		LONG res = InterlockedDecrement (&m_lRefCount);
		if (0 ==  res) delete this;
		return  res;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv)
	{
		assert (ppv != 0);
		if (riid == IID_IMCruxPlugin) *ppv = static_cast <IMCruxPlugin*> (this); 
		else if (riid == IID_IUnknown) *ppv = static_cast <IMCruxPlugin*> (this); 
		else { ppv = 0; return E_NOINTERFACE; } 
		reinterpret_cast <IUnknown*> (*ppv)->AddRef ();
		return S_OK; 
	}
};
