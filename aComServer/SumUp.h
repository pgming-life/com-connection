#pragma once

#include "resource.h"
#include "CServerCP.h"

class ATL_NO_VTABLE CSumUp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSumUp, &CLSID_SumUp>,
	public IConnectionPointContainerImpl<CSumUp>,
	public IDispatchImpl<ISumUp, &IID_ISumUp, &LIBID_CONNECTIONCOMLib>,
	public CProxy_ISumUpEvents<CSumUp>
{
public:
	CSumUp(){}

DECLARE_REGISTRY_RESOURCEID(IDR_SUMUP)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSumUp)
	COM_INTERFACE_ENTRY(ISumUp)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSumUp)
CONNECTION_POINT_ENTRY(IID__ISumUpEvents)
END_CONNECTION_POINT_MAP()

// ÉÅÉ\ÉbÉh
STDMETHOD(SumUp)(int a,int b);
};