#include <stdio.h>
#include <stdlib.h>

int main(void) {
    if (!yyparse()) {                      // call to the parsing (and lexing) function
        printf("\nParsing:: syntax OK\n"); // reached if parsing follows the grammar
    }
    exit(EXIT_SUCCESS);
}