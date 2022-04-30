/* file TP.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */
#include "parseur.tab.h"/* header for TOKEN */
#include "AST.c"	/* AST fonctions */

extern FILE* yyin;

int main(int argc, char const *argv[]) 
{
    yyin = fopen(argv[1], "r");
    programme_ast p; 				/* &t allows to modifie the tree */

    if (yyin != NULL) {     // Avec un fichier en argument 
        if (yyparse(&p)==0) { 		/* yyparse calls yylex */
            printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
            
            /* print the obtained tree */
            if (p->expression->left!=NULL) printf("Root symbol:: %c\n", p->expression->car);	/* check if car at root */
            printProg(p); printf("\n");
                            
            freeProg(p);
        } 
        fclose(yyin); // On ferme le fichier qui a été ouvert
    } else {                // Sans fichier en argument
        if (yyparse(&p)==0) {                      // call to the parsing (and lexing) function
            printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
            
            /* print the obtained tree */
            if (p->expression->left!=NULL) printf("Root symbol:: %c\n", p->expression->car);	/* check if car at root */
            printProg(p); printf("\n");
            freeProg(p);        }
    }

    exit(EXIT_SUCCESS);
}

