// MCrux.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include <commctrl.h>
#include <objbase.h>
#include <shlwapi.h>
#include <wininet.h>

#include "MCrux.h"

#include "windowsnative/MCruxWindow.h"
#include "windowsnative/MCruxWindowConfiguration.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif


MCrux::MCrux()
{
}


MCrux::~MCrux()
{
	return;
}

void MCrux::Initialize()
{
	// Initialize Common controls
    INITCOMMONCONTROLSEX InitCtrlEx;

    InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCtrlEx.dwICC  = 0x00004000; //ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&InitCtrlEx);

	MCruxWindow::initWindowClass(GetModuleHandle(NULL));

	// Init COM
    OleInitialize(NULL);
}

void MCrux::UnInitialize()
{
    // Shut down COM.
    OleUninitialize();
}


bool MCrux::InitializeAndRunWith(const string & mcruxAppConfigFileName)
{
	Initialize();

	HINSTANCE hInstance = GetModuleHandle(NULL);
	//MCruxWindowConfiguration mainWindowConfig(TEXT("http://www.google.com"));
	MCruxWindowConfiguration mainWindowConfig(TEXT("C:/Users/mital/Documents/main.html"));
	//MCruxWindowConfiguration mainWindowConfig(TEXT("C:/main.html"));
	MCruxWindow * mainWindow = new MCruxWindow(hInstance, &mainWindowConfig);
	mainWindow->ShowWindow();
	mainWindow->UpdateWindow();

	HACCEL hAccelTable = NULL;// LoadAccelerators(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_blah));

	MSG msg;
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnInitialize();
	return false;
}
