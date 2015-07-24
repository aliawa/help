
// ---------------- ******** ----------------------

/*	
	back_inserter can be used with any class provided
	
	  1. class has a member push_back( value_type)
	  2. has a public typedef value_type

	for example struct Z in this example

*/
// ---------------- ******** ----------------------

#include "stdafx.h"
#include <list>
#include <iostream>
#include <algorithm>
#include <functional> // unary_function<_ListElemTyp *, _RetTyp> 


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


// generator for lst
A* gen()
{
	static long l;
	return new A(l++);
};


struct Z
{
	Z():m_n(0){}
	typedef A* value_type;

	void push_back(A* p)
	{
		m_n+= p->f();
	}

	// Internal data
	long m_n;
};

	



int main(int argc, char* argv[])
{
	list<A*> lst;

	// fill lst with A(0) ... A(9)
	generate_n(back_inserter(lst), 10, gen);

	// The real test
	Z Obj;
	copy(lst.begin(), lst.end(), back_inserter(Obj));
	
	// call f for all elements of lst.
	transform(lst.begin(), lst.end(), ostream_iterator<long>(cout, " "), mem_fun(&A::f));
	cout << endl;

	return 0;
}


;
