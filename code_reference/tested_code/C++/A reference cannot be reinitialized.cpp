/* ---------------------------------------------------------------------*/
/*.			A reference cannot be changed after initialization

*/
/* ---------------------------------------------------------------------*/



#include "stdafx.h"
#include <set>

// The element class
struct Elem
{
	Elem(int n): m_Mem(n){}

	int m_Mem;
};



// A class that has a reference member variable

// Can we make this reference refer to something else
// after initialization ??
class RefOwner
{
	Elem& m_Elem;

public:
	RefOwner(Elem& e): m_Elem(e){} // reference initialized

	void Detach()
	{
		Elem* y = &m_Elem;			// what is the address of ref before

		Elem* x = new Elem(3);
		m_Elem  = *x;				// try to make m_Elem refer to something else

		y = &m_Elem;				// what is the address of ref after
									// it is the same as before 
	}

	~RefOwner()
	{
		delete &m_Elem;
	}
};



int main(int argc, char* argv[])
{

	Elem* e = new Elem(4);
	RefOwner R(*e);

	R.Detach(); 

	delete e;	// We may think that this is O.K because Detach() made m_Elem refer
				// to something else but this deletes the same thing as
				// m_Elem is refering to 
				// and we get an assertion when R is deleted
	
	return 0;
}


