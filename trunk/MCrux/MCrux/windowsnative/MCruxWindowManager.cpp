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

#include "StdAfx.h"
#include "MCruxWindowManager.h"


MCruxWindowManager::MCruxWindowManager(const list<MCruxWindowConfiguration*> & _windowConfigurations,
									   MCruxPluginManager * _pluginManager)
									   : pluginManager(_pluginManager)
{
	if(_windowConfigurations.size())
	{
		for(list<MCruxWindowConfiguration*>::const_iterator
			oIter = _windowConfigurations.begin();
			oIter != _windowConfigurations.end();
		oIter++)
		{
			MCruxWindowConfiguration * mainWindowConfig = *oIter;
			MCruxWindow * newWindow = new MCruxWindow(mainWindowConfig, pluginManager, this);
			newWindow->ShowWindow();
			newWindow->UpdateWindow();
			windows.push_back(newWindow);
		}
	}
}


MCruxWindowManager::~MCruxWindowManager()
{
}


IWebView * MCruxWindowManager::createWindow(IWebURLRequest *request)
{
	MCruxWindowConfiguration * mainWindowConfig = new MCruxWindowConfiguration(L"title", 200, 200, request);
	MCruxWindow * newWindow = new MCruxWindow(mainWindowConfig, pluginManager, this);
	//newWindow->ShowWindow();
	//newWindow->UpdateWindow();
	windows.push_back(newWindow);
	return newWindow->getMCruxWebView()->getWebView();
}