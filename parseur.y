%{ // the code between %{ and %} is copied at the start of the generated .c
    #include <stdio.h>
    int yylex(void); // -Wall : avoid implicit call
    int yyerror(const char*); // on fonctions defined by the generator
%}

%token NUMBER

%left '+' '-'
%left '*'
%nonassoc UMOINS

%%

result: expression

expression:
        expression '+' expression
    |   expression '-' expression
    |   expression '*' expression
    |   '(' expression ')'
    |   '-' expression %prec UMOINS
    |   NUMBER
;