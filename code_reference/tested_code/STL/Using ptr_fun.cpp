

// ---------------------------- ************************ -------------------------
/*
			In order to use bind2nd with a function we need to use ptr_fun
			which converts it into an adaptable function.

			This is useful because then we don't need a class object(function
			object)
*/
// ---------------------------- ************************ -------------------------

//#include "stdafx.h"
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

// The test class
struct A
{
	// construct
	A(long n):m_n(n){}
	
	// overloaded function
	long f()
	{
		return m_n;
	}
	

	// some operation
	long g(int n)
	{
		return (m_n+=n);
	}

	// Internal data
	long m_n;
};



// A binary function
long f( A* p, int n)
{
	return p->g(n);
}

// generator for lst
A* gen()
{
	static long l;
	return new A(l++);
}



int main(int argc, char* argv[])
{
	list<A*> lst;

	// fill lst with A(0) ... A(9)
	generate_n(back_inserter(lst), 10, gen);


	// call a binary function f with second arg of f bound to 3
	for_each(lst.begin(), lst.end(), bind2nd(ptr_fun(f), 3));


	// call pM for all elements of lst.
	transform(lst.begin(), lst.end(), ostream_iterator<long>(cout, " "), mem_fun(&A::f));
	cout << endl;




	return 0;
}
