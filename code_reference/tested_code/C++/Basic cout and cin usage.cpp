// ----------------------------------------------------------
//
//              Basic input and output in c++
//
//      read a line from standard input and  then print it 
//      
//-----------------------------------------------------------

#include "stdafx.h"
#include <iostream>   // needed for cin and cout

#include <string>     // needed for getline(std_stream, string) function
using namespace std;


#define METHOD1
#undef  METHOD2
#undef  METHOD3


int main(int argc, char* argv[])
{
// --------- method 3 ---------------
//   simple method

#ifdef METHOD1

    char c;
    while (cin.get(c)) 
    {
        if (c == '/')  // replace all '/' to '\'
            c = '\\';
        cout.put(c);
    }
#endif
    

// --------- method 3 ---------------
//   using getline() instead of get()

#ifdef METHOD2

    char buff[256];
    cin.getline(buff, 256, '\n');
    cout << buff;

#endif


// --------- method 3 ---------------
//   using string as buffer


#ifdef METHOD3

    string sline;
    getline(cin, sline);
    cout << sline;

#endif     
    return 0;
}
