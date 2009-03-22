#pragma once

#include <list>
#include <iostream>

using namespace std;

#include <JavaScriptCore/JSContextRef.h>

class MCruxPluginHandler
{
public:
	MCruxPluginHandler();
	~MCruxPluginHandler();

	bool initialize(list<string> plugins, JSContextRef ctx);
};
