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
 int yyerror(struct _commande_ast**, const char*); /* same for bison */
%}

%parse-param {struct _commande_ast* *pT} // yyparse(&t) call => *pT = *(&t) = t 

%union {
  struct _tree* exp;
  struct _commande_ast* com;
  struct _commande_ast* prog;
  double num;
  int valCal;
  int boolean;
  int opeBool;
  char* var;
} ;

%type  <exp> expression
%type  <com> commande
%type  <prog> programme
%token <num> NOMBRE
%token <boolean> BOOLEAN
%token <opeBool> OPERATIONBOOL
%token <var> VARIABLE
%token AFF
%token ';'


%left ';'
%left AFF
%left '!'
%left OPERATIONBOOL 
%left '?' ':'
%left '+' '-' // Le + et - sont prioritaire sur les opération booléen 
%left '*' '%' 
%nonassoc UMOINS


%%

resultat:   programme		{ *pT = $1; }

programme:  
      commande programme    { $$ = addComToProg($2,$1); }
    |   %empty              { $$ = newProgramme(); }       
;

commande: 
    expression ';'              { $$ = newCommanedeExpAST($1,';'); }              
  | ';'                         { $$ = newCommanedePVirgAST(';'); }
;

expression: 
    expression '+' expression	{ $$ = newBinaryAST('+',$1,$3); }
  | expression '-' expression	{ $$ = newBinaryAST('-',$1,$3); }
  | expression '%' expression	{ $$ = newBinaryAST('%',$1,$3); }
  | expression '*' expression	{ $$ = newBinaryAST('*',$1,$3); }
  | expression '/' expression	{ $$ = newBinaryAST('/',$1,$3); }
  | '(' expression ')'		    { $$ = $2; }
  | '-' expression %prec MOINSU	{ $$ = newUnaryAST('-',$2); }
  | expression OPERATIONBOOL expression         { $$ = newOpeBoolAST($2,$1,$3); }
  | expression '?' expression ':' expression    { $$ = newIfThenElseAST('?',':',$1,$3,$5); }
  | NOMBRE			{ $$ = newLeafAST($1, yylval.valCal); } 
  | VARIABLE			{ $$ = newVariableAST($1); } 
  | BOOLEAN         { $$ = newBooleanAST($1); } 
  | VARIABLE AFF expression { $$ = newAffAST($1,'=',$3); }
  ;

%%

#include <stdio.h>	/* printf */
int yyerror(struct _commande_ast **pT, const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */
