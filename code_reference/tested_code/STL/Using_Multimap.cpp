//
// - Testing Different Hash Functions 
// - Using a multimap to study hash function
//   multimap is required because the different keys can produce the same hash value
//   Note: the contents of multimap are automatically sorted by key
//

//#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <map>

//#include "types.h"

using namespace std;



const char* Keys[] = 
{
    "PCMU",    
    "GSM",       
    "G723",      
    "DVI4",      
    "DVI4",      
    "LPC",       
    "PCMA",      
    "G722",      
    "L16",       
    "L16",       
    "QCELP",     
    "CN",        
    "MPA",       
    "G728",      
    "DVI4",      
    "DVI4",      
    "G729",      
    "G726-40",   
    "G726-32",   
    "G726-24",   
    "G726-16",   
    "G729D",     
    "G729E",     
    "GSM-EFR",   
    "L8",        
    "RED",       
    "VDVI",      
    "CelB",      
    "JPEG",      
    "nv",        
    "H261",      
    "MPV",       
    "MP2T",      
    "H263",
    "telephone-event",
    "noop",
    "Noop",
    "garbage",
    "GarBaaaggee"
};

    

// Elf or PJW hash function
unsigned long PJWhash ( const char *name )
{
    unsigned long   h = 0, g;
    while ( *name )
    {
        h = ( h << 4 ) + *name++;
        if ( g = h & 0xF0000000 )
            h ^= g >> 24;
        h &= ~g;
    }
    return h;
}


// CRC hash function
unsigned long CRChash ( const char *name )
{
    unsigned long   h = 0, highorder;
    while ( *name )
    {
        highorder = h & 0xf8000000;
        h = ( h << 5 );
        h = h ^ (highorder >> 27);
        h ^= *name++;
    }
    return h;
}


// Reduced size CRC hash function
unsigned short Myhash ( const char *name )
{
    unsigned short   h = 0, highorder;
    while ( *name )
    {
        highorder = h & 0xf800;
        h = ( h << 3 );
        h = h ^ (highorder >> 13);
        h ^= *name++;
    }
    return h;
}



// simphash function (Stroustrup)
// creates duplicates easily
unsigned long simphash(const char* key)
{
    unsigned long res = 0;
    while(*key)
        res = (res <<1)^*key++;

    return res;
}



// print output on console
void show(pair<unsigned long, const char*> p1)
{
    cout << p1.first << " = " << p1.second << endl; 
}


// ---------------- main --------------------
int main(int argc, char* argv[])
{
    int nrOfKeys = sizeof(Keys)/sizeof(char*);

    multimap<unsigned long, const char*> hashMap;
    
    // calculate hash and store values in the multimap
    for (int i=0; i< nrOfKeys; ++i)
    {
        hashMap.insert(make_pair(Myhash(Keys[i]), Keys[i]));
    }

    // show contents of hashList on console
    for_each(hashMap.begin(), hashMap.end(), show);

    return 0;
}
