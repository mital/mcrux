#include "StdAfx.h"
#include "MCruxPluginHandler.h"

MCruxPluginHandler::MCruxPluginHandler()
{
}


MCruxPluginHandler::~MCruxPluginHandler()
{
}


bool MCruxPluginHandler::initialize(list<string> plugins)
{
	::MessageBoxA(0, plugins.back().c_str(), "MCruxPluginHandler called", MB_OK);
	return false;
}

