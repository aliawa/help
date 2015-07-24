#include <stdio.h>    // needed for FILE

int main(void) {

    char buff[30];
    buff[0] = '\0';

    while (fgets(buff, sizeof(buff), stdin)) {
        printf("%s\n", buff);
    }
}
