// -----------------------------***************----------------------------------
/*	
		To get the Microsoft debugger to display wchar_t arrays as Unicode
		Tools ->Options->DebugTab->enable Display_Unicode_Strings.
*/
// -----------------------------***************----------------------------------
#include "stdafx.h"

#include <STDDEF.H>		// atlconv.h needs this header
#include <tchar.h>		// definition of _T
#include <wtypes.h>		// definition of LPTSTR
#include <CRTDBG.H>		// needed when atlconv.h is included, contains def of _ASSERTE
#include <ATLCONV.H>	// define A2W

int main(int argc, char* argv[])
{

	wchar_t* pwcX;
	pwcX = L"ABCD"; // convert abc to unicode
	
	
	
	/* ------------ Generic Types ------------*/

	LPTSTR pmbA;		// since _MBCS is defined this maps to char*
	pmbA = _T("abc");	// since _MBCS is defined _T is removed by preprocessor



	
	/* ------------ String Functions for UNICODE strings ------------*/

	wchar_t* pwcY = new wchar_t[5]; // enough to copy pwcX
	
	// since _MBCS is defined simple lstrcpy will be
	// translated to lstrcpyA which expects
	// a multibyte character pointer, therefore we
	// cannot write
	// lstrcpy(pwcY, pwcX);  

	lstrcpyW(pwcY, pwcX);
	delete pwcY;


	 /* ------------ UNICODE -> MBCS conversion ------------*/

	// ATL conversion macros :
	// may be efficient because allocates memory on stack
	USES_CONVERSION;
	char* pmbB = W2A(pwcX);


    // C++ runtime Lib Conversion :
	// wcstombs() has to be called twice
	// how much space is required for the resulting mb string
	unsigned nSize = wcstombs(NULL, pwcX, SysStringLen(pwcX)) + 1;

    // Allocate string buffer and translate ANSI string into it.
    char* pmbC = new char[nSize];
	wcstombs(pmbC, pwcX, nSize);


	/* ------------ MBCS -> UNICODE conversion ------------*/

	// the ATL way
	pwcY = A2W(pmbC); // no need to clear memory allocated to pwcY
	delete pmbC;
	
	
	// now using the C++ runtime library
	char    *pmbD = "ABCDEFGHI K";
	nSize = _tcslen(pmbD);			// use generic strlen()
	wchar_t *pwcZ      = new wchar_t[ nSize ]; // also reserves space for the 4 Byte header

	int i = mbstowcs( pwcZ, pmbD, nSize ); 
	
	size_t nSizeWC = wcslen(pwcZ); // returns nSize+4 (4 byte header);
	delete pwcZ;

	// Dump memory leaks
	_CrtDumpMemoryLeaks();

	return 0;
}
