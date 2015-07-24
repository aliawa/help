#include <stdio.h>

int main(int argc, char* argv){

    // open a file for writing.
    FILE* f = fopen("tmpfile.txt", "w");

    //write a string to file
    if (f) {
        fputs("a text string\n", f);
        fclose(f);
    }
}
