#pragma once

#include "MCrux.h"
#include "Resource.h"
#include "MCruxWebView.h"

class ATL_NO_VTABLE CMCruxObject
: public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CMCruxObject, &CLSID_MCruxObject>,
  public IDispatchImpl<IMCrux, &IID_IMCrux, &LIBID_MCruxLib, 1, 0>
{
	MCruxWebView webView;

public:

	BEGIN_COM_MAP(CMCruxObject)
		COM_INTERFACE_ENTRY(IMCrux)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_REGISTRY_RESOURCEID(IDR_MCRUXOBJECT)

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	CMCruxObject();

	virtual ~CMCruxObject();

	STDMETHOD(createWebView)(LONG* hParent);

};

OBJECT_ENTRY_AUTO(__uuidof(MCruxObject), CMCruxObject)
