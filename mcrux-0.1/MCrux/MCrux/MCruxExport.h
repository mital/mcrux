#ifndef _MCRUX_EXPORT_H_
#define _MCRUX_EXPORT_H_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MCRUX_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MCRUX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MCRUX_EXPORTS
#define MCRUX_API __declspec(dllexport)
#else
#define MCRUX_API __declspec(dllimport)
#endif

#endif // _MCRUX_EXPORT_H_