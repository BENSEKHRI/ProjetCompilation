/* file lexeur.l */
/* compilation: flex lexeur.l */
/* result: lex.yy.c = lexical analyser in C */

%{
    #include <stdio.h>       /* printf */
    #include <string.h>	     /* Manipulation de chaine de caractères */
    #include "parseur.tab.h" /* token constants def. in parseur.y via #define */
    
    /**
     * @brief   Cette fonction permet de convertir une chaine de caractère en un boolean (en C).
     *          Représenter par 1 pour True et 2 pour False.
     *          2 au lieu de 0 pour False pour des raison de besoin dans newBooleanAST (t->boolean).
     * 
     * @param str la chaine à convertir
     * @return 1 si True, 2 si False
     */
    int strToBool (const char *str){ 
        if(strcmp(str, "True") == 0) 
            return 1; 
        else if(strcmp(str, "False") == 0) 
            return 2;
    }


    /**
     * @brief   Cette fonction permet de convertir une chaine de caractère en une opération boolèene.
     * 
     * @param str la chaine à convertir
     * @return 1 si ==, 2 si <=, 3 si >=, 4 si <, 5 si > 
     */
    int strToOpeBool (const char *str) {
        if(strcmp(str, "==") == 0) 
            return 1;
        else if(strcmp(str, "<=") == 0) 
            return 2;
        else if(strcmp(str, ">=") == 0) 
            return 3;
        else if(strcmp(str, "<") == 0) 
            return 4;
        else if(strcmp(str, ">") == 0) 
            return 5;
        else if(strcmp(str, "!") == 0) 
            return 6;
        else if(strcmp(str, "||") == 0) 
            return 7;
        else if(strcmp(str, "&&") == 0) 
            return 8;
    }
%}

%%

function  						    { printf("lex::FUNCTION %s\n", yytext); return FUNCTION;}
return  						    { printf("lex::RETURN %s\n", yytext); return RETURN;}
if  						        { printf("lex::IF %s\n", yytext); return IF;}
else						        { printf("lex::ELSE %s\n", yytext); return ELSE;}
do						            { printf("lex::DO %s\n", yytext); return DO;}
while						        { printf("lex::WHILE %s\n", yytext); return WHILE;}
for						            { printf("lex::FOR %s\n", yytext); return FOR;}
0|[1-9][0-9]*  	                    { printf("lex::NOMBRE %s\n",yytext); yylval.num=atof(yytext); yylval.valCal = 1; return NOMBRE; } 
[0-9]*\.[0-9]+  	                { printf("lex::NOMBRE %s\n",yytext); yylval.num=atof(yytext); yylval.valCal = 2; return NOMBRE;}
[0-9]*\.?[0-9]+(e-?[0-9]+)?         { printf("lex::NOMBRE %s\n",yytext); yylval.num=atof(yytext); yylval.valCal = 3; return NOMBRE;}
NaN                                 { printf("lex::NOMBRE %s\n",yytext); yylval.num=atof(yytext); yylval.valCal = 4; return NOMBRE;}
True|False                          { printf("lex::BOOLEAN %s\n",yytext); yylval.boolean=strToBool(yytext); return BOOLEAN; }  
==|\<=|>=|<|>|!|"||"|&&             { printf("lex::OPERATIONBOOL %s\n",yytext); yylval.opeBool=strToOpeBool(yytext); return OPERATIONBOOL; }  
[a-zA-Z_][a-zA-Z0-9_]*              { printf("lex::IDENT %s\n",yytext); yylval.var = strdup(yytext); return IDENT;}
=							        { printf("lex::AFF %s\n", yytext); return AFF;} 
[ \t\n] 	                        { ; } /* ignore space, tab, and line return */
[€]                                 { return 0; } // exit sucessfully
. 		                            { printf("lex::char %s\n",yytext); return yytext[0]; } /* other one-char = token, ex. '+' */

%%
