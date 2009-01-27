#include "StdAfx.h"

#include "AddressBar.h"
#include "MCruxView.h"
#include "Resources.h"

#include "WebKit.h"

long DefEditProc;

MCruxView* AddressBar::mcruxView = NULL;

LRESULT CALLBACK AddressBar::AddressBarHandler(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
	{
        case WM_CHAR:
            if (wParam == 13) // Enter Key
			{
				//navigateToURL(hDlg);
				wchar_t * str = new wchar_t(MAX_URL_LENGTH);
				*((wchar_t*) str) = MAX_URL_LENGTH;
				int len = SendMessage(hDlg, EM_GETLINE, 0, (LPARAM)str);
				BSTR bstr = SysAllocStringLen(str, len);
				if (AddressBar::mcruxView)
				{
					AddressBar::mcruxView->loadURL(bstr);
				}
				SysFreeString(bstr);
				return 0;
			}
			else
			{
                return (LRESULT)CallWindowProc((WNDPROC)DefEditProc,hDlg,message,wParam,lParam);
			}
            break;
        default:
             return (LRESULT)CallWindowProc((WNDPROC)DefEditProc,hDlg,message,wParam,lParam);
        break;
    }
    return 0;
}


AddressBar::AddressBar(HWND hMainWnd, HINSTANCE hInstance)
{
    hURLBarWnd = CreateWindow(ADDRESS_BAR_NAME,
		0, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOVSCROLL, 
        0, 0, 0, 0, hMainWnd, 0, hInstance, 0);

    DefEditProc = GetWindowLong(hURLBarWnd, GWL_WNDPROC);
    SetWindowLong(hURLBarWnd, GWL_WNDPROC,(long)AddressBarHandler);
    SetFocus(hURLBarWnd);

}

AddressBar::~AddressBar()
{
}

void AddressBar::resize(RECT rcClient)
{
	MoveWindow(hURLBarWnd, 0, 0, rcClient.right, URLBAR_HEIGHT, TRUE);
}

void AddressBar::setMCruxView(MCruxView* _mcruxView)
{
	mcruxView = _mcruxView;
}


void AddressBar::setText(BSTR url)
{
    SendMessage(hURLBarWnd, (UINT)WM_SETTEXT, 0, (LPARAM)url);
}

void AddressBar::navigateToURL(HWND hDlg)
{
	wchar_t * str = new wchar_t(MAX_URL_LENGTH);
	*((wchar_t*) str) = MAX_URL_LENGTH;
	int len = SendMessage(hDlg, EM_GETLINE, 0, (LPARAM)str);
	BSTR bstr = SysAllocStringLen(str, len);
	if (AddressBar::mcruxView)
	{
		AddressBar::mcruxView->loadURL(bstr);
	}
	SysFreeString(bstr);
}