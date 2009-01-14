#pragma once

#include <iostream>

using namespace std;


class MCruxWindowConfiguration
{
	string url;
public:
	MCruxWindowConfiguration(const string & _url);
	~MCruxWindowConfiguration();

	string getURL() const;
	TCHAR * getWindowTitle() const;
};
