#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car=car;
    t->left=left;
    t->right=right;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(int val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=val;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

/* delete an AST */
void freeAST(AST t)
{
  if (t!=NULL) {
    freeAST(t->left);
    freeAST(t->right);
    free(t);
  }
}

/* infix print an AST*/
void printAST(AST t)
{
  if (t!=NULL) {
    printf("[ ");
    printAST(t->left);
    /* check if node is car|val */
    if (t->left==NULL) printf(":%d: ",t->val); else printf(":%c: ",t->car);
    printAST(t->right);
    printf("] ");
  }
}

/**
 * @brief Cette fonction permet un affichage de la sortie post fixe de l'AST
 * 
 * @param t l'AST
 */
void code (AST t) {
  if (t!=NULL) {
    code(t->left);
    if (t->left==NULL) 
      printf("CsteNb %d\n",t->val); 
    else if (t->right == NULL) 
      printf("NegNb\n");
    else 
      switch (t->car)
      {
        case '+':
          printf("AddiNb\n");
          break;
        case '-':
          printf("SubiNb\n");
          break;
        case '%':
          printf("ModuNb\n");
          break;  
        case '*':
          printf("MultNb\n");
          break;   
        case '/':
          printf("DiviNb\n");
          break;                                
        default: printf("unknown\n");
          break;
      }
    code(t->right);
  }
}

/**
 * @brief Cette fonction permet d'ecrire la sortie post fixe d'un AST dans un fichier. 
 * 
 * @param t AST
 * @param filename nom du fichier qui contiendera la sortie post fixe de l'AST 
 */
void echoCodeInFile (AST t, char const *filename) {
  FILE* f = fopen(filename, "r+");
  if (f != NULL) {
    fseek(f, 0, SEEK_END);
    if (t!=NULL) {
      echoCodeInFile(t->left, filename);
      if (t->left==NULL) {
        fprintf(f,"CsteNb %d\n", t->val);
      } 
      else if (t->right == NULL) {
        fseek(f, 0, SEEK_END);
        fprintf(f,"NegNb\n");
      }
      else 
        switch (t->car)
        {
          case '+':
            fseek(f, 0, SEEK_END);
            fprintf(f,"AddiNb\n");
            break;
          case '-':
            fseek(f, 0, SEEK_END);
            fprintf(f,"SubiNb\n");
            break;
          case '%':
            fseek(f, 0, SEEK_END);
            fprintf(f,"ModuNb\n");
            break; 
          case '*':
            fseek(f, 0, SEEK_END);
            fprintf(f,"MultNb\n");
            break;  
          case '/':
            fseek(f, 0, SEEK_END);
            fprintf(f,"DiviNb\n");
            break;                                     
          default: fprintf(f,"unknown\n");
            break;
        }
      fclose(f);
      echoCodeInFile(t->right, filename);
    }
  } else {
    printf("Erreur lors de leccture / création du ficheir\n");
    exit(1);
  }
}

