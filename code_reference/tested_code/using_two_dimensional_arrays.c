// Demonstrate use of two dimensional arrays
//
#include <stdio.h>
#include "stdafx.h"

void print1(){
	printf("1");
}

void print2(){
	printf("2");
}

void print3(){
	printf("3");
}

void print4(){
	printf("4");
}

/* A struct with a function pointer					*/
/* Note: typedef is necessary in C as against C++	*/
typedef struct _TableEntry{
	int newState;
	void (*Action)();
} TableEntry;


int main(int argc, char* argv[])
{
	/* demonstrate initializing a two dimensional array */
	TableEntry D[2][3] = {
		{ {1,print1}, {3,print2}, {1,print3} },
		{ {3,print1}, {1,print3}, {3,print4} }
	};

	int i,j;
	
	
	/* calling a function through a function pointer */
	for (i=0; i<2; ++i){
		for (j=0; j<3; ++j){
			printf("%d", D[i][j].newState);
			(D[i][j].Action)();
			printf("  ");
		}
		printf("\n");
	}

	
	return 0;
}
