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

#include <iostream>

using namespace std;

#include <WebKit/WebKit.h>
#include <JavaScriptCore/JSContextRef.h>

#include "MCruxExport.h"


class MCRUX_API MCruxPlugin
{
protected:

	static IWebView* webView;

public:

	MCruxPlugin();

	virtual ~MCruxPlugin();

	virtual const char * getName() const=0;

	// static namespace related methods
	virtual JSStaticFunction * getStaticFunctions() const;

	virtual JSObjectCallAsConstructorCallback getConstructor() const;

	bool injectPlugin(JSContextRef ctx, IWebView * _webView, JSObjectRef parentObject);

	// object creation related methods
	JSObjectRef createJSObject(JSContextRef ctx);

	virtual JSStaticFunction * getJSObjectFunctions() const;
};
