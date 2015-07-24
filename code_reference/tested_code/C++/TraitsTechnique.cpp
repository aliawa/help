// TraitsTechnique.cpp : Defines the entry point for the console application.
//
/**
**----------------------------------------------------------------**

  How a typedef can act like a virtual function in some sense

  CBase "typedefs" CFoo to myType, the derived class CDerived
  typedefs something else to myType. CBase::myType and
  CDerived::myType are two different classes. CDerived2 has 
  no typedef therefore CDerived2::myType == CBase::myType

  This technique is like the traits classes in STL

**----------------------------------------------------------------**
**/

#include "stdafx.h"

class CFoo
{
public:
	int get() {return 1;}
};

class CBar
{
public:
	int get() { return 2;}
};


class CBase  
{
public:
	typedef CFoo myType;
};


class CDerived : public CBase
{
public:
	typedef CBar myType;
};


class CDerived2 : public CBase
{};


class CDerived3 : public CDerived
{};

int main(int argc, char* argv[])
{
	int x = CBase::myType().get();		// x=1
	int y = CDerived::myType().get();	// y=2

	int z = CDerived2::myType().get();	// z=1  same as CBase

	int a = CDerived3::myType().get();	// a=2  same as CDerived
	
	return 0;
}
