// Socket.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SocketJSObject.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif


__declspec(dllexport) MObject * getMCruxPlugin(JSContextRef context)
{
	return new SocketJSObject(context);
}

