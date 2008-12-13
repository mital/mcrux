#include "StdAfx.h"
#include <comdef.h>

#include "MCruxAddressBar.h"

long MCruxAddressBar::DefEditProc = NULL;

LRESULT CALLBACK MCruxAddressBar::MyEditProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case WM_CHAR:
            if (wParam == 13)
			{
				// Enter Key
				::MessageBoxA(0, "test", "test", MB_OK);
                wchar_t strPtr[MAX_URL_LENGTH];
                *((LPWORD)strPtr) = MAX_URL_LENGTH; 
                int strLen = SendMessage(hDlg, EM_GETLINE, 0, (LPARAM)strPtr);

                BSTR bstr = SysAllocStringLen(strPtr, strLen);
                //loadURL(bstr);
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


MCruxAddressBar::MCruxAddressBar(HINSTANCE hInstance, HWND hParentWnd)
{
    hWndAddressBar = CreateWindow(L"EDIT", 0,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOVSCROLL, 
		0, 0, 0, 0,
		hParentWnd,
		0,
		hInstance, 0);

    DefEditProc = GetWindowLong(hWndAddressBar, GWL_WNDPROC);
    SetWindowLong(hWndAddressBar, GWL_WNDPROC,(long)MyEditProc);
    SetFocus(hWndAddressBar);
}

MCruxAddressBar::~MCruxAddressBar()
{
}


HWND MCruxAddressBar::getAddressBarWindow() const
{
	return hWndAddressBar;
}
