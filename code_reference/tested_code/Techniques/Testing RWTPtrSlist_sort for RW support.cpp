//
// Purpose : Testing RWTPtrSlist<T>::sort() for Rouge Wave Technical Support
// Author  : Ali Awais
// (c)     : ViagInterkom GmbH
//
// Problem : The RWTPtrSlist<T>::sort() expects operator > in the contained class
//			 althouh the operator < should be enough. A workaround is 
//			 list.std().sort() where list is of type RWTPtrSlist<T>
//

#include "stdafx.h"

#include <algorithm>
#include <rw/tpslist.h>     


// the class 
struct A
{
	A(int x):m_x(x){}
	
	operator < ( const A& rhs)
	{
		return (m_x < rhs.m_x);
	}
	
	int m_x;

};


// Generator
struct Gen
{
	A* operator()()
	{
		return new A(rand());
	}
};


// Debug Output
struct Vals
{
	void operator()(const A* c)
	{
		std::cout << "A has " << c->m_x << std::endl ;
	}
};


int main(int argc, char* argv[])
{
	RWTPtrSlist<A> list;

	std::generate_n(std::back_inserter(list.std()),50,Gen());
	std::for_each(list.begin(), list.end(), Vals());

	list.sort();    // the program compiles if this line is commented out.
	
	return 0;
}
