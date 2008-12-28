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

#include <JavaScriptCore/JSContextRef.h>

#include "MCrux.h"
#include "MCruxPluginClassImpl.h"


class CMCruxJSObject
	: public CComObjectRootEx<CComSingleThreadModel>,
	  public CComCoClass<CMCruxJSObject, &CLSID_MCruxJSObject>,
	  public IDispatchImpl<IMCruxPlugin, &IID_IMCruxPlugin, &LIBID_MCruxLib, 1, 0>,
	  public MCruxPluginClassImpl<CMCruxJSObject>
{
	JSObjectRef createJSWrapper(JSContextRef context);

public:

	CMCruxJSObject();
	~CMCruxJSObject();

	bool placeMCruxJSGlobalObject(JSContextRef context);
};

BEGIN_MCRUX_FUNCTION_MAP(MCruxJSObject)
//		MCRUX_FUNCTION_MAP_ENTRY(
END_MCRUX_FUNCTION_MAP()
