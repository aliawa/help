// MyAdviseSink.cpp : Implementation of CMyAdviseSink
#include "stdafx.h"
#include "OwnOleClientItem.h"
#include "MyAdviseSink.h"

/////////////////////////////////////////////////////////////////////////////
// CMyAdviseSink


STDMETHODIMP_(void) CMyAdviseSink::OnClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CMyAdviseSink::OnDataChange(FORMATETC *pFormatetc, STGMEDIUM *pStgmed)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CMyAdviseSink::OnRename(IMoniker *pmk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CMyAdviseSink::OnSave()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CMyAdviseSink::OnViewChange(DWORD dwAspect, LONG lindex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}
