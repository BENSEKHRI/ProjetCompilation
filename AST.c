#include <stdio.h>
#include <stdlib.h>
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

/* create an AST from a root value and two AST sons */
AST newOpeBoolAST(int opeBool, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->opeBool=opeBool;
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

/* create an AST leaf from a boolean */
AST newBooleanAST(int boolean)
{  
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
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
    if (t->left==NULL) {
      if (t->val) 
        printf(":%d: ",t->val); 
      if (t->boolean)
        switch (t->boolean) {
          case 1: printf(":True: "); break;
          case 2: printf(":False: "); break;
          default:  printf("Error boolean\n"); break;
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
          default: printf("Error boolean operation\n"); break;
        }
    }
    printAST(t->right);
    printf("] ");
  }
}

