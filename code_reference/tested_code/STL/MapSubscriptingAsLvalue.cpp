// ----------------------------------

/*	illustrates
	how a map's subscript operator can be used as an lvalue
	since operator[key] returns a reference to the corresponding
	value part of the key value pair, this can be used to modify
	the map.

	if the key is not found subscripting will add a "default-element"
	to the map. This means that the value type must have a default 
	value
*/
// ----------------------------------

#include "stdafx.h"
#include <map>

void GetValue(int id, int& x)
{
	switch (id)
	{
	case 1: x = 7000; break;
	case 2: x = 500;  break;
	}
	
}

int main(int argc, char* argv[])
{
	std::map<int, int> Mymap;
	
	// key has no corresponding value
	GetValue(1, Mymap[2]);
	int y = Mymap[2];			// y = 7000

	// now the key has already a value
	GetValue(2, Mymap[2]);
	y = Mymap[2];				// y = 500

	return 0;
}
