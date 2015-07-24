
#include <stdio.h>                      // Standard input/output header file, needed printf and scanf
#include <stdlib.h>                     // This header file contains the itoa function
#include <stdarg.h>

char* my_itoa(int num, char * buff, int sz)
{
    snprintf(buff, sz, "%d", num);
    return buff;
}


// Test: variable argument lists
void myprintf(const char *fmt, ...)
{
    const char *p;
    va_list argp;     // va_list is like FILE* type
    int i;
    char *s;
    char fmtbuf[256];

    va_start(argp, fmt);   // va_start is like fopen

    for(p = fmt; *p != '\0'; p++)
    {
        if(*p != '%')
        {
            putchar(*p);
            continue;
        }

        switch(*++p)
        {
            case 'c':
                i = va_arg(argp, int);
                putchar(i);
                break;

            case 'd':
                i = va_arg(argp, int);
                s = my_itoa(i, fmtbuf, sizeof(fmtbuf));
                fputs(s, stdout);
                break;

            case 's':
                s = va_arg(argp, char *);
                fputs(s, stdout);
                break;

            case 'x':
                i = va_arg(argp, int);
                s = my_itoa(i, fmtbuf, sizeof(fmtbuf));
                fputs(s, stdout);
                break;

            case '%':
                putchar('%');
                break;
        }
    }

    va_end(argp);
}


// Test: Using vprintf
char * my_debug_print(const char *fmt, ...)
{
    va_list ap; //arg pointer

    va_start(ap, fmt);
    int n = vprintf(fmt, ap);
    va_end(ap);

    printf ("printed %d characters\n", n);
}



// A variadic trick with array
void func(int* values) {
    while(*values) {
        printf("--> %d\n", *values);
        values++;
    }
}


int main(int ac, char** av)
{
    func((int[]){1,5,6,7,11,13,0});
}


