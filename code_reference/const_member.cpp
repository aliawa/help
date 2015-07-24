#include <iostream>

using namespace std;


class myclass
{
	public:
		myclass(int x):myint(x){}
		const int myint;
};



int main()
{
	myclass inst(1);

	cout << inst.myint << endl;
}
