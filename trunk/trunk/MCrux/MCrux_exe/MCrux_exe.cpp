#include "stdafx.h"
#include "MCrux.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	MCrux mcrux;
	string appConfigFileWithFullPath = "c:\\mcrux\\myApplication.mcruxspec";
	mcrux.InitializeAndRunWith(appConfigFileWithFullPath);

	return 0;
}
