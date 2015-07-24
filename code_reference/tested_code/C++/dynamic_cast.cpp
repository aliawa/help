// dynamic_cast.cpp : Defines the entry point for the console application.
//
/**
**----------------------------------------------------------------**
	Use /GR to use dynamic_cast operator with VC++
	
**----------------------------------------------------------------**
**/

#include "stdafx.h"


class CBase  
{
public:
	virtual ~CBase(){};
};


class CDerived : public CBase
{
};



int main(int argc, char* argv[])
{
	
	CBase* pB = 0; //CBase polymorphic class i.e., at least one virtual function;

	// dynamic_cast behaves correctly with null pointer
	CDerived* pD = dynamic_cast<CDerived*>(pB); // pD == 0

	return 0;
}
