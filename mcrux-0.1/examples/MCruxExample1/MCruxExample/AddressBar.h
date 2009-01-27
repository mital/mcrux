#pragma once

#include "Resources.h"
class MCruxView;

class AddressBar
{
	HWND hURLBarWnd;
	static MCruxView * mcruxView;
	static LRESULT CALLBACK AddressBarHandler(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static void navigateToURL(HWND hDlg);

public:

	AddressBar(HWND hMainWnd, HINSTANCE hInstance);
	~AddressBar();

	void resize(RECT rcClient);
	void setMCruxView(MCruxView* _mcruxView);
	void setText(BSTR url);
};
