#include <stdio.h>
#include <string.h>


// -----------------------------------------------------------------------
//  A function that takes a function pointer as argument
// -----------------------------------------------------------------------

typedef struct st1_t st1;
typedef struct st2_t st2;

struct st1_t
{
    int m_1;
    int m_2;
};

struct st2_t
{
    char* m_3;
    char* m_4;
};



// This is the call-back function
int callback_fn (st1* p1, st2* p2)
{
    printf ("in callback_fn: m_1:%d, m_3:%s\n", p1->m_1, p2->m_3);
    return 5;
}


// Forward declaration of a function that takes a pointer to a call-back
// function as argument
// NOTE: Name of the call-back function argument is not given
void execute(st1* s1, st2* s2,  int (*)(st1*, st2*), int* ret);


// A typedef for the function pointer
// This will be used as PTR2FN* fn. If the typedef is "int (*PTR2FN) (st1*,st2*)
// then the usage will be PTR2FN fn.
typedef int (PTR2FN) (st1*, st2*);


int main (int argc, char* argv[])
{
    st1 v1 = {11, 12};
    st2 v2 = {"Eleven", "Twelve"};
    int ret;

    execute(&v1, &v2, callback_fn, &ret);
    printf("in main: ret:%d\n", ret);

    ret = execute2(&v1, &v2, callback_fn);
    printf("in main: execute2 returned:%d\n", ret);
}



// A function that takes a pointer to a call back function
// The call back function returns an int and take two parameters
void execute(st1* s1, st2* s2,  int (*cb)(st1*, st2*), int* ret)
{
    *ret = cb(s1, s2);
    printf("in execute: call_back_return:%d\n", *ret);
}


// Using typedef of callback function in definition
int execute2(st1* s1, st2* s2,  PTR2FN* fn )
{
    int ret = fn(s1, s2);
    return ret;
}


