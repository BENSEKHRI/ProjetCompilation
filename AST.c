#include <stdio.h>
#include <stdlib.h>
#include <string.h>	     /* Manipulation de chaine de caractères */
#include "AST.h"



/*-----------------------------------------------.
|                AST - expression                |
`-----------------------------------------------*/

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    // Condition d'ajout de taille pour ne cas - expression  float négatif.
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
  printf("newIfThenElseAST\n");
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

/**
 * @brief Cette fonction permet un affichage de la sortie post fixe de l'AST
 * 
 * @param t l'AST
 */
void codeAST (AST t) {
  if (t!=NULL) {   
    codeAST(t->left);
    if (t->left==NULL) {
      if(t->val)
        switch (t->valCal) {
          case 1: printf("CsteNb %.0lf\n", t->val); break;  // int
          case 2: printf("CsteNb %.2lf\n", t->val); break;  // float
          case 3: printf("CsteNb %.2e\n", t->val); break;   // float scientific
          case 4: printf("CsteNb NaN\n"); break;            // NaN
          default: printf("Error Float\n"); break;
        }

      if (t->boolean)
        switch (t->boolean) {
          case 1: printf("CsteBo True\n"); break;
          case 2: printf("CsteBo False\n"); break;
          default:  printf("Error boolean\n"); break;
        }         
    }
    else if (t->right == NULL) 
      printf("NegNb\n");
    else {
      if (t->right && t->ifThenElse) 
          printf("ConJmp %d\n", t->right->taille+=1);

      codeAST(t->right);

      if(t->car)
        switch (t->car) {
          case '+': printf("AddiNb\n"); break;
          case '-': printf("SubiNb\n"); break;
          case '%': printf("ModuNb\n"); break;  
          case '*': printf("MultNb\n"); break;   
          case '/': printf("DiviNb\n"); break;                                
        }

      if(t->opeBool)
        switch (t->opeBool) {
          case 1: printf("Equals\n"); break;
          case 2: printf("LoEqNb\n"); break;
          case 3: printf("GrEqNb\n"); break;
          case 4: printf("LoStNb\n"); break;
          case 5: printf("GrStNb\n"); break;
          default: printf("unknown\n"); break;
        }
    
      if (t->ifThenElse)
        printf("Jump %d\n", t->ifThenElse->taille);

      codeAST(t->ifThenElse);
    }
  }   
}

/**
 * @brief Cette fonction permet d'ecrire la sortie post fixe d'un AST dans un fichier. 
 * 
 * @param t AST
 * @param filename nom du fichier qui contiendera la sortie post fixe de l'AST 
 */
void echoCodeASTInFile (AST t, char const *filename) {
  FILE* f = fopen(filename, "r+");
  if (f != NULL) {
    fseek(f, 0, SEEK_END);
    if (t != NULL) {
      echoCodeASTInFile(t->left, filename);
      if (t->left==NULL) {
        if(t->val) {
          fseek(f, 0, SEEK_END);
          switch (t->valCal) {
            case 1: fprintf(f, "CsteNb %.0lf\n", t->val); break;  // int
            case 2: fprintf(f, "CsteNb %.2lf\n", t->val); break;  // float
            case 3: fprintf(f, "CsteNb %.2e\n", t->val); break;   // float scientific
            case 4: fprintf(f, "CsteNb NaN\n"); break;            // NaN
            default: fprintf(f, "Error Float\n"); break;
          }
        }
        
        if (t->boolean) {
          fseek(f, 0, SEEK_END);
          switch (t->boolean) {
            case 1: fprintf(f, "CsteBo True\n"); break;
            case 2: fprintf(f, "CsteBo False\n"); break;
            default:  fprintf(f, "Error boolean\n"); break;
          } 
        }
      } 
      else if (t->right == NULL) {
        fseek(f, 0, SEEK_END);
        fprintf(f,"NegNb\n");
      }
      else {
        if (t->right && t->ifThenElse) {
          fseek(f, 0, SEEK_END);
          fprintf(f, "ConJmp %d\n", t->right->taille+=1);
        }
        
        fseek(f, 0, SEEK_END);
        echoCodeASTInFile(t->right, filename);
        
        if (t->car) {
          fseek(f, 0, SEEK_END);
          switch (t->car) {
            case '+': fprintf(f,"AddiNb\n"); break;
            case '-': fprintf(f,"SubiNb\n"); break;
            case '%': fprintf(f,"ModuNb\n"); break; 
            case '*': fprintf(f,"MultNb\n"); break;  
            case '/': fprintf(f,"DiviNb\n"); break;                                     
              break;
          }
        }

        if(t->opeBool) {
          fseek(f, 0, SEEK_END);
          switch (t->opeBool) {
            case 1: fprintf(f, "Equals\n"); break;
            case 2: fprintf(f, "LoEqNb\n"); break;
            case 3: fprintf(f, "GrEqNb\n"); break;
            case 4: fprintf(f, "LoStNb\n"); break;
            case 5: fprintf(f, "GrStNb\n"); break;
            default: fprintf(f, "unknown\n"); break;
          }
        }

        if (t->ifThenElse) {
          fseek(f, 0, SEEK_END);
          fprintf(f,"Jump %d\n", t->ifThenElse->taille);
        }
 
        fseek(f, 0, SEEK_END);
        echoCodeASTInFile(t->ifThenElse, filename);
      }
      fclose(f);
    }
  } else {
    printf("Erreur lors de lecture / création du ficheir\n");
    exit(1);
  }
}



/*-----------------------------------------------.
|                AST - commande                  |
`-----------------------------------------------*/

/**
 * @brief   Cette fonction permet de créer une commande à partir d'une expression et d'un point virgule ';'
 *          expression ';'
 * 
 * @param expression l'AST de l'expression.
 * @param pVirg le point virgule de la fin de l'expression
 * @return commande_ast la commande créee.
 */
commande_ast newCommanedeExpAST(AST expression, char pVirg) {
  commande_ast c =(struct _commande_ast*) malloc(sizeof(struct _commande_ast));
  if (c!=NULL){	/* malloc ok */
    c->expression = expression;
    c->pVirg = pVirg;
  } else printf("MALLOC! ");
  return c;
}


/**
 * @brief   Cette fonction premet de créer une commande à partir d'une affectation.
 *          VARIABLE AFF expression
 * 
 * @param expression l'AST de l'expression.
 * @param var La variable.
 * @param aff le = de l'affectation
 * @param pVirg le point virgule de la fin de l'expression
 * @return commande_ast la commande créee.
 */
commande_ast newCommanedeAffAST(AST expression, char* var, char aff, char pVirg) {
  commande_ast c =(struct _commande_ast*) malloc(sizeof(struct _commande_ast));
  if (c!=NULL){	/* malloc ok */
    c->var = var;
    c->aff = aff;
    c->pVirg = pVirg;
    c->expression = expression;
  } else printf("MALLOC! ");
  return c;
}


/**
 * @brief   Cette fonction permet de créer une commande à partir d'un point virgule ';'
 * 
 * @param pVirg le point virgule de la fin de l'expression
 * @return commande_ast la commande créee.
 */
commande_ast newCommanedePVirgAST(char pVirg) {
  commande_ast c =(struct _commande_ast*) malloc(sizeof(struct _commande_ast));
  if (c!=NULL){	/* malloc ok */
    c->pVirg = pVirg;
    c->expression = newBinaryAST(pVirg, NULL, NULL);
  } else printf("MALLOC! ");
  return c;
}


/**
 * @brief   Cette fonction permet de libérer la mémoire allouée par une commande
 * 
 * @param c La commande.
 */
void freeCommande(commande_ast c) {
  if (c!=NULL) {
    freeAST(c->expression);
    free(c->var);
    free(c);
  }
}


/**
 * @brief   Cette fonction permet d'afficher une commande.
 *          Une commande est afficher une deux '|' ainsi:  |commande |
 * 
 * @param c la commande à afficher.
 */
void printCommande(commande_ast c) {
  if (c!=NULL) {
    printf("| ");
    if (c->expression) {
      if (c->var) {
        printf(":%s: ", c->var);
        printf(":%c: ", c->aff);
        printAST(c->expression);  
        printf(":%c: ", c->pVirg);
      } else {
        printAST(c->expression);  
        printf(":%c: ", c->pVirg);
      }      
    } else
        printf(":%c: ", c->pVirg);
    printf("| ");
  }
}



/*-----------------------------------------------.
|                   Programme                    |                  
`-----------------------------------------------*/

/**
 * @brief   Cette fonction permet d'initialiser un programme vide.
 *          - Le programme est une liste de commandes.
 * 
 * @return programme_ast le programme initial.
 */
programme_ast newProgramme () {
  programme_ast p = NULL;
  return p;
}


/**
 * @brief   Cette fonction permet d'ajouter une commande à la fin d'un programme.
 * 
 * @param prog Le programme auquel on ajoute la commande.
 * @param newCommande La commande a ajotuer
 * @return programme_astle prgramme après ajout de la commande
 */
programme_ast addComToProg (programme_ast prog, commande_ast newCommande) {
  if (newCommande) {
    newCommande->suivant = NULL;

    if (!prog) 
      return newCommande;  
    else {
      newCommande->suivant = prog;
      return newCommande;
    }
  } else {
    printf("Error - addComToProg\n");
    exit(EXIT_FAILURE);
  }
}


/**
 * @brief   Cette fonction permet de libérer la mémoire alloué par un programme.
 * 
 * @param prog Le programme.
 */
void freeProg(programme_ast prog) {
  if (prog!=NULL) {
    commande_ast commandeSuivante = NULL;
    while (prog) {
      commandeSuivante = prog->suivant;
      freeCommande(prog);
      prog = commandeSuivante;
    }
  }
}


/**
 * @brief   Cette fontion permet d'afficher un programme.
 * 
 * @param prog le programme à afficher.
 */
void printProg(programme_ast prog) {
  if (prog) { 
    printf("Program:\n");
    commande_ast tmpCommande = prog;
    while (tmpCommande) {
      printCommande(tmpCommande);
      printf("\n");
      tmpCommande = tmpCommande->suivant;
    }
  } else {
    printf("Error - printProg - Liste vide !\n");
    exit(EXIT_FAILURE);
  }
}
