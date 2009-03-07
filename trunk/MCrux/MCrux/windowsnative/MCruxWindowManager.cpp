#include "StdAfx.h"
#include "MCruxWindowManager.h"


MCruxWindowManager::MCruxWindowManager(const list<MCruxWindowConfiguration*> & _windowConfigurations,
									   MCruxPluginManager * _pluginManager)
									   : pluginManager(_pluginManager)
{
	if(_windowConfigurations.size())
	{
		bool bMainWindow = true;
		for(list<MCruxWindowConfiguration*>::const_iterator
			oIter = _windowConfigurations.begin();
			oIter != _windowConfigurations.end();
		oIter++)
		{
			MCruxWindowConfiguration * mainWindowConfig = *oIter;
			MCruxWindow * mainWindow = new MCruxWindow(mainWindowConfig, pluginManager, bMainWindow);
			mainWindow->ShowWindow();
			mainWindow->UpdateWindow();
			if (bMainWindow)
			{
				bMainWindow = false;
			}
		}
	}
}


MCruxWindowManager::~MCruxWindowManager()
{
}
