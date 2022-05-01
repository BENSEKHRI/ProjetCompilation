/* file lexeur.l
* compilation: flex lexeur.l
* result: lex.yy.c = lexical analyser in C
*/
%{
    #include <stdio.h> // printf
    #include "parseur.tab.h" // token constants defined in parseur.y via #define
%}

%%

0|[1-9][0-9]*|[0-9]*\.[0-9]+            { printf("lex::NUMBER %s\n",yytext); return NUMBER; }
[0-9]*\.?[0-9]+(e-?[0-9]+)?             { printf("lex::NUMBER %s\n",yytext); return NUMBER; }
NaN                                     { printf("lex::NUMBER %s\n",yytext); return NUMBER; }
True|False                              { printf("lex::BOOLEAN %s\n",yytext); return BOOLEAN; }  
==|\<=|>=|<|>                           { printf("lex::OPERATIONBOOL %s\n",yytext); return OPERATIONBOOL; }  
[ \t\n]|[/\*a-z*A-Z*0-9**/] 	        { ; } /* ignore space, tab, and line return and comments*/
[;]                                     { return 0; } // exit sucessfully
.                                       { printf("lex::char %s\n",yytext); return yytext[0]; } // other one-

%%
int yywrap(void){ return 1; } // function called at the end of the file