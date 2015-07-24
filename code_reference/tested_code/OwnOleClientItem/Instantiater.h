#if !defined(AFX_INSTANTIATER_H__CFF2B2AE_0AEC_11D4_AFEF_00500413F521__INCLUDED_)
#define AFX_INSTANTIATER_H__CFF2B2AE_0AEC_11D4_AFEF_00500413F521__INCLUDED_

#include "OwnOleClientItem_i.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Instantiater.h : header file


/////////////////////////////////////////////////////////////////////////////
// CInstantiater command target

class ATL_NO_VTABLE CInstantiater : /*public CObject,*/
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInstantiater, &CLSID_Instantiater>,
	public IAdviseSink

{
// Construction Destruction
public:
	CInstantiater();
	virtual ~CInstantiater();

	BEGIN_COM_MAP(CInstantiater)
		COM_INTERFACE_ENTRY(IAdviseSink)
	END_COM_MAP()

// Data
protected:
	IOleObject*		m_lpObject;
	IStorage*		m_lpStorage;	// provides storage for m_lpObject
	ILockBytes*		m_lpLockBytes;  // part of implementation of m_lpStorage
	DWORD			m_dwConnection; // advise connection to the m_lpObject
	LPVIEWOBJECT2	m_lpViewObject;	// IViewObject for IOleObject above

	

// IAdviseSink
public:
	STDMETHOD_(void, OnViewChange)(DWORD dwAspect, LONG lindex);
	STDMETHOD_(void, OnSave)();
	STDMETHOD_(void, OnRename)(IMoniker* pmk);
	STDMETHOD_(void, OnDataChange)(FORMATETC* pFormatetc, STGMEDIUM* pStgmed);
	STDMETHOD_(void, OnClose)();


// Operations
public:
	BOOL LinkAndActivate(LPCTSTR lpszFileName);
	void Reset();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstantiater)
	public:
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitObject();
	BOOL FinishCreate(SCODE sc);
	void GetItemStorageFlat();
	void CheckGeneral(SCODE sc);
	void ReleaseObjects(OLECLOSE dwCloseOption = OLECLOSE_NOSAVE);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTANTIATER_H__CFF2B2AE_0AEC_11D4_AFEF_00500413F521__INCLUDED_)
