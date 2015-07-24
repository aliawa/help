
// ________________________********************________________________


/*		How to make sure that a single instance of a class is created
		and subsequently only a reference to that single instance is 
		returned
*/

// ________________________********************________________________

#include "stdafx.h"
#include <crtdbg.h>								// defines the _RPT0 macro


//*** first test class
class A
{
private:
	A(){}; // no construction allowed
public:
	~A(){};

	static A& Create()
	{
		static A m_this = A();
		return m_this;
	}

	long	f(){return 1;}
	char*	g(){return "aaa";}
};




//*** second test class
//*** uses new to create the class
//*** clears the memory in destructor
class B
{
private:
	B(){};
public:
	~B()
	{ 
		_RPT0(_CRT_WARN, "-- Destrutor B Called\n");	// inside the destructor.

	}

	static B* Create()
	{
		static B* m_this = new B();
		return m_this;
	}
	
	long	f(){return 2;}
	char*	g(){return "bbb";}
};




int main(int argc, char* argv[])
{
	// test A
	A o1 = A::Create();
	A o2 = A::Create();
	A o3 = A::Create();		// o1 = o2 = o3		

	long n1		= o2.f();	// use the pointer
	char* pCh1	= o3.g();	// use o3, it functions


	// test B
	B* p1 = B::Create();
	B* p2 = B::Create();	// p1 and p3 have the same address

	long n2		= p1->f();
	char* pCh2	= p2->g();

	delete p1;				// clear the memory;
	// delete p2;			// a second delete will throw an exception


	return 0;
}
