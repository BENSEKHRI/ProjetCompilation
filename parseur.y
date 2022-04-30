%{ // the code between %{ and %} is copied at the start of the generated .c
    #include <stdio.h>
    int yylex(void); // -Wall : avoid implicit call
    int yyerror(const char*); // on fonctions defined by the generator
%}


%token NUMBER
%token BOOLEAN
%token OPERATIONBOOL
%token VARIABLE
%token AFF
%token ';'


%left ';'
%left AFF
%left '?' ':'
%left OPERATIONBOOL 
%left '+' '-' // Le + et - sont prioritaire sur les opération booléen 
%left '%' '*'
%nonassoc UMOINS

%%

result: programme

programme:  
      commande programme
    |   %empty
;


commande: 
      expression ';'
    | ';'
;

expression:
        expression '+' expression
    |   expression '-' expression
    |   expression '%' expression
    |   expression '*' expression
    |   '(' expression ')'
    |   '-' expression %prec UMOINS
    |   expression OPERATIONBOOL expression
    |   expression '?' expression ':' expression
    |   NUMBER
    |   BOOLEAN
    |   VARIABLE
    |   VARIABLE AFF expression
;


%%  // denotes the end of the grammar
    // everything after %% is copied at the end of the generated .c
int yyerror(const char *msg) { // called by the parser if the parsing fails
    printf("Parsing:: syntax error\n");
    return 1; // to distinguish with the 0 retured by the success
}
