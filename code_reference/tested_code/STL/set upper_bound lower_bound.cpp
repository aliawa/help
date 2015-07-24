// ---------------------********************---------------------
/*
		set::upper_bound(k):
			first element greater than k

		set::lower_bound(k):
			first element that is not less than k
*/
// ---------------------********************---------------------



#include "stdafx.h"
#include <set>

// The element class
struct Elem
{
	Elem(int n): m_Mem(n){}
	int m_Mem;
};



// IMPORTANT : the operator() should be const
struct comp
{
	bool operator()(const Elem* lhs, const Elem* rhs) const
	{
		return (lhs->m_Mem < rhs->m_Mem);
	}
};



int main(int argc, char* argv[])
{
	typedef std::set<Elem*, comp>::iterator iter;
	
	std::set<Elem*, comp> MySet;

	MySet.insert(new Elem(1));
	MySet.insert(new Elem(2));
	MySet.insert(new Elem(3));
	MySet.insert(new Elem(5));
	MySet.insert(new Elem(6));


	// what happens when we try to find the first element that is greater
	// than a given element when the given element is the greatest element
	// in the set.
	Elem* mn = new Elem(6);
	iter it = MySet.upper_bound(mn);	// returns it to end() because there is no
										// element greater than Elem(6)
	
	if (it != MySet.end())		
		em = *it;



	// what happens when we try to find the first element that is not less
	// than a given element when the given element is the greatest element
	// in the set.
	it = MySet.lower_bound(mn);			// returns it to 6 because it is the first
										// element that is not less than the searched
	Elem* em;							// element
	if (it != MySet.end())			
		em = *it;


	
	// we search for an element Elem(4) which is not in MySet
	Elem m(4);
	it = MySet.lower_bound(&m);			// returns iterator to 5 because this is the
										// first element which is "not less than" 4 
	
	if (it != MySet.end())
		em = *it;



	return 0;
}


