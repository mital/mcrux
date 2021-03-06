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

#ifndef _MCRUXWINDOWCONFIG_H_
#define _MCRUXWINDOWCONFIG_H_

#include <iostream>

using namespace std;

#ifdef WIN32
#include <webkit/webkit.h>
#else
#include <QtWebKit/QtWebKit>
#endif
class MCruxWindowConfiguration
{
	const wstring windowTitle;
	const unsigned int width;
	const unsigned int height;
	const wstring url;
#ifdef WIN32
	IWebURLRequest *request;
#endif
public:
	MCruxWindowConfiguration(const wstring _windowTitle,
		unsigned int _width,
		unsigned int _height,
		const wstring & _url);

#ifdef WIN32
	MCruxWindowConfiguration(const wstring _windowTitle,
		unsigned int _width,
		unsigned int _height,
		IWebURLRequest *_request);
#endif

	~MCruxWindowConfiguration();

	wstring getURL() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	wstring getWindowTitle() const;
#ifdef WIN32
	IWebURLRequest *getRequest() const;
#endif
};

#endif // _MCRUXWINDOWCONFIG_H_
