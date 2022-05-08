/* file TP.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <stdio.h>       /* printf */
#include <stdlib.h>      /* exit */
#include "parseur.tab.h" /* header for TOKEN */
#include "AST.c"         /* AST fonctions */

extern FILE* yyin;
extern symboles SYMBOL_PROG;


int modifyExtensionJs(char const *str);

int main(int argc, char *argv[])
{
    programme_ast prog; /* &prog allows to modifie the tree */

    if (argv[1])
    { // execution avec argument
        yyin = fopen(argv[1], "r");
        if (yyin != NULL)
        {                                        // Le fichier existe
            if (modifyExtensionJs(argv[1]) == 1) // fichier js en argument
            {
                if ((yyparse(&prog) == 0))
                {                                        /* yyparse calls yylex */
                    printf("\nParsing:: syntax OK\n\n"); /* reached if parsing folllows the grammar */

                    /* print the obtained tree */
                    if (prog->expression->left != NULL)
                        printf("Root symbol:: %c\n", prog->expression->car); /* check if car at root */

                    writeCodeProgInFile(prog, argv[1]);
                    printf("\n/*-------------------------------------.\n");
                    printf("|    Writing the file %s    |\n", argv[1]);
                    printf("`-------------------------------------*/\n");
                    FILE *f = fopen(argv[1], "r+");
                    if (f != NULL)
                    {
                        fseek(f, 0, SEEK_END);
                        fprintf(f, "Halt\n");
                        fclose(f);
                    }
                    else
                    {
                        printf("Error: reading / creating the file\n");
                        exit(1);
                    }

                    printf("\n/*----------.\n");
                    printf("|    AST    |\n");
                    printf("`----------*/\n");
                    printProg(prog);
                    printf("\n\n");
                    freeProg(prog);
                }
                exit(EXIT_SUCCESS);
            }
            else
            { // fichier non js en argument
                printf("\n/*-----------------------------------------------------------.\n");
                printf("|    Error - The file: %s is not a js file  !     |\n", argv[1]);
                printf("`-----------------------------------------------------------*/\n");
                fclose(yyin);
                exit(EXIT_FAILURE);
            }
            fclose(yyin);
        }
        else
        { // Le fichier n'existe pas
            printf("\n/*-----------------------------------------------------------.\n");
            printf("|    Error - The file: %s does not exist !     |\n", argv[1]);
            printf("`-----------------------------------------------------------*/\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    { // execution sans argument
        if ((yyparse(&prog) == 0))
        {                                        /* yyparse calls yylex */
            printf("\nParsing:: syntax OK\n\n"); /* reached if parsing folllows the grammar */

            /* print the obtained tree *
            if (prog->expression->left != NULL)
                printf("Root symbol:: %c\n", prog->expression->car); * check if car at root */
            printf("\n/*----------.\n");
            printf("|    AST    |\n");
            printf("`----------*/\n");
            printProg(prog);
            printf("\n\n");

            printf("/*----------------.\n");
            printf("|    POST-FIXE    |\n");
            printf("`----------------*/\n");
            codeProg(prog);
            printf("Halt\n");
            freeProg(prog);
        }
        exit(EXIT_SUCCESS);
    }
    
    freeProg(prog);
    exit(EXIT_SUCCESS);
}

/**
 * @brief La fonction prend le nom d'un fichier, teste s'il a une extension si c'est
 *        le cas et que c'est un fichier "js" elle créer un nouveau fichier avec le meme
 *        nom mais avec l'extension .jsm et renvoi 1.
 *        Si le fichier n'a pas d'extension ou bien que l'exention n'est pas js, elle retourne 0.
 *
 * @param str le nom d'un fichier.
 * @return int return 1 si c'est un fichier js, retourne 0 sinon
 */
int modifyExtensionJs(char const *str)
{
    if (strchr(str, '.'))
    { // fichier sans extension
        if (strcmp(".js", strchr(str, '.')) == 0)
        { // fichier js
            int taille = (strlen(str) - strlen(strchr(str, '.')));
            char *dest = (char *)malloc(taille * sizeof(char));
            int i = 0;
            while (str[i] != '.')
            {
                dest[i] = str[i];
                i++;
            }
            strcat(dest, ".jsm");
            strcpy((char *)str, dest);
            free(dest);
            FILE *f = fopen(str, "w+"); // création du fichier .jsm avec le nom du fichier js
            if (f == NULL)
            {
                printf("Couldn't open file: %s\n", str);
                exit(1);
            }
            else
            {
                fclose(f);
                return 1;
            }
        }
        else // fichier avec ext mais pas js
            return 0;
    }
    else
    { // fichier sans extension
        printf("\n/*-------------------------------------------------------.\n");
        printf("|      The file in argument has no extension !           |\n");
        printf("`-------------------------------------------------------*/\n");
        return 0;
    }
}