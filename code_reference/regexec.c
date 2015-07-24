// Testing regcomp, regerror, regexec, regfree
// compares its standard input against the regular expression given (on command line)
//
// TEST:
// echo 'Bob <sip:bob@bioloxi.com>;tag=a6cd5cf' | a.out 'sip:(.*)@(.*)>.*tag=(.*)'
//

#include <stdio.h> 
#include <string.h>             // for index(): */
#include <regex.h>
 
#define MAX_ERR_LENGTH   80     // max error message length 
#define MAX_TXT_LENGTH   600    // max length of a line of text from stdin 
#define MAX_SUB_EXPR     5      // max number of subexpressions to match
#define MAX_SUB_EXPR_LEN 30     // max sub expression length




int main(int argc, char *argv[]) {
     
    regex_t myre;                // will contain the regular expression 
    regmatch_t pm[MAX_SUB_EXPR]; // will contain offsets to sub expressions
    int err;
    char err_msg[MAX_ERR_LENGTH];
    char buff[MAX_SUB_EXPR_LEN];
    char text[MAX_TXT_LENGTH];
    
    // safe check on cmd line args 
    if ( argc < 2 || argc > 2 ) {
        printf("Usage:\n\t%s 'RE' < file\n\tOR\n\techo \"string\" | qegrep 'RE'\n", argv[0]);
        return 1;
    }
   
    // compiles the RE. If this step fails, reveals what's wrong with the RE 
    if ( (err = regcomp(&myre, argv[1], REG_EXTENDED)) != 0 ) {
        regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
        printf("regcomp error:%s  regular_expression:'%s'\n", err_msg, argv[1]);
        return 1;
    }
    
    // "executes" the RE against the text taken from stdin
    while ( fgets(text, MAX_TXT_LENGTH, stdin) != NULL ) {
        // we rely on the fact that text contains newline chars 
        *(index(text, '\n')) = '\0';

        if ( (err = regexec(&myre, text, MAX_SUB_EXPR, pm, 0)) == 0 ) {
            int i=0;
            for(;i<MAX_SUB_EXPR;++i){
                if (pm[i].rm_so != -1) {
                    int len = pm[i].rm_eo - pm[i].rm_so;
                    bzero(buff,sizeof(buff));
                    strncpy(buff, text+pm[i].rm_so, len);
                    puts(buff);
                }
            }
        } else if ( err != REG_NOMATCH ) {
            // error in regexec
            regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
            printf("regexec error:%s\n", err_msg);
            return 2;
        }
    } 

    // meaningless here. Useful in many other situations.
    regfree(&myre);
    
    return 0;
}
