
// ----------------------------------------------------------------------
//
//          using STL find_if on cstring Arrays
//
//          ALSO: - using sizeof to find the size of an array of pointers
//                - using bind2nd with a self defined binary function
//
// ----------------------------------------------------------------------

//#include "stdafx.h"
#include <string.h>
#include <algorithm>     // find_if algorithm
#include <functional>    // find_if algorithm
#include <iostream>      // for cerr, cout



using namespace std;

// cstring comparison function object used in find_if
struct cstrCmp : public binary_function<const char*, const char*, bool>
{
	bool operator()(const char* p, const char* q)  const
	{
		return strcmp(p,q) == 0;
	}
};




int main(int argc, char* argv[])
{

    // An array of cstrings
    const char* OutputFormats[] = {"G723_53","G723_63","G711_A","G711_U"};

    //pointer to start of array
    const char** pStart = &OutputFormats[0];

    // pointer to end of array can be obtained by using sizeof operator
    const char** pEnd   = &OutputFormats[sizeof(OutputFormats)/4];

    // Let's say we want to find this string in the array
    char* stringToFind = "G711_A";

    const char** pElement = std::find_if (pStart, pEnd, bind2nd(cstrCmp(), stringToFind));

    if (pElement == pEnd)
        cout << "string not found" << endl;
    else if (pElement == pStart)
        cout << "empty range" << endl;
    else
        cout << "string found at location: " << pElement-pStart << endl;



    return 0;
}


