#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* Manipulation de chaine de caractères */
#include "AST.h"

symboles SYMBOL_PROG = NULL;

/*-----------------------------------------------.
|                AST - expression                |
`-----------------------------------------------*/

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t = (struct _tree *)malloc(sizeof(struct _tree));
  if (t != NULL)
  { /* malloc ok */
    // Condition d'ajout de taille pour ne cas - expression  float négatif.
    if (left && right)
      t->taille += 1 + left->taille + right->taille;
    if (left && !right)
      t->taille += 1 + left->taille;
    if (right && !left)
      t->taille += 1 + right->taille;

    t->car = car;
    t->left = left;
    t->right = right;
  }
  else
    printf("MALLOC! ");
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
  AST t = (struct _tree *)malloc(sizeof(struct _tree));
  if (t != NULL)
  { /* malloc ok */
    t->taille++;
    t->val = val;
    t->valCal = valCal;
    t->left = NULL;
    t->right = NULL;
  }
  else
    printf("MALLOC! ");
  return t;
}

/* create an AST leaf from a boolean */
AST newBooleanAST(int boolean)
{
  AST t = (struct _tree *)malloc(sizeof(struct _tree));
  if (t != NULL)
  { /* malloc ok */
    t->taille++;
    t->boolean = boolean;
    t->left = NULL;
    t->right = NULL;
  }
  else
    printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and two AST sons */
AST newOpeBoolAST(int opeBool, AST left, AST right)
{
  AST t = (struct _tree *)malloc(sizeof(struct _tree));
  if (t != NULL)
  { /* malloc ok */
    if (left && right)
      t->taille += 1 + left->taille + right->taille;
    if (left && !right)
      t->taille += 1 + left->taille;
    t->opeBool = opeBool;
    t->left = left;
    t->right = right;
  }
  else
    printf("MALLOC! ");
  return t;
}

/* create an AST from a if then else operation and 3 AST sons */
AST newIfThenElseAST(char car1, char car2, AST ifSon, AST thenSon, AST elseSon)
{
  AST t = (struct _tree *)malloc(sizeof(struct _tree));
  if (t != NULL)
  { /* malloc ok */
    t->taille += 2 + ifSon->taille + thenSon->taille + elseSon->taille;
    t->car = car1;
    t->car2 = car2;
    t->left = ifSon;
    t->right = thenSon;
    t->ifThenElse = elseSon;
  }
  else
    printf("MALLOC! ");
  return t;
}

/**
 * @brief   Cette fonction premet de créer une commande à partir d'une affectation.
 *          VARIABLE AFF expression
 *
 * @param var La variable.
 * @param aff le = de l'affectation
 * @param son l'expression de la variable.
 * @return AST l'expression créee.
 */
AST newAffAST(char *var, char aff, AST son)
{
  AST t = (struct _tree *)malloc(sizeof(struct _tree));
  if (t != NULL)
  { /* malloc ok */
    t->taille += 1 + son->taille;
    t->var = var;
    t->aff = aff;
    t->left = son;
    t->right = NULL;
    t->ifThenElse = NULL;
    // Afficher les identifiants prénsent et ajout des nouveau || modification des présent
    searchSymbol(SYMBOL_PROG, var) ? printf("\nIDENT: %s is already present. - Update in progress...", var) : printf("\nIDENT: %s is new - Addition in progress...", var);
    SYMBOL_PROG = addASymbol(SYMBOL_PROG, var);
    printSymbol(SYMBOL_PROG);
  }
  else
    printf("MALLOC! ");
  return t;
}

/**
 * @brief   Cette fonction permet de créer une nouvelle AST à partir d'une variable.
 *          La variable doit être connu dans le programme.
 *
 * @param var la variable
 * @return AST l'AST créée
 */
AST newVariableAST(char *var)
{
  if (searchSymbol(SYMBOL_PROG, var) == 1)
  {
    AST t = (struct _tree *)malloc(sizeof(struct _tree));
    if (t != NULL)
    { /* malloc ok */
      t->taille++;
      t->var = var;
      t->left = NULL;
      t->right = NULL;
      t->ifThenElse = NULL;
    }
    else
      printf("MALLOC! ");
    return t;
  }
  else
  {
    printf("Error - no variable\n");
    exit(EXIT_FAILURE);
  }
}

/* delete an AST */
void freeAST(AST t)
{
  if (t != NULL)
  {
    free(t->var);
    freeAST(t->left);
    freeAST(t->right);
    freeAST(t->ifThenElse);
    free(t);
  }
}

/* infix print an AST*/
void printAST(AST t)
{
  if (t != NULL)
  {
    printf("[ ");

    if (t->left)
    {
      if (t->var)
        printf(":%s: ", t->var);

      if (t->aff)
        printf(":%c: ", t->aff);

      if (t->opeBool == 6)
        printf(":!: ");

      if (t->car && !t->right)
        printf(":%c: ", t->car);
    }

    printAST(t->left);
    /* check if node is car|val */

    if (t->left == NULL)
    {
      if (t->car)
        printf(":%c: ", t->car);

      if (t->val)
        switch (t->valCal)
        {
        case 1:
          printf(":%.0lf: ", t->val);
          break; // int
        case 2:
          printf(":%.2lf: ", t->val);
          break; // float
        case 3:
          printf(":%.2e: ", t->val);
          break; // float scientific
        case 4:
          printf(":NaN: ");
          break; // NaN
        default:
          printf("Error Float\n");
          break;
        }

      if (t->boolean)
        switch (t->boolean)
        {
        case 1:
          printf(":True: ");
          break;
        case 2:
          printf(":False: ");
          break;
        }

      if (t->var)
        printf(":%s: ", t->var);
    }
    else
    {
      if (t->car && t->right)
        printf(":%c: ", t->car);

      if (t->opeBool)
        switch (t->opeBool)
        {
        case 1:
          printf(":==: ");
          break;
        case 2:
          printf(":<=: ");
          break;
        case 3:
          printf(":>=: ");
          break;
        case 4:
          printf(":<: ");
          break;
        case 5:
          printf(":>: ");
          break;
        case 7:
          printf(":||: ");
          break;
        case 8:
          printf(":&&: ");
          break;
        }
    }

    printAST(t->right);

    if (t->car2)
      printf(":%c: ", t->car2);

    printAST(t->ifThenElse);
    printf("] ");
  }
}

/**
 * @brief Cette fonction permet un affichage de la sortie post fixe de l'AST
 *
 * @param t l'AST
 */
void codeAST(AST t)
{
  if (t != NULL)
  {
    codeAST(t->left);

    if (t->left == NULL)
    {
      if (t->val)
        switch (t->valCal)
        {
        case 1:
          printf("CsteNb %.0lf\n", t->val);
          break; // int
        case 2:
          printf("CsteNb %.2lf\n", t->val);
          break; // float
        case 3:
          printf("CsteNb %.2e\n", t->val);
          break; // float scientific
        case 4:
          printf("CsteNb NaN\n");
          break;
        }

      if (t->boolean)
        switch (t->boolean)
        {
        case 1:
          printf("CsteBo True\n");
          break;
        case 2:
          printf("CsteBo False\n");
          break;
        }
    }
    else if (t->right == NULL)
    {
      if (t->aff && t->var)
        printf("SetVar %s\n", t->var);

      if (t->opeBool)
        printf("Not\n");
      else if (!t->opeBool && !t->aff && !t->var)
        printf("NegNb\n");
    }
    else
    {
      if (t->right && t->ifThenElse)
        printf("ConJmp %d\n", t->right->taille += 1);

      if (t->right)
      {
        if (t->opeBool)
        {
          switch (t->opeBool)
          {
          case 7:
            printf("ConJmp 2\n");
            printf("CsteBo True\n");
            printf("Jump %d\n", t->right->taille);
            break;
          case 8:
            printf("ConJmp %d\n", t->right->taille += 1);
            break;
          }
        }
      }

      codeAST(t->right);

      if (t->car)
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
        }

      if (t->opeBool)
        switch (t->opeBool)
        {
        case 1:
          printf("Equals\n");
          break;
        case 2:
          printf("LoEqNb\n");
          break;
        case 3:
          printf("GrEqNb\n");
          break;
        case 4:
          printf("LoStNb\n");
          break;
        case 5:
          printf("GrStNb\n");
          break;
        }

      if (t->ifThenElse)
        printf("Jump %d\n", t->ifThenElse->taille);

      if (t->right)
      {
        if (t->opeBool)
        {
          switch (t->opeBool)
          {
          case 8:
            printf("Jump 1\n");
            printf("CsteBo False\n");
            break;
          }
        }
      }

      codeAST(t->ifThenElse);
    }

    if (t->var)
      printf("GetVar %s\n", t->var);
  }
}

/**
 * @brief Cette fonction permet d'ecrire la sortie post fixe d'un AST dans un fichier.
 *
 * @param t AST
 * @param filename nom du fichier qui contiendera la sortie post fixe de l'AST
 */
void writeCodeASTInFile(AST t, char const *filename)
{
  FILE *f = fopen(filename, "r+");
  if (f != NULL)
  {
    fseek(f, 0, SEEK_END);
    if (t != NULL)
    {
      writeCodeASTInFile(t->left, filename);
      if (t->left == NULL)
      {
        if (t->val)
        {
          fseek(f, 0, SEEK_END);
          switch (t->valCal)
          {
          case 1:
            fprintf(f, "CsteNb %.0lf\n", t->val);
            break; // int
          case 2:
            fprintf(f, "CsteNb %.2lf\n", t->val);
            break; // float
          case 3:
            fprintf(f, "CsteNb %.2e\n", t->val);
            break; // float scientific
          case 4:
            fprintf(f, "CsteNb NaN\n");
            break;
          }
        }

        if (t->boolean)
        {
          fseek(f, 0, SEEK_END);
          switch (t->boolean)
          {
          case 1:
            fprintf(f, "CsteBo True\n");
            break;
          case 2:
            fprintf(f, "CsteBo False\n");
            break;
          }
        }
      }
      else if (t->right == NULL)
      {
        fseek(f, 0, SEEK_END);
        if (t->aff && t->var)
          fprintf(f, "SetVar %s\n", t->var);

        fseek(f, 0, SEEK_END);

        if (t->opeBool)
          fprintf(f, "Not\n");

        else if (!t->opeBool && !t->aff && !t->var)
          fprintf(f, "NegNb\n");
      }
      else
      {
        if (t->right && t->ifThenElse)
        {
          fseek(f, 0, SEEK_END);
          fprintf(f, "ConJmp %d\n", t->right->taille += 1);
        }

        if (t->right)
        {
          if (t->opeBool)
          {
            switch (t->opeBool)
            {
            case 7:
              fseek(f, 0, SEEK_END);
              fprintf(f, "ConJmp 2\n");
              fprintf(f, "CsteBo True\n");
              fprintf(f, "Jump %d\n", t->right->taille);
              break;
            case 8:
              fseek(f, 0, SEEK_END);
              fprintf(f, "ConJmp %d\n", t->right->taille += 1);
              break;
            }
          }
        }

        fseek(f, 0, SEEK_END);
        writeCodeASTInFile(t->right, filename);

        if (t->car)
        {
          fseek(f, 0, SEEK_END);
          switch (t->car)
          {
          case '+':
            fprintf(f, "AddiNb\n");
            break;
          case '-':
            fprintf(f, "SubiNb\n");
            break;
          case '%':
            fprintf(f, "ModuNb\n");
            break;
          case '*':
            fprintf(f, "MultNb\n");
            break;
          }
        }

        if (t->opeBool)
        {
          fseek(f, 0, SEEK_END);
          switch (t->opeBool)
          {
          case 1:
            fprintf(f, "Equals\n");
            break;
          case 2:
            fprintf(f, "LoEqNb\n");
            break;
          case 3:
            fprintf(f, "GrEqNb\n");
            break;
          case 4:
            fprintf(f, "LoStNb\n");
            break;
          case 5:
            fprintf(f, "GrStNb\n");
            break;
          }
        }

        if (t->ifThenElse)
        {
          fseek(f, 0, SEEK_END);
          fprintf(f, "Jump %d\n", t->ifThenElse->taille);
        }

        if (t->right)
        {
          if (t->opeBool)
          {
            switch (t->opeBool)
            {
            case 8:
              fseek(f, 0, SEEK_END);
              fprintf(f, "Jump 1\n");
              fprintf(f, "CsteBo False\n");
              break;
            }
          }
        }

        fseek(f, 0, SEEK_END);
        writeCodeASTInFile(t->ifThenElse, filename);
      }

      fseek(f, 0, SEEK_END);
      if (t->var)
        fprintf(f, "GetVar %s\n", t->var);

      fclose(f);
    }
  }
  else
  {
    printf("Erreur lors de lecture / création du ficheir\n");
    exit(1);
  }
}

/*-----------------------------------------------.
| functions for manipulating the list of symbols |                 |
`-----------------------------------------------*/

/**
 * @brief   Cette fonction permet d'ajouter un symbole au symbole déja passé dans le programme.
 *
 * @param sym la liste des symboles du programme.
 * @param var le symbole à ajouter dans ce premier cas c'est une variable.
 * @return symboles le résultat après ajout du symbole.
 */
symboles addASymbol(symboles sym, char *var)
{
  if (searchSymbol(sym, var) == 1)
    return sym;
  else
  {
    symbole newSymbol = (struct _symbole *)malloc(sizeof(struct _symbole));
    if (newSymbol != NULL)
    {
      newSymbol->var = var;
      newSymbol->suivant = sym;
    }
    else
    {
      printf("Error - addASymbol\n");
      exit(EXIT_FAILURE);
    }
    return newSymbol;
  }
}

/**
 * @brief   Cette fonction permet de rechercher un symbole dans la liste des symbole du programme.
 *          Permet de savoir si une variable par exemple est déja passé.
 *
 * @param sym liste des symboles.
 * @param var le symbole à rechercher, dans ce premier cas c'est une variable.
 * @return int 1 si le symbole appartient, 0 sinon.
 */
int searchSymbol(symboles sym, char *var)
{
  while (sym != NULL)
  {
    if (strcmp(sym->var, var) == 0)
      return 1;
    sym = sym->suivant;
  }
  return 0;
}

/**
 * @brief   Cette fonction permet de libérer la mémoire allouée par les symboles du programe.
 *
 * @param sym les symboles du programme.
 */
void freeSymbol(symboles sym)
{
  if (sym != NULL)
  {
    symbole symboleSuivant = NULL;
    while (sym)
    {
      symboleSuivant = sym->suivant;
      free(sym->var);
      sym = symboleSuivant;
    }
  }
}

/**
 * @brief   Cette fonction permet d'afficher tous les symboles du programme.
 *
 * @param sym les symboles du programme.
 */
void printSymbol(symboles sym)
{
  printf("\nIDENT = |");
  while (sym != NULL)
  {
    printf(" %s |", sym->var);
    sym = sym->suivant;
  }
  printf("\n\n");
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
commande_ast newCommandeExpAST(AST expression, char pVirg)
{
  commande_ast c = (struct _commande_ast *)malloc(sizeof(struct _commande_ast));
  if (c != NULL)
  { /* malloc ok */
    c->expression = expression;
    c->taille += c->expression->taille;
    c->pVirg = pVirg;
    c->left = NULL;
    c->right = NULL;
    c->motCle1 = NULL;
    c->motCle2 = NULL;
  }
  else
    printf("MALLOC! ");
  return c;
}

/**
 * @brief   Cette fonction permet de créer une commande à partir d'un point virgule ';'
 *
 * @param pVirg le point virgule de la fin de l'expression
 * @return commande_ast la commande créee.
 */
commande_ast newCommandePVirgAST(char pVirg)
{
  commande_ast c = (struct _commande_ast *)malloc(sizeof(struct _commande_ast));
  if (c != NULL)
  { /* malloc ok */
    c->pVirg = pVirg;
    c->expression = newBinaryAST(pVirg, NULL, NULL);
    c->taille += c->expression->taille;
    c->left = NULL;
    c->right = NULL;
    c->motCle1 = NULL;
    c->motCle2 = NULL;
  }
  else
    printf("MALLOC! ");
  return c;
}

/**
 * @brief   Cette fonction permet de copier les suivant du programme de la commande dans les next de la commandes.
 *
 * @param prog le programme de la commande entre { }
 * @return commande_ast la commande finale.
 */
commande_ast copyList(programme_ast prog)
{
  if (prog == NULL)
  {
    return NULL;
  }
  else
  {
    commande_ast commande = (struct _commande_ast *)malloc(sizeof(struct _commande_ast));
    if (commande != NULL)
    { /* malloc ok */
      commande = prog;
      commande->next = copyList(prog->suivant);
    }
    else
      printf("MALLOC! ");
    return commande;
  }
}

/**
 * @brief   Cette fonction permet de créer une ommande à partir d'une séquence de commandes, c'est a dire à partir d'un programme.
 *
 * @param prog la séquence de commandes
 * @return commande_ast la commande en sortie.
 */
commande_ast newCommandeProg(programme_ast prog)
{
  commande_ast commande = (struct _commande_ast *)malloc(sizeof(struct _commande_ast));
  if (commande != NULL)
  { /* malloc ok */
    commande = copyList(prog);
    while (prog)
    {
      commande->taille += prog->expression->taille;
      prog = prog->suivant;
    }
  }
  else
    printf("MALLOC! ");
  return commande;
}

/**
 * @brief   Cette fonction permet de créer une commande a partir de deux mots clé If et Else une expression qui est un AST et deux commandes pour le then et le else.
 *
 * @param iF mot clé If.
 * @param eLse mot clé Else.
 * @param son l'expression - AST.
 * @param tHen la commande si True.
 * @param elseCom la commande si False.
 * @return commande_ast
 */
commande_ast newCommandeIfElseAST(char *iF, char *eLse, AST son, commande_ast tHen, commande_ast elseCom)
{
  commande_ast c = (struct _commande_ast *)malloc(sizeof(struct _commande_ast));
  if (c != NULL)
  { /* malloc ok */
    c->motCle1 = strdup(iF);
    c->motCle2 = strdup(eLse);
    c->expression = son;
    c->left = tHen;
    c->right = elseCom;
    c->taille += c->expression->taille;
  }
  else
    printf("MALLOC! ");
  return c;
}

/**
 * @brief   Cette fonction permet de créer une nouvelle commande à partir de deux mot clé do et while ainsi que la commande de do et l'expression de while.
 *
 * @param dO mot clé do
 * @param wHile mot clé while
 * @param doCom commande de do
 * @param whileSon expression de while
 * @return commande_ast
 */
commande_ast newCommandeDoWhileAST(char *dO, char *wHile, commande_ast doCom, AST whileSon)
{
  commande_ast c = (struct _commande_ast *)malloc(sizeof(struct _commande_ast));
  if (c != NULL)
  { /* malloc ok */
    c->motCle1 = strdup(dO);
    c->motCle2 = strdup(wHile);
    c->expression = whileSon;
    c->left = doCom;
    c->taille += c->expression->taille + c->left->expression->taille;
  }
  else
    printf("MALLOC! ");
  return c;
}

/**
 * @brief   Cette fonction permet de créer une commande à partir d'un mot clé while, de l'expression du while ainsi que la commande.
 *
 * @param wHile le mot clé while
 * @param son l'expression de while qui est un AST
 * @param com la commande à exécuté dans le while
 * @return commande_ast
 */
commande_ast newCommandeWhileAST(char *wHile, AST son, commande_ast com)
{
  commande_ast c = (struct _commande_ast *)malloc(sizeof(struct _commande_ast));
  if (c != NULL)
  { /* malloc ok */
    c->motCle1 = strdup(wHile);
    c->expression = son;
    c->left = com;
    c->taille += c->expression->taille + c->left->expression->taille;
  }
  else
    printf("MALLOC! ");
  return c;
}

/**
 * @brief   Cette fonction permet de libérer la mémoire allouée par une commande
 *
 * @param c La commande.
 */
void freeCommande(commande_ast c)
{
  if (c != NULL)
  {
    freeAST(c->expression);
    freeCommande(c->left);
    freeCommande(c->right);
    freeCommande(c->next);
    free(c->motCle1);
    free(c->motCle2);
    free(c);
  }
}

/**
 * @brief   Cette fonction permet d'afficher une commande.
 *          Une commande est afficher une deux '|' ainsi:  |commande |
 *
 * @param c la commande à afficher.
 */
void printCommande(commande_ast c)
{
  if (c != NULL)
  {
    printf("| ");

    if (c->expression)
    {
      if (c->motCle1)
        printf(":%s: ", c->motCle1);

      if (c->motCle1)
      {
        if (strcmp(c->motCle1, "do") != 0)
          printAST(c->expression);
      }
      else
        printAST(c->expression);

      if (c->pVirg)
        printf(":%c: ", c->pVirg);
    }
    else
      printf(":%c: ", c->pVirg);

    printCommande(c->left);

    if (c->motCle2)
      printf(":%s: ", c->motCle2);

    printCommande(c->right);
    if (c->motCle1)
      if (strcmp(c->motCle1, "do") == 0)
        printAST(c->expression);

    printf("| ");

    if (c->next)
    {
      printf("\n\t");
      printCommande(c->next);
    }
  }
}

/**
 * @brief Cette fonction permet un affichage de la sortie post fixe de la commande.
 *
 * @param c la commande
 */
void codeCommande(commande_ast c)
{
  if (c != NULL)
  {
    if (c->expression)
      if (c->motCle1)
      {
        if (strcmp(c->motCle1, "do") != 0)
          codeAST(c->expression);
      }
      else
        codeAST(c->expression);

    if (c->left)
    {
      if (c->motCle1)
      {
        if (strcmp(c->motCle1, "do") != 0)
          printf("CondJump %d\n", c->left->taille += 1);
      }
      else
        printf("CondJump %d\n", c->left->taille += 1);

      codeCommande(c->left);
      if (c->right)
        printf("Jump %d\n", c->taille);

      if (strcmp(c->motCle1, "while") == 0)
        printf("Jump -%d\n", c->left->taille + 1);
    }

    codeCommande(c->right);

    if (c->motCle1)
      if (strcmp(c->motCle1, "do") == 0)
      {
        codeAST(c->expression);
        printf("CondJump -%d\n", c->left->taille);
      }

    if (c->next)
      codeCommande(c->next);
  }
}

/* write a post-fix command in a file*/
/**
 * @brief Cette fonction permet d'ecrire la sortie post fixe d'une commande dans un fichier.
 *
 * @param c la commmande
 * @param filename nom du fichier qui contiendera la sortie post fixe de l'AST
 */
void writeCodeCommandeInFile(commande_ast c, char const *filename)
{
  FILE *f = fopen(filename, "r+");
  if (f != NULL)
  {
    fseek(f, 0, SEEK_END);
    if (c != NULL)
    {
      if (c->expression)
      {
        if (c->motCle1)
        {
          if (strcmp(c->motCle1, "do") != 0)
          {
            fseek(f, 0, SEEK_END);
            writeCodeASTInFile(c->expression, filename);
          }
        }
        else
        {
          fseek(f, 0, SEEK_END);
          writeCodeASTInFile(c->expression, filename);
        }
      }

      if (c->left)
      {
        if (c->motCle1)
        {
          if (strcmp(c->motCle1, "do") != 0)
          {
            fseek(f, 0, SEEK_END);
            fprintf(f, "CondJump %d\n", c->left->taille += 1);
          }
        }
        else
        {
          fseek(f, 0, SEEK_END);
          fprintf(f, "CondJump %d\n", c->left->taille += 1);
        }

        fseek(f, 0, SEEK_END);
        writeCodeCommandeInFile(c->left, filename);

        if (c->right)
        {
          fseek(f, 0, SEEK_END);
          fprintf(f, "Jump %d\n", c->taille);
        }

        if (strcmp(c->motCle1, "while") == 0)
        {
          fseek(f, 0, SEEK_END);
          fprintf(f, "Jump -%d\n", c->left->taille + 1);
        }
      }

      fseek(f, 0, SEEK_END);
      writeCodeCommandeInFile(c->right, filename);

      if (c->motCle1)
        if (strcmp(c->motCle1, "do") == 0)
        {
          fseek(f, 0, SEEK_END);
          writeCodeASTInFile(c->expression, filename);
          fseek(f, 0, SEEK_END);
          fprintf(f, "CondJump -%d\n", c->left->taille);
        }

      if (c->next)
      {
        fseek(f, 0, SEEK_END);
        writeCodeCommandeInFile(c->next, filename);
      }
      fclose(f);
    }
  }
  else
  {
    printf("Erreur lors de lecture / création du ficheir\n");
    exit(1);
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
programme_ast newProgramme()
{
  programme_ast p = NULL;
  return p;
}

/**
 * @brief   Cette fonction permet d'ajouter une commande à la fin d'un programme.
 *
 * @param prog Le programme auquel on ajoute la commande.
 * @param newCommande La commande a ajotuer
 * @return programme_ast le prgramme après ajout de la commande
 */
programme_ast addComToProg(programme_ast prog, commande_ast newCommande)
{
  if (newCommande)
  {
    newCommande->suivant = NULL;

    if (!prog)
      return newCommande;
    else
    {
      newCommande->suivant = prog;
      return newCommande;
    }
  }
  else
  {
    printf("Error - addComToProg\n");
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief   Cette fonction permet de libérer la mémoire alloué par un programme.
 *
 * @param prog Le programme.
 */
void freeProg(programme_ast prog)
{
  if (prog != NULL)
  {

    commande_ast commandeSuivante = NULL;
    while (prog)
    {
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
void printProg(programme_ast prog)
{
  if (prog)
  {
    printf("Program:\n");
    commande_ast tmpCommande = prog;
    while (tmpCommande)
    {
      if (tmpCommande->next)
        printf("{ \n\t");
      printCommande(tmpCommande);
      if (tmpCommande->next)
        printf("\n}");
      printf("\n");
      tmpCommande = tmpCommande->suivant;
    }
  }
  else
  {
    printf("Error - printProg - Liste vide !\n");
    exit(EXIT_FAILURE);
  }
}

/* print post-fix a command*/
void codeProg(programme_ast prog)
{
  if (prog)
  {
    commande_ast tmpCommande = prog;
    while (tmpCommande)
    {
      codeCommande(tmpCommande);
      tmpCommande = tmpCommande->suivant;
    }
  }
  else
  {
    printf("Error - codeProg - Liste vide !\n");
    exit(EXIT_FAILURE);
  }
}

/* write a post-fix command in a file*/
void writeCodeProgInFile(programme_ast prog, char const *filename)
{
  if (prog)
  {
    commande_ast tmpCommande = prog;
    while (tmpCommande)
    {
      writeCodeCommandeInFile(tmpCommande, filename);
      tmpCommande = tmpCommande->suivant;
    }
  }
  else
  {
    printf("Error - writeCodeProgInFile - Liste vide !\n");
    exit(EXIT_FAILURE);
  }
}
