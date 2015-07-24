#include <stdio.h>

// Find the next closest multiple of BOUNDRY

#define BOUNDRY 0x1000

int main()
{
	int x;
	int boundry;
	
    printf ("/nCalculates next multiple of %d\n", BOUNDRY);
    printf ("Enter Number:");
	scanf("%d", &x);

	boundry = ((x & (BOUNDRY-1)) != 0)? (x & ~(BOUNDRY-1)) +(BOUNDRY) : x;

	printf("boundry:%d  hex:0x%x\n", boundry, boundry);

}


	
	
