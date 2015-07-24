//		----------------------------------------------------------

//				Diagnostic output to the debugger
//		Outputs to the VC++ output window if run in Debug mode
//		otherwise to Dbmon if that is running.
//
//		----------------------------------------------------------
//					Defines for faster builds
//		Also demonstrating defines for faster builds, these macros
//		are also defined by VC_EXTRALEAN for MFC apps.

//		----------------------------------------------------------


#include "stdafx.h"

#define WIN32_EXTRA_LEAN
#define NOSERVICE
#define NOMCX
#define NOIME
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#ifndef NO_ANSIUNI_ONLY
#ifdef _UNICODE
#define UNICODE_ONLY
#else
#define ANSI_ONLY
#endif
#endif //!NO_ANSIUNI_ONLY


#include <windows.h>
#include <winbase.h>

int main(int argc, char* argv[])
{
	printf("Hello Next World!\n");

	OutputDebugString("Hello Next World!\n");
	return 0;
}

