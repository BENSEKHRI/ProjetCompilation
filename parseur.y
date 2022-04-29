/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */

/* comlements: https://www.gnu.org/software/bison/manual/html_node/Parser-Function.html */
/* about implicit call: https://stackoverflow.com/questions/20106574/simple-yacc-grammars-give-an-error */

%{
 #include <stdio.h>	/* printf REMOVE AFTER TEST */
 #include "AST.h"
 int yylex(void);	/* flex with -Wall (implicite call) */
 int yyerror(struct _tree**, const char*); /* same for bison */
%}

%parse-param {struct _tree* *pT} // yyparse(&t) call => *pT = *(&t) = t 

%union {
  struct _tree* prog;
  double num;
  int valCal;
  int boolean;
  int opeBool;
  char* var;
} ;

%type  <prog> programme
%token <num> NOMBRE
%token <boolean> BOOLEAN
%token <opeBool> OPERATIONBOOL
%token <var> VARIABLE
%token AFF
%token ';'


%left ';'
%left AFF
%left '?' ':'
%left OPERATIONBOOL 
%left '+' '-' // Le + et - sont prioritaire sur les opération booléen 
%left '%' '*' '/'
%nonassoc MOINSU

%%

resultat:   programme		{ *pT = $1; }

programme:  
      commande programme
    |   %empty
;

commande: 
      progression ';'
    | VARIABLE AFF progression
    | ';'
;

progression: 
    progression '+' progression	{ $$ = newBinaryAST('+',$1,$3); }
  | progression '-' progression	{ $$ = newBinaryAST('-',$1,$3); }
  | progression '%' progression	{ $$ = newBinaryAST('%',$1,$3); }
  | progression '*' progression	{ $$ = newBinaryAST('*',$1,$3); }
  | progression '/' progression	{ $$ = newBinaryAST('/',$1,$3); }
  | '(' progression ')'		{ $$ = $2; }
  | '-' progression %prec MOINSU	{ $$ = newUnaryAST('-',$2); }
  | progression OPERATIONBOOL progression { $$ = newOpeBoolAST($2,$1,$3); }
  | progression '?' progression ':' progression { $$ = newIfThenElseAST('?',':',$1,$3,$5); }
  | NOMBRE			{ $$ = newLeafAST($1, yylval.valCal); } 
  | BOOLEAN         { $$ = newBooleanAST($1); } 
  ;

%%

#include <stdio.h>	/* printf */
int yyerror(struct _tree **pT, const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */
