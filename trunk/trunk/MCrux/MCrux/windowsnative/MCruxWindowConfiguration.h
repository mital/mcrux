#pragma once

#include <iostream>

using namespace std;


class MCruxWindowConfiguration
{
	const wstring windowTitle;
	const unsigned int width;
	const unsigned int height;
	const wstring url;
public:
	MCruxWindowConfiguration(const wstring _windowTitle,
		unsigned int _width,
		unsigned int _height,
		const wstring & _url);

	~MCruxWindowConfiguration();

	wstring getURL() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	wstring getWindowTitle() const;
};
