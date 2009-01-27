#include "StdAfx.h"
#include <tchar.h>

#include "MCruxWindowConfiguration.h"


MCruxWindowConfiguration::MCruxWindowConfiguration(const wstring & _url)
	: url(_url)
{
}

MCruxWindowConfiguration::~MCruxWindowConfiguration()
{
}


TCHAR * MCruxWindowConfiguration::getWindowTitle() const
{
	static TCHAR windowTitleName[MAX_LOADSTRING] = _T("MCruxWindowTitleName");
	return windowTitleName;
}

wstring MCruxWindowConfiguration::getURL() const
{
	return url;
}
