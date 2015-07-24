
// ----------------------------------------------------------------------
//
//          writing and reading from a file in binary format
//          using C++ file streams.
//                            
//          ALSO: use of exit() function
//          AND : Formatting of stream output using ios_base flags
//
// ----------------------------------------------------------------------

#include "stdafx.h"

#include <fstream>      // streams to files and stream from files
#include <iostream>     // for cerr
#include <cstdlib>      // for exit()



using namespace std;

// output file
#define FILE_TO_OPEN "test.dat"

// some sample data
unsigned char g_data[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};



// An error handling function
void error(const char* p, const char* p2 = "")
{
    cerr <<p<<' ' << p2<< '\n';

    // like the return value of main(), exit()'s argument is returned
    // to the system as the value of the program. (see $9.4.1.1)
    exit(1);
}


// prints data in hexadecimal format
void debugOutput(const unsigned char* pData, int sizeOfData)
{
    // set the base of the integer to be hexadecimal
    cout.setf(ios_base::hex, ios_base::basefield);
    
    // show '0x' before hexadecimal numbers
    cout.setf(ios_base::showbase);
    
    for (int k = 0; k<sizeOfData; ++k)
    {
        cout << int(pData[k]) << ' ';
    }
    cout << endl;
}



int main(int argc, char* argv[])
{

    // pointer to data, 
    // NOTE: The ostream.write() takes const char* as pointer to data
    const char* pData = reinterpret_cast<const char*>(&g_data[0]); 
    int sizeOfData    = sizeof(g_data);

    // buffer for reading data
    unsigned char buff[16];
    

    // File stream classes
    // ----------------------
    // To open a file for output            --> create an object of type ofstream
    // To open a file for input             --> create an object of type ifstream
    // To open a file for output and input  --> create an object of type fstream


    // open a file for output in binary mode
	ofstream strmFile(FILE_TO_OPEN, std::ios_base::binary);
    if (!strmFile) error("cannot open output file", FILE_TO_OPEN);

    // write data into file
    for (int i=0; i<10; ++i)
        strmFile.write(pData, sizeOfData);

    // no need to close the file if 'strmFile' goes out of scope
    // but now we will close it because we want to reopen for reading
    strmFile.close();




    // open the file for reading in binary mode
    ifstream strmInputFile(FILE_TO_OPEN, std::ios_base::binary);
    if (!strmInputFile) error("cannot open input file", FILE_TO_OPEN);

    // read 10 records.
    for (int j=0; j<10; ++j)
    {
        // read sizeOfData bytes from the file
        strmInputFile.read(reinterpret_cast<char*>(&buff[0]), sizeOfData);

        // see what have we read
        debugOutput(&buff[0], sizeOfData);
    }

    return 0;
}


