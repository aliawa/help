// MySink.h : Declaration of the CMySink

#ifndef __MYSINK_H_
#define __MYSINK_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMySink
class ATL_NO_VTABLE CMySink : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMySink, &CLSID_MySink>,
	public IDispatchImpl<IMySink, &IID_IMySink, &LIBID_OwnOleClientItemLib>,
	public IDispatchImpl<IAdviseSink, &IID_IAdviseSink, &LIBID_OwnOleClientItemLib>

	{
public:
	CMySink()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYSINK)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMySink)
	COM_INTERFACE_ENTRY(IMySink)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IAdviseSink)
END_COM_MAP()

// IAdviseSink
public:
	STDMETHOD_(void, OnViewChange)(DWORD dwAspect, LONG lindex);
	STDMETHOD_(void, OnSave)();
	STDMETHOD_(void, OnRename)(IMoniker* pmk);
	STDMETHOD_(void, OnDataChange)(FORMATETC* pFormatetc, STGMEDIUM* pStgmed);
	STDMETHOD_(void, OnClose)();

// IMySink
public:
};

#endif //__MYSINK_H_
