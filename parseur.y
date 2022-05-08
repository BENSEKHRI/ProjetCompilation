%{ // the code between %{ and %} is copied at the start of the generated .c
    #include <stdio.h>
    int yylex(void); // -Wall : avoid implicit call
    int yyerror(const char*); // on fonctions defined by the generator
%}


%token NUMBER
%token BOOLEAN
%token OPERATIONBOOL
%token FUNCTION
%token RETURN
%token IF
%token ELSE
%token DO
%token WHILE
%token FOR
%token IDENT
%token AFF
%token ';'



%left '{' '}'
%left ';'
%left AFF
%left IF ELSE DO WHILE FOR FUNCTION RETUR
%left '!'
%left OPERATIONBOOL 
%left '?' ':'
%left '+' '-' // Le + et - sont prioritaire sur les opération booléen 
%left '*' '%' 
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
    | '{' programme '}'                         
    | IF '(' expression ')' commande ELSE commande                         
    | DO commande WHILE '(' expression ')'                         
    | WHILE '(' expression ')' commande                         
    | FOR '(' expression ';' expression ';' expression ')' commande                         
    | FUNCTION IDENT '(' decl_args ')' '{' programme '}'                         
    | RETURN expression ';'                         
;

decl_args: 
        %empty
    |   IDENT
    |   IDENT ',' decl_args
;

expression:
        expression '+' expression
    |   expression '-' expression
    |   expression '*' expression
    |   expression '%' expression
    |   '(' expression ')'
    |   '-' expression %prec UMOINS
    |   '!' expression 
    |   expression OPERATIONBOOL expression
    |   expression '?' expression ':' expression
    |   IDENT '(' arguments ')'
    |   IDENT AFF expression 
    |   NUMBER
    |   BOOLEAN
    |   IDENT			 
;

arguments: 
        %empty 
    |   expression
    |   expression ','arguments
;

%%  // denotes the end of the grammar
    // everything after %% is copied at the end of the generated .c
int yyerror(const char *msg) { // called by the parser if the parsing fails
    printf("Parsing:: syntax error\n");
    return 1; // to distinguish with the 0 retured by the success
}
