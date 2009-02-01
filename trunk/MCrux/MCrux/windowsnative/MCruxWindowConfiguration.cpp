#include "StdAfx.h"
#include <tchar.h>

#include "MCruxWindowConfiguration.h"


MCruxWindowConfiguration::MCruxWindowConfiguration(const wstring _windowTitle,
												   unsigned int _width,
												   unsigned int _height,
												   const wstring & _url)
: windowTitle(_windowTitle),
  width(_width),
  height(_height),
  url(_url)
{
}

MCruxWindowConfiguration::~MCruxWindowConfiguration()
{
}


wstring MCruxWindowConfiguration::getWindowTitle() const
{
	return windowTitle;
}

wstring MCruxWindowConfiguration::getURL() const
{
	return url;
}

unsigned int MCruxWindowConfiguration::getWidth() const
{
	return width;
}

unsigned int MCruxWindowConfiguration::getHeight() const
{
	return height;
}
