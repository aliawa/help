%option noyywrap nodefault yylineno
%{
#define YYSTYPE char*
#include "flexbison_test.tab.h" /* Generated by Bison */
%}

STR         [A-Za-z][A-Za-z0-9_-]*

%%  //---------------------------

"\n"       { return yytext[0];}
{STR}      { yylval=strdup(yytext);  return TOKEN; }
[ \t\n]+   /* eat up white spaces */
.          { yyerror("Mystery character %c\n", *yytext); }

%% //---------------------------

