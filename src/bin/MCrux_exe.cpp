/**
 * copyright (C) 2009 Mital Vora. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of MCrux nor the names of its contributors may be 
 *     used to endorse or promote products derived from this software 
 *     without specific prior written permission.
 *
 * @author: Mital Vora.
 **/
#ifdef WIN32
#include "../win32/stdafx.h"

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#endif

#include <MCrux/MCrux.h>

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
	//string appConfigFileWithFullPath = "C:\\mcrux\\newapi\\window_create.mcruxspec";
	string appConfigFileWithFullPath = "C:\\mcrux\\myapplication.mcruxspec";
	mcrux.InitializeAndRunWith(appConfigFileWithFullPath);

	return 0;
}
