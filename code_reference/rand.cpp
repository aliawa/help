#include <iostream>

using namespace std;


// Generate a random number between start and end, not including end
// a range of 0-10 will give random numbers 0 - 9
int getRand(double start, double end)
{
    return (int)start + (int)((end-start) * (rand() / (RAND_MAX + 1.0)));
}


            
int getRandomStr(char* dst, int sz)
{
    char array[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234567890";
    for (int i=0; i<sz; ++i) {
        *dst++ = array[getRand(0,sizeof(array))];
    }
    *dst='\0';
}



int main (int argc, char** argv)
{
    srand(time(NULL));

    int start = atoi(argv[1]);
    int end = atoi (argv[2]);
    
    cout << "start:" << start << " end:" << end << endl;

    // generate 5 random numbers
    for (int i=0; i< 5; ++i) {
        cout << getRand(start, end) << endl;
    }

    // generate a random string
    char rstr[6];
    getRandomStr(rstr, sizeof(rstr));
    cout << "random string: " << rstr << endl;

}

