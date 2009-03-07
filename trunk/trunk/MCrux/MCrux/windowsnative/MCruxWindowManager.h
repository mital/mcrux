#pragma once

#include "windowsnative/MCruxWindow.h"
#include "windowsnative/MCruxWindowConfiguration.h"


class MCruxWindowManager
{
	const list<MCruxWindowConfiguration*> windowConfigurations;
	MCruxPluginManager * pluginManager;

public:

	MCruxWindowManager(const list<MCruxWindowConfiguration*> & _windowConfigurations,
		MCruxPluginManager * _pluginManager);

	~MCruxWindowManager();
};
