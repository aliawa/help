// OwnOleClientItem.h : main header file for the OWNOLECLIENTITEM application
//

#if !defined(AFX_OWNOLECLIENTITEM_H__CFF2B2A2_0AEC_11D4_AFEF_00500413F521__INCLUDED_)
#define AFX_OWNOLECLIENTITEM_H__CFF2B2A2_0AEC_11D4_AFEF_00500413F521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "OwnOleClientItem_i.h"

/////////////////////////////////////////////////////////////////////////////
// COwnOleClientItemApp:
// See OwnOleClientItem.cpp for the implementation of this class
//

class COwnOleClientItemApp : public CWinApp
{
public:
	COwnOleClientItemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COwnOleClientItemApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COwnOleClientItemApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWNOLECLIENTITEM_H__CFF2B2A2_0AEC_11D4_AFEF_00500413F521__INCLUDED_)
