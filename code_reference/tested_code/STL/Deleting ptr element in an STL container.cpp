// ------------------------------------
/*
	Ilustrates: The correct method of clearing an STL container
	that contains pointers.


	A delete_ptr function has to be defined for each container,
	because Microsoft does not support template functions as
	arguments to template functions. Other wise we could write

	template<class T> T* delete_ptr(T* p) {delete p; return 0;}

	once and for all.

*/
// ----------------------------------------


#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

string* delete_ptr(string* p) {delete p; return 0;}

void purge (std::vector<string*>& s)
{
	std::transform(s.begin(), s.end(), s.begin(), delete_ptr);
}



int main(int argc, char* argv[])
{
	
	std::vector<string*> v;

	v.push_back(new string("Awais"));
	v.push_back(new string("Ali"));
	v.push_back(new string("Bwais"));
	v.push_back(new string("Nwais"));
	v.push_back(new string("Hwais"));
	v.push_back(new string("Uwais"));


	purge(v);  // applies delete_ptr to all elements

	int x = v.size(); // x = 6

	v.erase(v.begin(), v.end());

	return 0;
}
