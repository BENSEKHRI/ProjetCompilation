#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include <string.h> /* Manipulation de chaine de caractères */

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t = (struct _tree *)malloc(sizeof(struct _tree));
  if (t != NULL)
  { /* malloc ok */
    // Condition d'ajout de taille pour ne cas - exp  float négatif.
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
  printf("newIfThenElseAST\n");
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

/* delete an AST */
void freeAST(AST t)
{
  if (t != NULL)
  {
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
    printAST(t->left);
    /* check if node is car|val */
    if (t->left == NULL)
    {
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
    }
    else
    {
      if (t->car)
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
        case 6:
          printf(":!: ");
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
void code(AST t)
{
  if (t != NULL)
  {
    code(t->left);
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
      if (t->opeBool)
        printf("Not\n");
      else
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

      code(t->right);

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

      code(t->ifThenElse);
    }
  }
}

/**
 * @brief Cette fonction permet d'ecrire la sortie post fixe d'un AST dans un fichier.
 *
 * @param t AST
 * @param filename nom du fichier qui contiendera la sortie post fixe de l'AST
 */
void echoCodeInFile(AST t, char const *filename)
{
  FILE *f = fopen(filename, "r+");
  if (f != NULL)
  {
    fseek(f, 0, SEEK_END);
    if (t != NULL)
    {
      echoCodeInFile(t->left, filename);
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
        if (t->opeBool)
          fprintf(f, "Not\n");
        else
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
              fprintf(f,"ConJmp %d\n", t->right->taille += 1);
              break;
            }
          }
        }

        fseek(f, 0, SEEK_END);
        echoCodeInFile(t->right, filename);

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
        echoCodeInFile(t->ifThenElse, filename);
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
