#include <stdio.h>
#include <string.h>

int usingFor(char * string)
{
    char *token  = strtok(string, ",");
    for (; token; token = strtok(NULL, ","))
        printf ("%s\n", token);
}


void usingWhile(char* string)
{
    char *token = strtok(string, ",");
    while (token)
    {
        printf ("%s\n", token);
        token = strtok(NULL, ",");
    }
}


void using_strtok_r(char* string)
{
    char* saveptr=NULL;
    char* token = strtok_r(string, ",", &saveptr);
    for (; token; token = strtok_r(NULL, ",", &saveptr))
       printf ("%s\n", token);
}



int main (int argc, char** argv)
{
    // strtok spoils the original string
    // if we want to preserve the original
    // string we will have to make a copy
    // first.

    if (argc != 2) {
        fprintf(stderr, "Usage: %s string with ',' as delimeter\n",
                argv[0]);
        return 1;
    }

    char * str = strdup (argv[1]);

    printf("\nMethod 1: strtok_r and for loop ---\n");
    using_strtok_r(str);
    printf("String after: %s\n", str);
    
    // str is now spoiled by earlier strtok
    // need to make a new copy
    free(str);
    str = strdup (argv[1]);

    printf("\nMethod 2: strtok and for loop ---\n");
    usingFor(str);
    printf("String after: %s\n", str);
    
    // str is now spoiled by earlier strtok
    // need to make a new copy
    free(str);
    str = strdup (argv[1]);

    printf("\nMethod 3: strtok and while loop ---\n");
    usingWhile(str);
    printf("String after: %s\n", str);

    free (str);
    return 0;
}

