/*  demonstrating :
//	Using COleVariant to convert between different data types
//
//	Compiling:
//  Link: tls15d.lib  OutputDir: C:/RtoDev/bind (for tls15d.dll)
//
*/

#include "stdafx.h"

#include <rw/cstring.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// The one and only application object
//
CWinApp theApp;

using namespace std;


COleVariant GetVal(int x)
{
	switch (x)
	{
	case 1:
		return COleVariant(_T("Hello"));
	case 2:
		return COleVariant(1L);
	case 3:
		return COleVariant(COleDateTime( 2000, 8, 14, 12, 30, 0 ));
	case 4:
		RWCString x("XXX");
		return COleVariant(x.data());
	}
	return COleVariant();
}



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	// initialize MFC
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		return 1;
	}
	else
	{
		
		// String literal
		COleVariant OleVar = GetVal(1);
		OleVar.ChangeType(VT_BSTR);
		CString cs = CString(OleVar.bstrVal);
		
		// Long
		OleVar = GetVal(2);
		OleVar.ChangeType(VT_BSTR);
		cs = CString(OleVar.bstrVal);
		
		// COleDateTime
		OleVar = GetVal(3);
		OleVar.ChangeType(VT_BSTR);
		cs = CString(OleVar.bstrVal);
		
		// RWCString
		OleVar = GetVal(4);
		OleVar.ChangeType(VT_BSTR);
		cs = CString(OleVar.bstrVal);
		
		// Empty
		OleVar = GetVal(5000);
		OleVar.ChangeType(VT_BSTR);
		cs = CString(OleVar.bstrVal);
		
	}
	
	return 0;
}


