//	____________________________________________________
	
/*	  Illustrates: Using the std::accumulate function
	
	  for the version of accumulate that take a ptr.
	  it is the responsibility of the function to 
	  to the adding.
*/
//	____________________________________________________

#include "stdafx.h"
#include <vector>
#include <numeric>


std::string g(int n)
{
	return "a_";
}


// function used as parameter to accumulate
std::string f(std::string& str, int n)
{
	return (str += std::string("a_"));
}



using namespace std;
int main(int argc, char* argv[])
{

	std::vector<int> vecX(10, 1); // 10 elements, all ones "1"
	std::string str1, str2;
	
	// simple version
	int i = std::accumulate(vecX.begin(), vecX.end(), 0);
	// now i = 10

	str1 = std::accumulate(vecX.begin(), vecX.end(), str1, f); 
	// now str1 = a_a_a_a_a_a_a_a_a_a_


	vector<int>::iterator it;
	for (it = vecX.begin(); it != vecX.end(); it++ ) //
		str2 += g(*it);
	// now str2 = a_a_a_a_a_a_a_a_a_a_

	return 0;
}
