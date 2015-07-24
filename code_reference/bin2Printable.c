
/*
 Converting binary to Hexadecimal
 bin2Hex
*/

#include <stdio.h>

void printBinArray(int len, unsigned char* b) {
    int i=0;
    for (;i<len;++i) {
        printf("%0x ", b[i]);
    }
}


void bin2Printable(int srcLen, unsigned char* src, int dstLen, char* dst) {
    int i=0;
    char* limit = dst+dstLen;
    for(;i<srcLen && dst<limit; ++i,++src) {
        snprintf(dst, 4, "%02x ", *src);
        dst+=3;

        // Line wrap after 20 bytes
        if ((i+1)%20 ==0){
            *dst='\n';
            dst++;
        }    
    }
    *dst='\0';
}

int main (int argc, char** argv) {
    unsigned char buffBinary[] = {0x1,  0x9,  0xff, 0xa,  1,    2,    3,    0,    0x0, 
                                  '\5', '\6', 0x8,  9,    255,  0xf,  104,  '\0', 5,
                                  3,    5 ,   0xb,  55
                                 };
    char buffPrintable[400];

    printBinArray(22, buffBinary);
    printf("\n");

    bin2Printable(22, buffBinary, 400, buffPrintable);
    printf("--- result of bin2Printable ---\n");
    printf ("%s\n", buffPrintable);
}

