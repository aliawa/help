// ---------------- ******** ----------------------
/*	A class contains a list and we need to call a mem
	function of the containing list on each element of
	the list

	we can use the mem_fun function if we need to call 
	a member of the list-element on each element.
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


//  NOTE:			This class is useful for a list of pointers
// _RetTyp			return type of the memberfuction
// _ListElemTyp		Type of the list element passed to operator()
// _MethodOwnerTyp	Type of class whose member function will be called

template<class _RetTyp, class _ListElemTyp, class _MethodOwnerTyp>
class foreign_mem_fun_t : public unary_function<_ListElemTyp *, _RetTyp> 
{
public:
	explicit foreign_mem_fun_t(_RetTyp (_MethodOwnerTyp::*pm)(_ListElemTyp*), _MethodOwnerTyp*)
		: _Ptr(pm) {}

	_RetTyp operator()(_ListElemTyp *P) const
	{
		return ((_pObj->*_Ptr)(P)); 
	}

private:
	_RetTyp (_MethodOwnerTyp::*_Ptr)(_ListElemTyp*);
	_MethodOwnerTyp* _pObj;
};



// A helper function for the foreign_mem_fun_t class, deduces the template argurments
// from the arguments list
template<class _RetTyp, class _ListElemTyp, class _MethodOwnerTyp>
foreign_mem_fun_t<_RetTyp, _ListElemTyp, _MethodOwnerTyp> 
	foreign_mem_fun(_RetTyp (_MethodOwnerTyp::*pm)(_ListElemTyp*), _MethodOwnerTyp* pObj)
{
	return (foreign_mem_fun_t<_RetTyp, _ListElemTyp, _MethodOwnerTyp>(pm, pObj)); 
}




// A class containing a list or it gets the list or iterators
// on it and must operate on this list
struct Z
{
	void f1(list<A*>::iterator first, list<A*>::iterator last)
	{
		//call f2 on each element of the list;
		for_each(first, last, foreign_mem_fun(&Z::f2, this));
	}

	long f2 (A* p)
	{
		return p->g(4);
	}
};



int main(int argc, char* argv[])
{
	list<A*> lst;

	// fill lst with A(0) ... A(9)
	generate_n(back_inserter(lst), 10, gen);

	// The real test
	Z Obj;
	Obj.f1(lst.begin(), lst.end());
	
	// call f for all elements of lst.
	transform(lst.begin(), lst.end(), ostream_iterator<long>(cout, " "), mem_fun(&A::f));
	cout << endl;

	return 0;
}


;
