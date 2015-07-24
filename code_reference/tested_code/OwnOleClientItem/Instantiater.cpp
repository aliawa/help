// Instantiater.cpp : implementation file
//

#include "stdafx.h"
#include "Instantiater.h"

#include <afxpriv.h> // USES_CONVERSION

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstantiater

//IMPLEMENT_DYNCREATE(CInstantiater, CCmdTarget)

CInstantiater::CInstantiater()
{
	InitObject();
}

CInstantiater::~CInstantiater()
{
	TRACE("Instantiater %s\n", "~CInstantiater");

	// release any references we may have to other objects
	ReleaseObjects();
}



/////////////////////////////////////////////////////////////////////////////
// CInstantiater message handlers

BOOL CInstantiater::FinishCreate(SCODE sc)
{
	USES_CONVERSION;
	
	// check return code from create function
	CheckGeneral(sc);

	TRY
	{
		// m_lpObject is currently an IUnknown, convert to IOleObject
		if (m_lpObject != NULL)
		{
			IUnknown* lpUnk = m_lpObject;
			
			sc = lpUnk->QueryInterface(IID_IOleObject, reinterpret_cast<void**>(&m_lpObject));
			//m_lpObject = QUERYINTERFACE(lpUnk, IOleObject);
			lpUnk->Release();
			if (m_lpObject == NULL)
				AfxThrowOleException(E_OUTOFMEMORY);
		}
		
		
		// cache the IViewObject interface
		sc = m_lpObject->QueryInterface(IID_IViewObject2, reinterpret_cast<void**>(&m_lpViewObject));
		CheckGeneral(sc);
		ASSERT(m_lpViewObject != NULL);
		
		
		/* ****------ Establish Advisory Connection ----------***** */
		
		// --- if IAdviseSink is implemented by CTestSink then ---
		// --- uncomment the following lines

		//sc = CComObject<CTestSink>::CreateInstance(&m_pMySink);
		//CheckGeneral(sc);
		//IAdviseSink* lpAdviseSink = NULL;
		//sc = m_pMySink->QueryInterface(IID_IAdviseSink,reinterpret_cast<void**>(&lpAdviseSink));
		//CheckGeneral(sc);

		// --- if IAdviseSink is implemented by this class then ---
		// --- uncomment the following lines
		IAdviseSink* lpAdviseSink = dynamic_cast<IAdviseSink*>(this);
		ASSERT(lpAdviseSink != NULL);
		
		sc = m_lpObject->Advise(lpAdviseSink, &m_dwConnection);
		CheckGeneral(sc);
		
		VERIFY(m_lpViewObject->SetAdvise(DVASPECT_CONTENT, 0, lpAdviseSink)
			== S_OK);
		
		// all items are "contained" -- this makes our reference to this object
		//  weak -- which is needed for links to embedding silent update.
		OleSetContainedObject(m_lpObject, TRUE);
		
	}
	CATCH_ALL(e)
	{
		ReleaseObjects();  // release the object just in case
		e->Delete();
		return FALSE;
	}
	END_CATCH_ALL
		
	// otherwise no errors, return success!
	return TRUE;
}



// modification of COleClientItem::CreateLinkFromFile
BOOL CInstantiater::LinkAndActivate(LPCTSTR lpszFileName)
{
	USES_CONVERSION;
	
	ASSERT(m_lpObject == NULL);     // one time only
	
	// get storage for the object via virtual function call
	GetItemStorageFlat();
	ASSERT(m_lpStorage != NULL);
	
	// How does the client want to show the object in its window
	OLERENDER render = OLERENDER_NONE;
	// What kind of data clipboard format the client would like to 
	// have in order to draw the object in its window
	LPFORMATETC lpFormatEtc = NULL;
	// Of importance for in place activation and embedded objects
	LPOLECLIENTSITE lpClientSite = NULL;
	
	// lpszFileName -- path of the file to be shown
	// IID_IUnknown -- the requested interface from the server for 
	//				   later communication with it
	// m_lpStorage  -- memory for the compound file object
	// m_lpObject	-- Address of output variable that receives 
    //				   the interface pointer requested in riid
	SCODE sc = ::OleCreateLinkToFile(T2COLE(lpszFileName),
		IID_IUnknown, render, lpFormatEtc, lpClientSite, m_lpStorage,
		reinterpret_cast<void**>(&m_lpObject));
	BOOL bResult = FinishCreate(sc);

	// Activate the object
	if (bResult)
	{
		// 1st param -- action to be performed
		// 2nd param -- windows message struct
		// 3rd param -- Pointer to IOleClientSite 
		// 4th param -- always 0
		// 5th param -- doc window containing the object
		// 6th param -- objects bounding rectangle
		SCODE sc = m_lpObject->DoVerb(OLEIVERB_SHOW, NULL, NULL, 0, NULL, NULL);
		CheckGeneral(sc);
	}
	
	return bResult;
}



void CInstantiater::GetItemStorageFlat()
{
	ASSERT(m_lpStorage == NULL);
	ASSERT(m_lpLockBytes == NULL);
	
	// Create a byte array in global memory supporting ILockBytes
	SCODE sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &m_lpLockBytes);
	if (sc != S_OK)
		AfxThrowOleException(sc);
	ASSERT(m_lpLockBytes != NULL);
	
	// Open a compound file supporting IStorage
	sc = ::StgCreateDocfileOnILockBytes(m_lpLockBytes,
		STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, 0, &m_lpStorage);
	if (sc != S_OK)
	{
		VERIFY(m_lpLockBytes->Release() == 0);
		m_lpLockBytes = NULL;
		AfxThrowOleException(sc);
	}
	ASSERT(m_lpStorage != NULL);
	
}


void CInstantiater::CheckGeneral(SCODE sc)
// throw exception if not ok to continue
{
	// check for error
	if (sc != S_OK)
	{
		if (!FAILED(sc))
		{
#ifdef _DEBUG
			// warn about non-NULL success codes
			TRACE1("Warning: operation returned scode = %s.\n",
				AfxGetFullScodeString(sc));
#endif
			return;
		}
		// this error wasn't expected, so throw an exception
		AfxThrowOleException(sc);
	}
}


void CInstantiater::ReleaseObjects(OLECLOSE dwCloseOption)
{
	TRACE("Instantiater %s\n", "ReleaseObjects");
	// cleanup view advise
	if (m_lpViewObject != NULL)
	{
		DWORD dwAspect;
		IAdviseSink* pAdviseSink = NULL;
		
		
		//pAdviseSink = NULL;
		VERIFY(m_lpViewObject->GetAdvise(&dwAspect, NULL, &pAdviseSink) == S_OK);
		if( pAdviseSink != NULL )
			pAdviseSink->Release();
		TRACE("%%%% --- pAdviseSink released\n");
		
		VERIFY(m_lpViewObject->SetAdvise(dwAspect, 0, NULL) == S_OK);
		m_lpViewObject->Release();
		TRACE("%%%% --- lpViewObject released\n");
	}
	
	// cleanup the OLE object itself
	if (m_lpObject != NULL)
	{
		// cleanup object advise
		if (m_dwConnection != 0)
		{
			VERIFY(m_lpObject->Unadvise(m_dwConnection) == S_OK);
			TRACE("%%%% --- m_lpObject->Unadvise");
			m_dwConnection = 0;
		}
		
		// close object and save (except now when called from destructor)
		//  (NOTE: errors are _not_ reported as an exception)
		// e.g., close Word without saving  dwCloseOption = OLECLOSE_NOSAVE
		m_lpObject->Close(dwCloseOption);
		m_lpObject->Release();
		TRACE("!!! --- m_lpObject released\n");
	}
	
	// cleanup storage related data
	if (m_lpStorage)
		m_lpStorage->Release();
	if (m_lpLockBytes)
		m_lpLockBytes->Release();
	TRACE("!!! --- end ReleaseObjects\n");

	
}

void CInstantiater::Reset()
{
	if (m_lpObject)
	{
		ReleaseObjects();
		InitObject();
	}
	
}

void CInstantiater::InitObject()
{
	m_lpViewObject	= NULL;
	m_lpObject		= NULL;
	m_lpStorage		= NULL;  // provides storage for m_lpObject
	m_lpLockBytes	= NULL;  // part of implementation of m_lpStorage
	m_dwConnection	= 0;
}


/////////////////////////////////////////////////////////////////////////////
// IAdviseSink

STDMETHODIMP_(void) CInstantiater::OnClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	AfxMessageBox("You Closed it");
	Reset();

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CInstantiater::OnDataChange(FORMATETC *pFormatetc, STGMEDIUM *pStgmed)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	AfxMessageBox("You Closed it");

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CInstantiater::OnRename(IMoniker *pmk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CInstantiater::OnSave()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

STDMETHODIMP_(void) CInstantiater::OnViewChange(DWORD dwAspect, LONG lindex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

}

