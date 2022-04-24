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