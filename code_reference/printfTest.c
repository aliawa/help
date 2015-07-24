
#include <stdio.h>


int main()
{
    int x = 0x10abc;

    // Conversion specifier X
    printf ("%X\n", x);

    // Flag character #
    printf ("%#X\n", x);

    // minimum width specifier
    printf ("%8X\n", x);

    // leading zeros
    printf ("%08X\n", x);

    // minimum width specifier, leading zeros, flag #
    printf ("%#08X\n", x);
    
    // minimum width specifier, leading zeros, flag #
    printf ("0x%08X\n", x);

    // field width given in argument
    printf ("0x%0*X\n", 9, x);

    // multiple field widths given in arguments
    printf ("0x%0*X  0x%0*x\n", 9, x, 10, x);
}
