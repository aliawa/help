// OwnOleClientItem.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "OwnOleClientItem.h"
#include "OwnOleClientItemDlg.h"
#include <initguid.h>
#include "OwnOleClientItem_i.c"
//#include "MySink.h"
//#include "MyAdviseSink.h"
//#include "TestSink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnOleClientItemApp

BEGIN_MESSAGE_MAP(COwnOleClientItemApp, CWinApp)
	//{{AFX_MSG_MAP(COwnOleClientItemApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COwnOleClientItemApp construction

COwnOleClientItemApp::COwnOleClientItemApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COwnOleClientItemApp object

COwnOleClientItemApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COwnOleClientItemApp initialization

BOOL COwnOleClientItemApp::InitInstance()
{
	AfxOleInit();
	if (!InitATL())
		return FALSE;

	AfxEnableControlContainer();
	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	COwnOleClientItemDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

	
COwnOleClientItemModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
//OBJECT_ENTRY(CLSID_MySink, CMySink)
//OBJECT_ENTRY(CLSID_MyAdviseSink, CMyAdviseSink)
//OBJECT_ENTRY(CLSID_TestSink, CTestSink)
END_OBJECT_MAP()

LONG COwnOleClientItemModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG COwnOleClientItemModule::Lock()
{
	AfxOleLockApp();
	return 1;
}


int COwnOleClientItemApp::ExitInstance()
{
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	}

	return CWinApp::ExitInstance();

}

BOOL COwnOleClientItemApp::InitATL()
{
	m_bATLInited = TRUE;

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	return TRUE;

}
