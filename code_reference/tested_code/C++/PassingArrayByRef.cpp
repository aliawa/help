// ------------------------------------
/*
	illustrates:
	1. enum in a namespace
	2. How a reference to an Array can be passed to a function

	Note:
	The recieving function will not know the size of the array
	therefore this has to be passed as well

*/
// ------------------------------------

#include "stdafx.h"
#include <iostream>
#include <vector>


namespace NmSpc
{
	enum Names {eName, eCity, eStreet, ePostCode};
};



class Item
{
public: 
	void SetStringFields( NmSpc::Names inList[])
	{
		int x = sizeof(inList);		// x = 4, size of a ptr => inList is a reference
		std::cout << inList[1];		// use inList			
	}
};


int main(int argc, char* argv[])
{

	// initializing is easy	
	NmSpc::Names myNames[] = 
	{
		NmSpc::eName,			// taken from a namespace
		NmSpc::eCity,
		NmSpc::eStreet,
	};

	int y = sizeof(myNames);					// y = 12 , 3*4=12

	// A std::vector cannot be initialised through an initializing list
	/*
	std::vector<NmSpc::Names> myVecNames =
	{
		NmSpc::eName,
		NmSpc::eCity,
		NmSpc::eStreet,
	};
	*/


	Item ItemObj;
	ItemObj.SetStringFields(myNames);			// pass myNames by reference

	
	return 0;
}
