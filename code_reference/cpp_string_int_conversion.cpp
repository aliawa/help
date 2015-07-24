#include <iostream>
#include <sstream>
#include <string>

// -----------------------------------------
//
//    String to int conversions C++ way
//
// -----------------------------------------


using namespace std;


// -----------------------------------------
//
//       convert anyting to string
//
// -----------------------------------------
template <class T>
std::string to_string(const T& i) {
    std::ostringstream ost;
    ost << i;
    return ost.str();
}

// -----------------------------------------
//
//     convert char* and string to int
//
// -----------------------------------------
template <class T>
int to_int(T& str) {
    int x;
    std::istringstream (str)>>x;
    return x;
}



int main (int argc, char** argv) {

    cout << "argc=" << to_string(argc) << endl;
    cout << "argv[0]=" << to_int(argv[1]) << endl;

    string theNumber("10000");
    cout << "theNumber=" << to_int(theNumber) << endl;

    return 1;
}


