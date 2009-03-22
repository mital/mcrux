#pragma once

#include <list>
#include <iostream>

using namespace std;


class MCruxPluginHandler
{
public:
	MCruxPluginHandler();
	~MCruxPluginHandler();

	bool initialize(list<string> plugins);
};
