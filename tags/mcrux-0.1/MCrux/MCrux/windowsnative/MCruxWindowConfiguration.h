#pragma once

#include <iostream>

using namespace std;


class MCruxWindowConfiguration
{
	wstring url;
public:
	MCruxWindowConfiguration(const wstring & _url);
	~MCruxWindowConfiguration();

	wstring getURL() const;
	TCHAR * getWindowTitle() const;
};
