
// ----------------------------------------------------------------------
//
//                            Useful Function Objects
//
// ----------------------------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;



//
// Calculate a Sum Page:514 $18.4
//
template<class T> class Sum 
{
    T res;
public:
    Sum(T i = 0) : res(i){}             // initialize
    void operator() (T x) { res+= x;}   // accumulate
    T result() const { return res;}     // return sum
};


int main(int argc, char* argv[])
{
    vector<int> v(10,5); // 10 copies of 5

    
    // sum of all elements of v
    Sum<int> s;
    s = for_each(v.begin(), v.end(), s);
    cout << "the sum is " << s.result() << '\n';




    return 0;
}


