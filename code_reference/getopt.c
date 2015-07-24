#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/*
 * can be called with 
 * -n -f in.txt -o out.txt aaw
 * -nfin.txt -oout.txt aaw
 * -f in.txt -no out.txt aaw
 * etc.
 */


void usage( char* progname)
{
    fprintf(stderr, "Usage: %s [-f input-file] [-n] [-o output-file] name\n",
                                progname);
}


int main(int argc, char *argv[])
{
    int flags=0;
    char *inputFile = NULL;
    char *outputFile = NULL;
    int opt;
   
    while ((opt = getopt(argc, argv, "nf:o:")) != -1) {
        switch (opt) {
        case 'n':
            flags = 1;
            break;
        case 'f':
            inputFile= optarg;
            break;
        case 'o':
            outputFile= optarg;
            break;
        default: /* '?' */
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    printf("flags=%d\ninputFile=%s\noutputFile=%s\n", flags, inputFile, outputFile);

    if (optind >= argc) {
        fprintf(stderr, "\nExpected argument after options\n");
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("name argument = %s\n", argv[optind]);

    exit(EXIT_SUCCESS);
}
