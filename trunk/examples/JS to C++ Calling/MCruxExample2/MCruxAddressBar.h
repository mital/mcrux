#pragma once

class MCruxAddressBar
{
	HWND hWndAddressBar;
	static long DefEditProc;
	static LRESULT CALLBACK MCruxAddressBar::MyEditProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
public:
	MCruxAddressBar(HINSTANCE hInstance, HWND hParentWnd);
	~MCruxAddressBar();

	HWND getAddressBarWindow() const;
};
