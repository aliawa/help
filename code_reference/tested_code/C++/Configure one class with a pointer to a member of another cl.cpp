// --------------- ****************************************************--------------
/*
			PROBLEM:
			We have a number of item objects that are changed by a class X  
			and then they need to be saved.
			depending on the type of change a different saving 
			algorithm has to be used

			The saving algorithm is known to an external class C or D

			SOLUTION:
			We give the item object at the time of change an instance of 
			a class B.
			B is a template class. As template parameter we give C or D. As 
			constructor parameter we will give B a pointer to the function in
			C or D that needs to be called for saving

			NOTE:
			We call the constructor of B with pointer to a funciton of class A
			although at this time A is not instantiated
*/
// --------------- ****************************************************--------------


#include "stdafx.h"
#include <string.h> // for strlen

class A
{
public:
	int f(int x, char* y)
	{
		return strlen(y);
	}

	int g(int x, char* y)
	{
		int n = 0;
		while (*y)
			n += char(*y++);

		return n;
	}
};



template<class R>
class B
{
public:
	typedef int (R::*p_mem)(int, char*);	// define p_mem as a pointer
											// to a member function fo R
											// that takes int and char* as parameters
											// and give an int back
										
	B(p_mem x)
	{
		m_pFunc = x;
		pClass = new R();
	}

	int Do()
	{
		return (pClass->*m_pFunc)(1, "abc");
	}

private:
	R*		pClass;
	p_mem	m_pFunc;
};




int main(int argc, char* argv[])
{
	
	
	B<A> cl(&A::f);				// Tell B that we want it to call A::f(int, char*) when
								// we call the Do method of B
	int x = cl.Do();
	

	B<A> cl2(&A::g);
	int y = cl2.Do();			// calls A::g()
	
	return 0;
}
