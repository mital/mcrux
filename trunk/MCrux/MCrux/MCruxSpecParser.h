#pragma once

#define MCRUXSPEC_ROOT_NAME "mcrux"
#define MCRUXSPEC_PLUGINS_NAME "plugins"
#define MCRUXSPEC_PLUGIN_NAME "plugin"
#define MCRUXSPEC_WINDOW_NAME "mcruxwindow"
#define MCRUXSPEC_WINDOW_URL_NAME "url"
#define MCRUXSPEC_XMLNS_VERSION_1 "http://www.mcrux.com/2009/mcruxspec-version-1"

#include <list>
#include <iostream>

using namespace std;

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "windowsnative/MCruxWindowConfiguration.h"


class MCruxSpecParser
{
	list <MCruxWindowConfiguration *> windowConfigs;
	list<wstring> plugins;

	wstring getURL(xmlNode *child_prop) const;
	wstring getPlugin(xmlNode *child_prop) const;
	bool parseMCruxSpecRootElement(xmlNode *root_element);
	bool parseMCruxSpecXMLNSVersion1(xmlNode *root_child);

public:
	MCruxSpecParser();
	~MCruxSpecParser();

	bool parse(const string & mcruxAppConfigFileName);

	bool getWindowConfigList(list <MCruxWindowConfiguration *> & mcruxWindowConfigs) const;
	bool getPlugins(list <wstring> & _plugins) const;
};
