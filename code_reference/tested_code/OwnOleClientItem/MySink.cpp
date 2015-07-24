// MySink.cpp : Implementation of CMySink
#include "stdafx.h"
#include "OwnOleClientItem.h"
#include "MySink.h"

/////////////////////////////////////////////////////////////////////////////
// CMySink

STDMETHODIMP_(void) CMySink::OnClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	AfxMessageBox("You Closed it");
	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CMySink::OnDataChange(FORMATETC *pFormatetc, STGMEDIUM *pStgmed)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	AfxMessageBox("You Closed it");

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CMySink::OnRename(IMoniker *pmk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CMySink::OnSave()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CMySink::OnViewChange(DWORD dwAspect, LONG lindex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}
