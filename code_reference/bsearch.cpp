#include <iostream>
#include <stdlib.h>


using namespace std;


int compf(const void* s1, const void* s2){
    const char* st1 = (const char*)s1;
    const char* st2 = **(const char***)s2;
    return strcmp(st1, st2);
}

const char* REQ_ACK = "ACK";
const char* REQ_BYE = "BYE";
const char* REQ_INV = "INVITE";
const char* REQ_NOT = "NOTIFY";
const char* REQ_REF = "REFER";

int getId(const char* method) 
{
    // putting address of the pointers in the array so that they are
    // at equal distance from each other.
    const char** array[] = {&REQ_ACK, &REQ_BYE, &REQ_INV, &REQ_NOT, &REQ_REF};
    int nElem = sizeof(array)/sizeof(const char*);
    void * m = bsearch (method, &array[0], nElem, sizeof (const char*), compf);
    if (m) {
        int diff = (((const char***)m)-&array[0]);
        cout << method <<"=" << diff << endl;
    } else {
        cout << method << " Not Found" << endl;
    }
}


int main (int argc, char** argv)
{
    getId("ACK");
    getId("BYE");
    getId("INVITE");
    getId("NOTIFY");
    getId("REFER");
    getId("BBBB");
}
