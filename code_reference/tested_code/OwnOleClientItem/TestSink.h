// TestSink.h : Declaration of the CTestSink

#ifndef __TESTSINK_H_
#define __TESTSINK_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestSink
class ATL_NO_VTABLE CTestSink : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestSink, &CLSID_TestSink>,
	public ITestSink, public IAdviseSink
{
public:
	CTestSink()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTSINK)
DECLARE_NOT_AGGREGATABLE(CTestSink)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestSink)
	COM_INTERFACE_ENTRY(ITestSink)
	COM_INTERFACE_ENTRY(IAdviseSink)
END_COM_MAP()

// ITestSink
public:
	// IAdviseSink
	STDMETHOD_(void, OnDataChange)(FORMATETC* /*pFormatetc*/, STGMEDIUM* /*pStgmed*/)
	{
	}
	STDMETHOD_(void, OnViewChange)(DWORD /*dwAspect*/, LONG /*lindex*/)
	{
	}
	STDMETHOD_(void, OnRename)(IMoniker* /*pmk*/)
	{
	}
	STDMETHOD_(void, OnSave)()
	{
	}
	STDMETHOD_(void, OnClose)()
	{
		AfxMessageBox("KILLING");
	}


};

#endif //__TESTSINK_H_
