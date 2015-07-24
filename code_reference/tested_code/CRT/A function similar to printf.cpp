
//   ______________________________________ 

/*		A function similar to MFC Trace
*		A funcion similar to printf
*/
//   ______________________________________ 



#include <windows.h>
#include <cstring>
#include <cstdarg>
#include <cstdio>


void  MTRACE(const char *pszFormat, ...)
{
#ifdef _DEBUG
	char* szText = new char[1024 + strlen(pszFormat)];
	va_list args;

	va_start(args, pszFormat);
	vsprintf(szText, pszFormat, args);
	OutputDebugString(szText);
	delete szText;
	va_end(args);
#endif
}
