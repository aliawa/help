//
//  Multimap and equal_range usage
//

#include <iostream>
#include <algorithm>
#include <map>


using namespace std;

typedef multimap<unsigned, const char*>::iterator MI;
typedef pair<MI,MI> Range;


// print output on console
void show(pair<unsigned, const char*> p1)
{
    cout << p1.first << " = " << p1.second << endl; 
}


// print range
void printRange(Range rg, MI endIter) 
{  
    cout << "No. of entries in range:" << rg.second - rg.first << endl;
    cout << "first--> ";
    if(rg.first!=endIter){
        show(*rg.first);
    } else {
        cout << "endIter" << endl;
    }

    cout << "second-->";
    if (rg.second!=endIter){ 
        show(*rg.second); 
    } else {
        cout << "endIter" << endl;
    } 
    if (rg.second == rg.first) {
        cout << "No entries found" << endl;
    } else {
        for_each(rg.first, rg.second, show);
    }
    cout << endl;
}



// ---------------- main --------------------
int main(int argc, char* argv[])
{
    multimap<unsigned, const char*> myMap;
   
    // Note multimap does not have operator[]
    myMap.insert(make_pair(2, "record1"));
    myMap.insert(make_pair(2, "record2"));
    myMap.insert(make_pair(2, "record3"));
    myMap.insert(make_pair(4, "record4"));
    myMap.insert(make_pair(4, "record5"));
    myMap.insert(make_pair(6, "record6"));

    // show contents of hashList on console
    for_each(myMap.begin(), myMap.end(), show);
    cout << endl;


    // search for an exiting key
    cout << "search:4" << endl;
    printRange(myMap.equal_range(4), myMap.end());

    // search for a single entry
    cout << "search:6" << endl;
    printRange(myMap.equal_range(6), myMap.end());


    // search for a non-existent key greater than the largest key
    cout << "search:100" << endl;
    printRange(myMap.equal_range(100), myMap.end());

    // search for a non-existent key less than the smallest key
    cout << "search:1" << endl;
    printRange(myMap.equal_range(1), myMap.end());

    return 0;
}
