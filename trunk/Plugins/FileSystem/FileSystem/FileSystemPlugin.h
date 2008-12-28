#pragma once

#include <MCrux/MCruxPluginClassImpl.h>

#include "FileSystem.h"


class CFileSystemPlugin
	: public CComObjectRootEx<CComSingleThreadModel>,
	  public CComCoClass<CFileSystemPlugin, &CLSID_FileSystemPlugin>,
	  public IDispatchImpl<IMCruxPlugin, &IID_IMCruxPlugin, &LIBID_FileSystemLib, 1, 0>,
	  public MCruxPluginClassImpl<CFileSystemPlugin>
{
public:
	CFileSystemPlugin();
	~CFileSystemPlugin();
};

BEGIN_MCRUX_FUNCTION_MAP(CFileSystemPlugin)
//		MCRUX_FUNCTION_MAP_ENTRY(
END_MCRUX_FUNCTION_MAP()
