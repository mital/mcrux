#pragma once

#define MCRUXSPEC_ROOT_NAME "mcrux"
#define MCRUXSPEC_PLUGINS_NAME "plugins"
#define MCRUXSPEC_PLUGIN_NAME "plugin"
#define MCRUXSPEC_WINDOW_NAME "mcruxwindow"
#define MCRUXSPEC_WINDOW_TITLE_NAME "title"
#define MCRUXSPEC_WINDOW_URL_NAME "url"
#define MCRUXSPEC_XMLNS_VERSION_1 "http://www.mcrux.com/2009/mcruxspec-version-1"

#include <map>
#include <list>
#include <string>
#include <iostream>

using namespace std;

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "windowsnative/MCruxWindowConfiguration.h"

namespace XMLParser
{
	bool getProperties(_xmlAttr * properties, map<wstring, wstring> & attrMap);
};


class MCruxSpecParser
{
	list <MCruxWindowConfiguration *> windowConfigs;
	list<wstring> plugins;

	wstring getURL(xmlNode *child_prop) const;
	
	bool parseWindowElement(xmlNode *windowNode);
	bool parsePluginsElement(xmlNode *pluginsNode);

	/**
	 * Parses the MCruxSpec file with XML NameSpace version 1
	 * defined at http://www.mcrux.com/2009/mcruxspec-version-1
	 **/
	bool parseMCruxSpecXMLNSVersion1(xmlNode *root_child);

	/**
	 * root element parser (this will determine the XML NameSpace Version 
	 * depending on version it will select perticular parser.
	 * for now it is the initial version of MCruxSpec. 
	 **/
	bool parseMCruxSpecRootElement(xmlNode *root_element);

public:
	MCruxSpecParser();
	~MCruxSpecParser();

	bool parse(const string & mcruxAppConfigFileName);

	bool getWindowConfigList(list <MCruxWindowConfiguration *> & mcruxWindowConfigs) const;
	bool getPlugins(list <wstring> & _plugins) const;
};
