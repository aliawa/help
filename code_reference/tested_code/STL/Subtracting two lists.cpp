
// ***************  -------------------------- *******************

/*		Subracting a list of pointers from an other list
		The problem with list of pointers is that we need
		to delete the elements that were removed from the
		list. the ListDiff function takes care of that
*/

// ***************  -------------------------- *******************

#include "stdafx.h"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

// The test class
struct A
{
	A(int x):m_n(x){}
	int m_n;
	
	// function to produce debug output
	int Out(){ cout << m_n<< "  "; return m_n;}
};


// *** Takes two lists and removes all elements from ***//
// *** the first list that are found in the second   ***//
// *** list										     ***//

// *** C is any container type

// *** C2::begin() and C2::end() should return a RANDOM_ACCESS_ITERATOR

// *** func is a functor that compares the elements (x and y) of the list and
// *** return true if x<y

template <class C, class C2,  class func>
ListDiff(C& lst, C2& lst2, func comp)
{
	sort(lst2.begin(), lst2.end(), comp);
	for (C::iterator it = lst.begin();it != lst.end(); )
	{
		if (binary_search(lst2.begin(), lst2.end(), *it, comp))
		{
			delete *it;
			it = lst.erase (it);
		}
		else
			++it;
	}
}



// a quick and dirty generator function
A* gen()
{
	static n =0;
	++n;
	return new A(n);
}



// function compares two pointers(a and b) of type A
// returns true if a<b
bool ElComp(A* a, A* b)
{
	return (a->m_n < b->m_n);
}




int main(int argc, char* argv[])
{
	list<A*> ls;
	generate_n(back_inserter(ls), 10, gen);
	
	// see what the list initially contains
	cout << "Before : ";
	for_each(ls.begin(), ls.end(), mem_fun(A::Out));
	cout << endl << endl;


	// vc will contain the elements that are to be
	// removed from ls
	vector<A*> vc;
	vc.push_back(new A(2));
	vc.push_back(new A(3));

	// remove all elements from ls that are found in vc
	ListDiff(ls, vc, ElComp);

	// show the list after the operation
	cout << "After  : ";
	for_each(ls.begin(), ls.end(), mem_fun(A::Out));

	return 0;
}
