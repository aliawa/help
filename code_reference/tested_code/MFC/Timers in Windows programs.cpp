//|
//| --------- How to use timers in a windows program ---------
//|
//| 1. Provide callBackFunction func() and use
//|    ::SetTimer(NULL, 0, durationInMs,  func);
//|
//| 2. Provide callBackFunction func() and use
//|    ::SetTimer(handleOfWindow, timerId, durationInMs,  func);
//|
//| 3. Provide handler for WM_TIMER message and use
//|    ::SetTimer(handleOfWindow, timerId, durationInMs, NULL);
//| 
//| 4. like 2 and 3 but use
//|    CWnd::SetTimer(timerId, durationInMs, ...);
//|

#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//| we will store the values returned by the SetTimer function in these
//| variables
UINT nTimer1;
UINT nTimer2;

//| This function will be called by the
//| default window procedure  
//| when it processes WM_TIMER. 
//|
//| The windows procedure knows which function to call because 
//| lparam of WM_TIMER contains the address of this function.
//|
//| NOTE: This also means that the thread which calls SetTimer()
//| must also GetMessage() from the windows message queue and
//| DispatchMessage() it to windows procedure so that it can
//| handle WM_TIMER
//|
VOID CALLBACK TimerProc1(
  HWND hwnd,     // this is parameter 1 of SetTimer()
  UINT uMsg,     // WM_TIMER message
  UINT idEvent,  // the value in SetTimer(), 2nd parameter
  DWORD dwTime   // current system time
)
{
    TRACE ("Proc 1\n");
}


//| This function will be called by the
//| default window procedure  
//| when it processes WM_TIMER. 
//|
VOID CALLBACK TimerProc2(
  HWND hwnd,     // NULL in this case
  UINT uMsg,     // WM_TIMER message
  UINT idEvent,  // in this case this value == nTimer2(the timer id);
  DWORD dwTime   // current system time
)
{
    TRACE ("Proc 2\n");
    int i = idEvent;
}


 
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog

CTestDlgDlg::CTestDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_DRAWITEM()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	//ON_COMMAND(IDC_BTN_TEST, OnTestBtn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg message handlers

BOOL CTestDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//* -------------- extra initialization ------------------

    //|set timer with windows handle set, 
    //|must provide timerId in this case
    //|NOTE: if you use CWnd::SetTimer() no
    //|need to use windows handle
    nTimer1 = ::SetTimer(m_hWnd, 3, 60, TimerProc1);

    //|set timer with no windows handle, 
    //|must save the id returned for KillTimer()
    nTimer2 = ::SetTimer(NULL, 0, 100, TimerProc2);

	//* -------------- end extra initialization --------------
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlgDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestDlgDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CTestDlgDlg::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	int y =0;
}


// called by framework when ownerdraw property set
void CTestDlgDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// Retrieve the button's caption
	TCHAR buffer[20];
	GetDlgItem(nIDCtl)->GetWindowText(buffer, 20);

	// has something regarding selection changed
	if (lpDrawItemStruct->itemAction & ODA_SELECT)
	{
		// what is the current selection state of the button
		if (lpDrawItemStruct->itemState & ODS_SELECTED)
			TRACE("selected %s\n", buffer);
		else
			TRACE("unselected %s\n", buffer);
	}
	DrawCustomButton(lpDrawItemStruct, &buffer[0]);
}



// draws a rectangular button
void CTestDlgDlg::DrawCustomButton(DRAWITEMSTRUCT* pDI, char* caption)
{
	CDC dc;
	dc.Attach(pDI->hDC);
	
    switch (pDI->itemAction) {

	// draw the whole thing
    case ODA_DRAWENTIRE: 
		// draw the button
		dc.DrawFrameControl(&pDI->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH);

		// draw the text
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(caption, strlen(caption), &pDI->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		break;

		// draw on change in selection state
    case ODA_SELECT: 
		{
			CRect textRect(pDI->rcItem);

			if (pDI->itemState & ODS_SELECTED)
			{
				dc.DrawFrameControl(&pDI->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
				textRect.OffsetRect(1,1); // text offset for pushed button
			}
			else
				dc.DrawFrameControl(&pDI->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH);
			
			// draw the text
			dc.SetBkMode(TRANSPARENT);
			dc.DrawText(caption, strlen(caption), textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			break;
		}

	// drawing when the button received input focus
	case ODA_FOCUS:
		// Draw a frame around the box
		CBrush pBlackBrush(COLORREF(0));
		dc.FrameRect(&pDI->rcItem,&pBlackBrush);

		// draw the dotted focus rect
		CRect pRec(pDI->rcItem);
		pRec.DeflateRect(3,3);
		dc.DrawFocusRect(pRec);
		
		break;

	}
}

void CTestDlgDlg::OnTestBtn()
{
	TRACE("kkk\n");
}


//|
//| Handler for WM_DESTROY
//| 
void CTestDlgDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//| clear the timer started with a windows
    //| handle as its first parameter
    //| NOTE if you use CWnd::KillTimer then
    //| no need to provice m_hWnd
    ::KillTimer(m_hWnd, 3);
	
	//| clear the timer started without a windows
    //| handle
    ::KillTimer(NULL, nTimer2);
}
