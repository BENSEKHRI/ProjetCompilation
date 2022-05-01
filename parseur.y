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
  struct _commande_ast* prog;
  struct _commande_ast* com;
  struct _tree* exp;
  double num;
  int valCal;
  int boolean;
  int opeBool;
  char* var;
} ;

%type  <prog> programme
%type  <com> commande
%type  <exp> expression
%token <num> NOMBRE
%token <boolean> BOOLEAN
%token <opeBool> OPERATIONBOOL
%token <var> IDENT
%token AFF
%token ';'


%left ';'
%left AFF
%left '?' ':'
%left OPERATIONBOOL 
%left '+' '-'           // Le + et - sont prioritaire sur les opération booléen 
%left '*' '%' 
%nonassoc UMOINS


%%


resultat:   programme		{ *pT = $1; }

programme:  
      commande programme    { $$ = addComToProg($2,$1); }
    |   %empty              { $$ = newProgramme(); }       
;

commande: 
    expression ';'              { $$ = newCommandeExpAST($1,';'); }              
  | ';'                         { $$ = newCommandePVirgAST(';'); }
;

expression: 
    expression '+' expression	                { $$ = newBinaryAST('+',$1,$3); }
  | expression '-' expression	                { $$ = newBinaryAST('-',$1,$3); }
  | expression '*' expression	                { $$ = newBinaryAST('*',$1,$3); }
  | expression '%' expression	                { $$ = newBinaryAST('%',$1,$3); }
  | '(' expression ')'		                    { $$ = $2; }
  | '-' expression %prec UMOINS	                { $$ = newUnaryAST('-',$2); }
  | OPERATIONBOOL expression                    { if($1 != 6){printf("Parsing:: syntax error - expression ! _\n"); return 1;} else $$ = newOpeBoolAST($1,$2, NULL); }
  | expression OPERATIONBOOL expression         { if($2 == 6){printf("Parsing:: syntax error - expression _ ! _ \n"); return 1;} else $$ = newOpeBoolAST($2,$1,$3); }
  | expression '?' expression ':' expression    { $$ = newIfThenElseAST('?',':',$1,$3,$5); }
  | IDENT AFF expression                        { $$ = newAffAST($1,'=',$3); }
  | NOMBRE			                            { $$ = newLeafAST($1, yylval.valCal); } 
  | IDENT			                            { $$ = newVariableAST($1); } 
  | BOOLEAN                                     { $$ = newBooleanAST($1); } 
  ;

%%

#include <stdio.h>	/* printf */
int yyerror(struct _commande_ast **pT, const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */
