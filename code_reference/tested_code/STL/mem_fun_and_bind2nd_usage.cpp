// ere.cpp : Defines the entry point for the console application.
// #include "stdafx.h" /*windows header*/

#include <set>
#include <functional> // mem_fun
#include <iterator>   // ostream_iterator
#include <algorithm>
#include <iostream>


// ------------------------------------------------------------------------------------
// bind2nd: Using two-argument function object as a single-argument function
//          Other words: convert binary predicate to unary predicate
//
// mem_fun: Using a member-function as an argument to algorithms.
//
// ------------------------------------------------------------------------------------


using namespace std;


struct Y 
{
	Y(int n): _mY(n){}
	
	int  change0   ()             {return ++_mY;}
	int  change1   (int n)        {return _mY = n;}
	bool operator< (const Y& lhs) {return _mY < lhs._mY;}
	int  show      ()             {return _mY;}
    
	int _mY;
};


int main(int argc, char* argv[])
{
	set<Y*> st;

	st.insert(new Y(1));
	st.insert(new Y(2));
	st.insert(new Y(3));
	st.insert(new Y(4));

    // original sequence
	transform(st.begin(), st.end(), ostream_iterator<int>(cout, " "), mem_fun(&Y::show));
	cout << endl;

    // Call Y::change0() for each element
    // Here we are using a member function that takes no arguments
	for_each(st.begin(), st.end(), mem_fun(&Y::change0));
	transform(st.begin(), st.end(), ostream_iterator<int>(cout, " "), mem_fun(&Y::show));
	cout << endl;

	set<Y*>::iterator first = st.begin();
	set<Y*>::iterator last = st.end();

    // Call change0 directly
	for (;first != last; ++first)
	{
		cout << (*first)->change0() << " ";
	}
    cout << endl;

    // Call change1(5) for each element
    // Here we use a member function that takes one argument through pointer to object
    // mem_fun converts change1 into a function object that takes two arguments (Y* and int)
    // We use bind2nd to bind the second argument to 5
	for_each(st.begin(), st.end(), bind2nd(mem_fun(&Y::change1), int(5)));
	transform(st.begin(), st.end(), ostream_iterator<int>(cout, " "), mem_fun(&Y::show));
	cout << endl;

	return 0;
}
