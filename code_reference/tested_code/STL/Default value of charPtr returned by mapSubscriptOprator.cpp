// ---------------------------------***********-----------------------------
/*				map operator[] returns a default value if the key
				is not found in the map. 
				What is the default value for char* ??
*/
// ---------------------------------***********-----------------------------

#include "stdafx.h"
#include <map>



int main(int argc, char* argv[])
{
	std::map<long, char*> xmap;

	char* pStr = xmap[2];		// pStr = NULL, which is correct
								// A pair (2,NULL) is created

	pStr = new char[4];
	strcpy (pStr, "abc");
	xmap[2] = pStr;				

	char* pStr2;
	pStr2 = xmap[2];			// A pair (2, "abc") is created
	pStr2 = "y";				// This does not affect xmap[2] as confirmed below
	
	char* pStr3 = xmap[2];		// pStr3 = "abc"
	
	
	return 0;
}
