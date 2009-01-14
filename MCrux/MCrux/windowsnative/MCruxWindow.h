#pragma once

#include <iostream>

using namespace std;

#include "MCruxWindowConfiguration.h"


class MCruxWindow
{
	HINSTANCE hInstance;
	HWND hWnd;
	const MCruxWindowConfiguration * config;

	static TCHAR * getWindowClassName();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	MCruxWindow(HINSTANCE _hInstance, const MCruxWindowConfiguration * _config);
	~MCruxWindow();

	int ShowWindow() const;
	int HideWindow() const;
	int UpdateWindow() const;


	static void initWindowClass(HINSTANCE hInstance);
	static void unInitWindowClass(HINSTANCE hInstance);
};
