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

#ifndef _MCRUXWINDOWMANAGER_H_
#define _MCRUXWINDOWMANAGER_H_

#include <list>
#ifdef WIN32
#include "window/MCruxWindow.h"
#endif
#include "window/MCruxWindowConfiguration.h"


class MCruxWindowManager
{
	const list<MCruxWindowConfiguration*> windowConfigurations;
#ifdef WIN32
	MCruxPluginManager * pluginManager;
#endif

#ifdef WIN32
	list<MCruxWindow *> windows;
#endif
public:

	MCruxWindowManager(const list<MCruxWindowConfiguration*> & _windowConfigurations
#ifdef WIN32
		,MCruxPluginManager * _pluginManager
#endif
		);

	~MCruxWindowManager();

#ifdef WIN32
	IWebView * createWindow(IWebURLRequest *request);
#endif
};

#endif // _MCRUXWINDOWMANAGER_H_
