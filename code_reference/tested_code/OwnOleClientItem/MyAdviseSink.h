// MyAdviseSink.h : Declaration of the CMyAdviseSink

#ifndef __MYADVISESINK_H_
#define __MYADVISESINK_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyAdviseSink
class ATL_NO_VTABLE CMyAdviseSink : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyAdviseSink, &CLSID_MyAdviseSink>,
	public IMyAdviseSink
{
public:
	CMyAdviseSink()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYADVISESINK)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyAdviseSink)
	COM_INTERFACE_ENTRY(IMyAdviseSink)
END_COM_MAP()

// IMyAdviseSink
public:
	STDMETHOD_(void, OnViewChange)(DWORD dwAspect, LONG lindex);
	STDMETHOD_(void, OnSave)();
	STDMETHOD_(void, OnRename)(IMoniker* pmk);
	STDMETHOD_(void, OnDataChange)(FORMATETC* pFormatetc, STGMEDIUM* pStgmed);
	STDMETHOD_(void, OnClose)();
};

#endif //__MYADVISESINK_H_
