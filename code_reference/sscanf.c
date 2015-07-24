#include <stdio.h>
#include <strings.h>

// Testing sscanf
// TEST: a.out "axxx:bnx:czx" 
// TEST: a.out "abc:def:ghi" 
// TEST: a.out "axxx:bnx:cz90x" 
// TEST: a.out "1234:5678:9033434"
//


char part1[5]={0};
char part2[5]={0};
char part3[5]={0};
int l1=0,l2=0,l3=0;


val_reset()
{
    bzero(part1,sizeof(part1));
    bzero(part2,sizeof(part2));
    bzero(part3,sizeof(part3));
    l1=0;l2=0;l3=0;
}


int main (int argc, char** argv) 
{
    // parse accepted character range
    val_reset();
    printf("Parse characters from the given range; stop when non-matching char found\n");    
    sscanf(argv[1], "%[a-z]:%[a-r]:%s", &part1, &part2, &part3);
    printf("part1:%s\npart2:%s\npart3:%s\n\n", part1, part2, part3);


    // specifying "maximum field width" %<integer><conversion-specifier>
    // for example %3s
    val_reset();
    printf("Parse with max field width of 3 characters\n");
    sscanf(argv[1], "%3s:%3s:%3s", &part1, &part2, &part3);
    printf("part1:%s\npart2:%s\npart3:%s\n\n", part1, part2, part3);
    

    // using %n to read the number of character consumed so far.
    val_reset();
    printf("Parse and store the number of chararters read so far from input\n");
    sscanf(argv[1], "%[a-z]%n:%[a-z]%n:%s%n", &part1, &l1, &part2, &l2, &part3, &l3);
    printf("part1:%s\tlen1:%d\npart2:%s\tlen2:%d\npart3:%s\tlen3:%d\n\n\n", 
            part1, l1, part2, l2, part3,l3);

    // Reading int
    val_reset();
    printf("Reading integers only\n");
    sscanf(argv[1], "%d:%d:%d", &l1,  &l2, &l3);
    printf("part1:%d\npart2:%d\npart3:%d\n\n", l1, l2, l3);
    

    // discard portions of input
    val_reset();
    printf("Discarding first 2 segments\n");
    sscanf(argv[1], "%*[a-z]:%*[a-z]:%s%n", &part3, &l1);
    printf("part3:%s\n", part3);
    printf("input chars consumed:%d\n", l1);
}
