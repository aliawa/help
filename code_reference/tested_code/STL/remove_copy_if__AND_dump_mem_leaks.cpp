// **** ---------------------------------------------------------------
/*
		Illustrating:
		1.	list.erase() calls the destructor of the controlled elements
			when they are stored by value not by pointer.

		2.	producing output similar to MFC TRACE in non MFC programms

*/
// **** ---------------------------------------------------------------
  

#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <list>
#include <algorithm>
#include <vector>
#include <iostream>
	
using namespace std;

class MyComp
{
public:
	MyComp(list<int>& ls): m_ls(ls){}
	bool operator()(int n)
	{
		list<int>::iterator it =
		 find(m_ls.begin(), m_ls.end(), n);
		return (it != m_ls.end());
	}
private:
	list<int>& m_ls;
};



int main(int argc, char* argv[])
{

	vector<int> vec;
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(13);

	list<int> l;
	l.push_back(7);
	l.push_back(5);

	vector<int> tmpVec;
	
	//
	// remove_copy_if will copy all elements 
	// from input sequence
	// into output sequence
	// for which MyComp(l)() is false
	//
	remove_copy_if(vec.begin(), vec.end(), back_inserter(tmpVec), MyComp(l));
	//
	// tmpVec now contains 1,3,13
	//

	// check what is in tmpVec
	// output is 1 3 13
	copy(tmpVec.begin(), tmpVec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	
	// check what is in vec
	// vec remains unchanged
	// output is 1 3 5 7 13
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	//
	// redirecting the output of remove_copy_if to vec
	// overwrite the  existing elements of vec
	// then erase the remaining
	//
	// end effect --> remove elements from vec
	// for which MyComp(l)() is false
	//
	vector<int>::iterator itLast =
		remove_copy_if(vec.begin(), vec.end(), vec.begin(), MyComp(l));
	vec.erase(itLast, vec.end());
	
	//
	// check what is in vec
	// output is 1 3 13
	//
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

	// Dump memory leaks
	_CrtDumpMemoryLeaks();
	
	return 0;
}
