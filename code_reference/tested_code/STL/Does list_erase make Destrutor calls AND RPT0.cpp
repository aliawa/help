// **** ---------------------------------------------------------------
/*
		Illustrating:
		1.	list.erase() calls the destructor of the controlled elements
			when they are stored by value not by pointer.

		2.	producing output similar to MFC TRACE in non MFC programms

*/
// **** ---------------------------------------------------------------
  

#include "stdafx.h"
#include <list>
#include <crtdbg.h>								// defines the _RPT0 macro

class A
{
	int * p;
public:
	A():p(new int(1)){}
	~A();
	A(const A& r) { p = new int(*(r.p)); }		// copy constructor is 
};												// very imp if the class
												// has ptr members


A::~A()											// placed outside the class  
{												// definition to enable us
	delete p;									// to put a breakpoint
	_RPT0(_CRT_WARN, "-- Destrutor Called\n");	// inside the destructor.
}


int main(int argc, char* argv[])
{
	using namespace std;
	
	list<A*> l;
	A* pA = new A;
	l.push_back(pA);
	l.erase(l.begin(), l.end());
	delete pA;									// erase() does not call the
												// destructor so we have to
												// free the memory ourselvs

	
	list<A> l2(2);								// list creates one temp A and
												// then initializes the rest
												// with this. At the end the
												// temporary A is destroyed
	
	int s = l2.size();	// s = 2
	l2.erase(l2.begin(), l2.end());				// calls ~A() twice
	s = l2.size();		// s = 0
	
	
	
	return 0;
}
