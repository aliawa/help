// OwnOleClientItemDlg.h : header file
//

#if !defined(AFX_OWNOLECLIENTITEMDLG_H__CFF2B2A4_0AEC_11D4_AFEF_00500413F521__INCLUDED_)
#define AFX_OWNOLECLIENTITEMDLG_H__CFF2B2A4_0AEC_11D4_AFEF_00500413F521__INCLUDED_

#include "Instantiater.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COwnOleClientItemDlg dialog

class COwnOleClientItemDlg : public CDialog
{
// Construction
public:
	COwnOleClientItemDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COwnOleClientItemDlg)
	enum { IDD = IDD_OWNOLECLIENTITEM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COwnOleClientItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CComObject<CInstantiater>* m_Instantiater;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COwnOleClientItemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButLaunch();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWNOLECLIENTITEMDLG_H__CFF2B2A4_0AEC_11D4_AFEF_00500413F521__INCLUDED_)
