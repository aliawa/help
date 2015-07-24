#include <stdio.h>    // needed for FILE
#include <strings.h>  // needed for bzero



void readInChunks(const char* filename)
{
    // Experiment with different sizes of buff
    char buff[10]={0};
    size_t bufSz = sizeof(buff)-1;

    FILE* f = fopen(filename, "r");
    if (f) {
        size_t s = 0;
        while ((s=fread(buff, bufSz, 1, f))) {
            printf ("data ---> %s\n", buff);
            bzero(buff, sizeof(buff));
        }
        // s==0 means that less than bufSz data
        // was read or no data was read. Therefore
        // we will do one more print to make sure
        // the last read data if any is printed
        printf ("data ---> %s\n", buff);
    }
    fclose(f);
}

int readInBigBuffer(const char* filename, char* buff ,int bufSz) 
{ 
    FILE *f= fopen(filename,"r");
    int lastlen=0;
    if (f) {
        int len;
        while((len = fread(buff+lastlen,1,bufSz-lastlen-1,f)) > 0) {
            lastlen+=len;
        }
        fclose(f);
    }
    return lastlen;
}


// Can be used to allocate a buffer of correct size.
int getFileSize(FILE* f) {
    fseek(f, 0, SEEK_END); // seek to end of file
    int size = ftell(f);
    rewind(f);
    return size;
}



int main(int argc, char** argv) 
{

    char buff[30];
    bzero(buff, sizeof(buff));
    int ret = readInBigBuffer(argv[1], buff, sizeof(buff));

    printf("bytes read:%d\n", ret);
    printf("%s\n", buff);
    return 0;
}
