// abc.cpp : Defines the My_ENtry point for the console application.
//

#include "stdafx.h"

// -----------------------------------------------------
/*			
			DEFINING an operator+ for enums

			WHY:
			we need to be able to add the enums so that
			we are able to determine later which enums 
			were added. This is only possible if the 
			enums are defined like 0001, 0010, 0100 etc. 
			but since they are not we devise a special 
			operator+().
*/
// -----------------------------------------------------

enum My_EN
{
	ONE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	INF = 0xFFFF
};


struct My_EN_Help
{
	My_EN_Help(long x): m_x(x){}

	// implicit conversion operator
	operator My_EN() { return My_EN(m_x);}

	long m_x;
};



//
// takes the operands by value
// because we want to be able to
// pass constants like 'TWO'
//
// A helper class is returned because
// we want to treat TWO + THREE differently
// from TWO + THREE + FIVE
//
// This function will be called in the
// first case only
//
My_EN_Help operator+ (My_EN l, My_EN r)						// 1st op
{
	long x = 1;
	long y = 1;

	// expanded version
	x <<= r-1;
	y <<= l-1;

	long z = y | x ;
	return My_EN_Help(z);

	// compact version
	//return My_EN_Help( (y << (l-1)) | (x << (r-1)) );

}



//
// This function will be called only after
// the above function has been called once
// 
My_EN_Help operator+ (My_EN_Help l, My_EN r)				// 2nd op
{
	long x = 1;
	
	// expanded version
	x <<= r-1;
	long z = l | x ;
	return My_EN_Help(z);

	// compact version
	//return My_EN_Help( l | (x << (r-1)) );
}



//
// Example taken from Stroustrup
//
enum Day { sun, mon, tue, wed, thu, fri, sat};

Day& operator++(Day& d)
{
	return d = (sat == d) ? sun : Day(d+1);
}


int main(int argc, char* argv[])
{
	My_EN f = ONE;

	// call 1st op+
	f = f + THREE;						// f = FIVE
	
	// calls 1st op+ then the 2nd one
	f = ONE + TWO + THREE;				// f = 0x7
	
	f = THREE + FIVE;					// f = 0x14
	f = FIVE + FOUR + TWO + THREE;		// f = 0x1e

	
	// Stroustrup example
	Day dayVar = sun;
	++dayVar;

	return 0;
}
