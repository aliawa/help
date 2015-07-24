
/*	remove_if  brings all elements for which pred is false at
	front replacing the existing ones

	therefore remove_if may not be suitable for pointer lists
	because we may want to delete the pointers before losing them

	The returned iterator points to the end of the sequece that
	contains the elements that do not match the pradicat.
*/

//#include "stdafx.h"
#include <vector>
#include <algorithm>	// generate_n
#include <iostream>		// for ostream_iterator

using namespace std;


// generator function
struct gen
{
	gen():n(0){}
	int n;
	int operator()(){ return ++n;}
};


// return true if x is not divisible by 2
bool IsOdd(int x)
{
	return (x%2)!=0? true : false;
}




int main(int argc, char* argv[])
{
	vector<int> v;
	generate_n(back_inserter(v), 10, gen()); // fill v with 1-10
	
	// show contents of v on console
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	// remove all odd numbers
	vector<int>::iterator it = remove_if(v.begin(), v.end(), IsOdd);

	// show contents of v on console
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;


	// show the part of sequence from which
	// remove_if has removed all undesired elements
	copy(v.begin(), it, ostream_iterator<int>(cout, " "));
	cout << endl;
	
	return 0;
}
