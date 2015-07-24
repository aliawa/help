/*  
//	Illustrating:
//  Comparisons with COleVarint using different data types
*/


#include "stdafx.h"


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



enum { E_STRING, E_LONG, E_DATE, E_EMPTY };

COleVariant GetVal(int x)
{
	switch (x)
	{
	case E_STRING:
		return COleVariant(_T("Hello"));

	case E_LONG:
		return COleVariant(2L);

	case E_DATE:
		return COleVariant(COleDateTime( 2000, 8, 14, 12, 30, 0 ));

	case E_EMPTY:
		return COleVariant();

	}
	return COleVariant(); // VT_EMPTY
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
		COleVariant OleVar;
		HRESULT Res;
		
		//
		// long
		//

		Res = VarCmp(GetVal(E_LONG),COleVariant(10L), LOCALE_USER_DEFAULT, NORM_IGNORECASE);
		ASSERT (Res == VARCMP_LT ); // 2 < 10

		//
		// empty (comparing interesting data types with empty)
		//
		
		OleVar = GetVal(E_EMPTY); // returns empty
		Res = VarCmp(GetVal(E_LONG),OleVar, LOCALE_USER_DEFAULT, NORM_IGNORECASE); 
		ASSERT (Res == VARCMP_GT ); // 2 > empty

		Res = VarCmp(OleVar, GetVal(E_LONG), LOCALE_USER_DEFAULT, NORM_IGNORECASE); 
		ASSERT (Res == VARCMP_LT ); // empty < 2

		Res = VarCmp(OleVar, GetVal(E_STRING), LOCALE_USER_DEFAULT, NORM_IGNORECASE); 
		ASSERT (Res == VARCMP_LT ); // empty < "Hello"

		Res = VarCmp(GetVal(E_STRING), OleVar,  LOCALE_USER_DEFAULT, NORM_IGNORECASE); 
		ASSERT (Res == VARCMP_GT ); // "Hello" > empty

		Res = VarCmp(OleVar, GetVal(E_DATE), LOCALE_USER_DEFAULT, NORM_IGNORECASE); 
		ASSERT (Res == VARCMP_LT ); // empty < 14.8.200

		Res = VarCmp(GetVal(E_DATE), OleVar,  LOCALE_USER_DEFAULT, NORM_IGNORECASE); 
		ASSERT (Res == VARCMP_GT ); // 14.8.200 > empty

		//
		// long <-> string   string <-> long
		//

		Res = VarCmp(GetVal(E_LONG),COleVariant("10"), LOCALE_USER_DEFAULT, NORM_IGNORECASE);
		ASSERT (Res == VARCMP_LT ); // 2 < "10" (string converted to long)

		Res = VarCmp(GetVal(E_STRING), GetVal(E_LONG), LOCALE_USER_DEFAULT, NORM_IGNORECASE);
		ASSERT (Res == VARCMP_GT ); // 2 > "Hello"  ("Hello" converted to long is 0)

		//
		// Date <-> Date 
		//

		COleDateTime d( 2000, 8, 15, 12, 30, 0 );
		Res = VarCmp(GetVal(E_DATE), COleVariant(d), LOCALE_USER_DEFAULT, NORM_IGNORECASE);
		ASSERT( Res == VARCMP_LT); // ( 14.8.2000 12:30:00 < 15.8.68 12:30:00 )
		
		
		d = COleDateTime ( 2000, 7, 15, 12, 30, 0 );
		Res = VarCmp(GetVal(E_DATE), COleVariant(d), LOCALE_USER_DEFAULT, NORM_IGNORECASE);
		ASSERT( Res == VARCMP_GT); // ( 15.7.2000 12:30:00 > 15.8.68 12:30:00 )
	
	}
	
	return 0;
}


