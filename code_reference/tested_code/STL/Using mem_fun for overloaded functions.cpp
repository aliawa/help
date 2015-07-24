// Using mem_fun if a class has two overloaded functions
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

// The test class
struct A
{
	// construct
	A(long n):m_n(n){}
	

	// some function
	void f(long x)
	{
		m_n = x;
	}

	
	// overloaded function
	long f()
	{
		return m_n;
	}
	

	// A const function
	long g() const
	{
		return m_n *2;
	}


	// Internal data
	long m_n;
};



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

	/********************/
	/*	since f is overloded mem_fun cannot differentiate between 
		"long f()" and "void f(long)" in order to overcome this
		problem we initialize a variable of type
		"Pointer to a member function returning a long with void arg type"
		and pass this to mem_fun
	*/
	/********************/
	
	typedef long (A::*_mem)();
	_mem pM= &A::f;

	// Alternatively we may write
	/*  long (A ::* pM)() = &A :: f; */


	// call pM for all elements of lst.
	transform(lst.begin(), lst.end(), ostream_iterator<long>(cout, " "), mem_fun(pM));
	cout << endl;


	/********************/
	/*	What if we need to call "long g() const".
		The problem is mem_fun does not like const functions so what to do

		Here is one soloution
		we use "reinterpret_cast" because "const_cast" does not work here
	*/
	/********************/
	long (A ::* pgMconst)() const	=	&(A :: g) ;
	long (A ::* pgM)()				=	reinterpret_cast<long (A ::* )()>(pgMconst) ;

	// we may also combine the above two lines
	//long (A ::* pgM)() = reinterpret_cast<long (A::* )()>(&(A::g));


	// call pgM for all elements of lst.
	transform(lst.begin(), lst.end(), ostream_iterator<long>(cout, " "), mem_fun(pgM));
	cout << endl;


	return 0;
}
