//

/* ---------------------------------****************--------------------------------*/
/*																					*/
/*		The copy constructor of the base class is not called automatically			*/
/*		from the derived class. This has to be called explicitly					*/
/*																					*/
/* ---------------------------------****************--------------------------------*/



#include "stdafx.h"

class A
{
public:
	A():m_n(1){}				// default constructor
	A(int y): m_n(y){}			// constructor
	A(A& rhs){ m_n = rhs.m_n;}	// copy constructor

protected:
	int m_n;
};


class B : public A
{
public:
	B():A(4),m_nb(2){}						// default constructor
	B(int z):A(z+3),m_nb(z){}				// constructor
	B(B& rhs):A(rhs){ m_nb = rhs.m_nb;}		// copy constructor
//			  ------
//				^^
//				||
protected:
	int m_nb;
};


int main(int argc, char* argv[])
{
	B x(3);
	B y = x;	// calls B's copy consructor, which then calls A's
				// copy consturctor

	return 0;
}
