// ------------------------------- 
//          PROLOG
// ------------------------------- 
%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char*

void yyerror (char const *s);

char buff[100];
%}

// ------------------------------- 
//      BISON DECLARATIONS 
// ------------------------------- 
%token TOKEN INT


// ------------------------------- 
//       GRAMMAR RULES
// ------------------------------- 
%%  
input : /* empty */
      | exp '\n'    { printf ("%s\n", $1); }
      ;

exp   : TOKEN       { strcat(buff, $1); $$=buff; }
      | exp TOKEN   { strcat(buff, "-"); strcat(buff, $2); $$=buff; }
      ;
%%

// ------------------------------- 
//       EPILOGUE
// ------------------------------- 
void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}

/* Controlling function */
int main (int argc, char** argv)
{
    return yyparse();
}



