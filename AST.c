#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
#include <string.h>	     /* Manipulation de chaine de caractères */


/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    // Condition d'ajout de taille pour ne cas - exp  float négatif.
    if (left && right) t->taille+=1+left->taille+right->taille;
    if (left && !right) t->taille+=1+left->taille;
    if (right && !left) t->taille+=1+right->taille;
    
    t->car=car;
    t->left=left;
    t->right=right;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and two AST sons */
AST newOpeBoolAST(int opeBool, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->taille+=1+left->taille+right->taille;
    t->opeBool=opeBool;
    t->left=left;
    t->right=right;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a if then else operation and 3 AST sons */
AST newIfThenElseAST(char car1, char car2, AST ifSon, AST thenSon, AST elseSon) {
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->taille+=2+ifSon->taille + thenSon->taille + elseSon->taille;
    t->car=car1;
    t->car2=car2;
    t->left=ifSon;
    t->right=thenSon;
    t->ifThenElse=elseSon;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(double val, int valCal)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->taille++;
    t->val=val;
    t->valCal=valCal;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST leaf from a boolean */
AST newBooleanAST(int boolean)
{  
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->taille++;
    t->boolean=boolean;
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
    freeAST(t->ifThenElse);
    free(t);
  }
}

/* infix print an AST*/
void printAST(AST t)
{
  if (t!=NULL) {
    printf("\n-- Taille: %d\n", t->taille);
    printf("[ ");
    printAST(t->left);
    /* check if node is car|val */
    if (t->left==NULL) {
      if (t->val) 
        switch (t->valCal) {
          case 1: printf(":%.0lf: ", t->val); break;  // int
          case 2: printf(":%.2lf: ", t->val); break;  // float
          case 3: printf(":%.2e: ", t->val); break;   // float scientific
          case 4: printf(":NaN: "); break;            // NaN
          default: printf("Error Float\n"); break;
        }
         
      if (t->boolean)
        switch (t->boolean) {
          case 1: printf(":True: "); break;
          case 2: printf(":False: "); break;
          default:  printf("Error Boolean\n"); break;
        }
    }
    else {
      if(t->car)
        printf(":%c: ",t->car);     
      if(t->opeBool)
        switch (t->opeBool) {
          case 1: printf(":==: "); break;
          case 2: printf(":<=: "); break;
          case 3: printf(":>=: "); break;
          case 4: printf(":<: "); break;
          case 5: printf(":>: "); break;
          default: printf("Error Boolean Operation\n"); break;
        }
    }
    printAST(t->right);
    
    if (t->car2)
      printf(":%c: ",t->car2); 
    
    printAST(t->ifThenElse);
    printf("] ");
  }
}

