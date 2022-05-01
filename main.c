#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;

int main(int argc, char const *argv[]) {
    yyin = fopen(argv[1], "r");

    if (yyin != NULL) {                    // Avec un fichier en argument 
        if (!yyparse()) {                  // call to the parsing (and lexing) function
            printf("\nParsing:: syntax OK\n"); // reached if parsing follows the grammar
        }
        fclose(yyin);                      // On ferme le fichier qui a été ouvert
    } else {                               // Sans fichier en argument
        if (!yyparse()) {                      // call to the parsing (and lexing) function
            printf("\nParsing:: syntax OK\n"); // reached if parsing follows the grammar
        }
    }
    
    exit(EXIT_SUCCESS);
}