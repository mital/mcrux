#ifndef _MCRUX_EXPORT_H_
#define _MCRUX_EXPORT_H_

#ifdef _MCRUXDLL
#define MCRUX_CLASS_TAG __declspec(dllexport)
#else
#define MCRUX_CLASS_TAG __declspec(dllimport)
#endif

#endif // _MCRUX_EXPORT_H_