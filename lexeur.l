/* file lexeur.l
* compilation: flex lexeur.l
* result: lex.yy.c = lexical analyser in C
*/
%{
    #include <stdio.h> // printf
    #include "parseur.tab.h" // token constants defined in parseur.y via #define
%}

%%

0|[1-9][0-9]*|[1-9][0-9]*,[1-9][0-9]*   {   printf("lex::NUMBER %s\n",yytext);
                    yylval.dval=atoi(yytext); yylval.ival=atoi(yytext); return NUMBER; }
[ \t\n]           { ; } // ignore space and tab
.               { printf("lex::char %s\n",yytext); return yytext[0]; } // other one-

%%
int yywrap(void){ return 1; } // function called at the end of the file