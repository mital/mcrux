#include "StdAfx.h"
#include "MCruxObject.h"

CMCruxObject::CMCruxObject()
{
}

CMCruxObject::~CMCruxObject()
{
}


STDMETHODIMP CMCruxObject::HelloWorld()
{
	::MessageBoxA(0, "CMCruxObject::helloworld called", "test", MB_OK);
	return S_OK;
}
