#include "StdAfx.h"
#include "MCruxSpecParser.h"
#include <algorithm>


MCruxSpecParser::MCruxSpecParser()
{
}

MCruxSpecParser::~MCruxSpecParser()
{
}

wstring MCruxSpecParser::getURL(xmlNode *child_prop) const
{
	xmlChar * text = xmlCharStrdup("text");
	if(child_prop->children->name, text)
	{
		string url8 = (char*)child_prop->children->content;
		wstring url(url8.begin(), url8.end());
		return url;
	}
	wstring url;
	return url;
}

bool MCruxSpecParser::parseMCruxSpecXMLNSVersion1(xmlNode *root_child)
{
	xmlChar * mCruxSpecWindowName = xmlCharStrdup(MCRUXSPEC_WINDOW_NAME);

	for (xmlNode *cur_node = root_child;
		cur_node != NULL;
		cur_node = cur_node->next)
	{
		if ((cur_node->type == XML_ELEMENT_NODE)
			&& (0 == xmlStrcmp(cur_node->name, mCruxSpecWindowName)))
		{
			wstring url;
			xmlChar * urlName = xmlCharStrdup(MCRUXSPEC_WINDOW_URL_NAME);
			for(xmlNode * child_prop = cur_node->children;
				child_prop;
				child_prop = child_prop->next)
			{
				if (0 == xmlStrcmp(child_prop->name, urlName))
				{
					url = getURL(child_prop);
				}
			}
			MCruxWindowConfiguration * winConf = new MCruxWindowConfiguration(url);
			windowConfigs.push_back(winConf);
		}
	}

	return true;
}

bool MCruxSpecParser::parseMCruxSpecRootElement(xmlNode *root_element)
{
	if (root_element)
	{
		xmlChar * mCruxSpecRootName = xmlCharStrdup(MCRUXSPEC_ROOT_NAME);

		if ((root_element->type == XML_ELEMENT_NODE)
			&& (0 == xmlStrcmp(root_element->name, mCruxSpecRootName)))
		{
			xmlChar * mCruxSpecNS = xmlCharStrdup(MCRUXSPEC_XMLNS_VERSION_1);
			if ((root_element->ns)
				&& (root_element->ns->type == XML_NAMESPACE_DECL)
				&& (0 == xmlStrcmp(mCruxSpecNS, root_element->ns->href)))
			{
				return parseMCruxSpecXMLNSVersion1(root_element->children);
			}
		}
	}
	return false;
}


bool MCruxSpecParser::parse(const string & mcruxAppConfigFileName)
{
	xmlDoc *doc = xmlReadFile(mcruxAppConfigFileName.c_str(), NULL, 0);;

	if (doc != NULL)
	{
		parseMCruxSpecRootElement(xmlDocGetRootElement(doc));

		xmlFreeDoc(doc);
		xmlCleanupParser();
		return true;
	}
	return false;
}

bool MCruxSpecParser::getWindowConfigList(list <MCruxWindowConfiguration *> & mcruxWindowConfigs) const
{
	if(windowConfigs.size())
	{
		for(list <MCruxWindowConfiguration *>::const_iterator
			oIter = windowConfigs.begin();
			oIter != windowConfigs.end();
		oIter++)
		{
			mcruxWindowConfigs.push_back(*oIter);
		}
		return true;
	}
	return false;
	
}