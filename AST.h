#ifndef _AST_H_
#define _AST_H_

/* unary-and-binary tree structure */
struct _tree
{
  int taille;                   /* Taille pour calcul des offset */
  char car;                     /* char for arithmetic operation */
  char car2;                    /* second char for if then else ternaire */
  double val;                   /* double for value */
  int valCal;                   /* int to know the double type (float | int | floating scientific) */
  int boolean;                  /* True 1 | False 2 */
  int opeBool;                  /* int for boolean operation */
  char *var;                    /* la variable ou l'identifiant */
  char aff;                     /* char '=' de l'affectation */
  struct _tree *left;           /* used for unary node but NULL if leaf */
  struct _tree *right;          /* NULL if unary node or leaf*/
  struct _tree *ifThenElse;     /* NULL if not if then else expresion */
  struct _arguments *arguments; /* arguments */
};

typedef struct _tree *AST;

/* Strucutre of a symbol in the first case it is a variable. */
struct _symbole
{
  char *var;
  struct _symbole *suivant;
};

typedef struct _symbole *symbole;

/* List of symbols */
typedef struct _symbole *symboles;

/* Structure of a command */
struct _commande_ast
{
  int taille;
  AST expression;
  AST expression2; /* deuxième expression for */
  AST expression3; /* troisième expression for */
  char pVirg;
  char *motCle1;                 /* Mot clé 1 pour les intruction exempl: IF, Else... */
  char *motCle2;                 /* Mot clé 1 pour les intruction exempl: IF, Else... */
  char *nameFun;                 /* Name of the function */
  struct _commande_ast *left;    /* used for unary node but NULL if leaf */
  struct _commande_ast *right;   /* NULL if unary node or leaf*/
  struct _commande_ast *suivant; /* Un programme est une liste de commande */
  struct _commande_ast *next;    /* Une commande peut être un programme */
  struct _decl_args *decl_args;  /* decl_args */
};

typedef struct _commande_ast *commande_ast;

/* Structure of a program that is a list of commands */
typedef struct _commande_ast *programme_ast;

/* Structure of a decl_args */
struct _decl_args
{
  char *ident;                /* l'identifiant */
  struct _decl_args *suivant; /* La déclaration d'argument peut être une liste d'arguments */
};

typedef struct _decl_args *decl_args;

/* Structure of a arguments */
struct _arguments
{
  AST expression;             /* Une expression */
  struct _arguments *suivant; /* Gérer une liste d'arguments */
};

typedef struct _arguments *arguments;

/*-----------------------------------------------.
|                AST - expression                |
`-----------------------------------------------*/
/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right);

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son);

/* create an AST leaf from a value */
AST newLeafAST(double val, int valCal);

/* create an AST leaf from a boolean */
AST newBooleanAST(int boolean);

/* create an AST from a boolean operation and two AST sons */
AST newOpeBoolAST(int opeBool, AST left, AST right);

/* create an AST from a if then else operation and 3 AST sons */
AST newIfThenElseAST(char car1, char car2, AST ifSon, AST thenSon, AST elseSon);

/* create an AST leaf from an assignment */
AST newAffAST(char *var, char aff, AST son);

/* create an AST leaf from a variable */
AST newVariableAST(char *var);

/* create an AST from an IDENT and arguments */
AST newIdentArgAST(char *ident, arguments args);

/* delete an AST */
void freeAST(AST t);

/* print an AST*/
void printAST(AST t);

/* print post-fix an AST*/
void codeAST(AST t);

/* write a post-fix AST in a file*/
void writeCodeASTInFile(AST t, char const *filename);

/*-----------------------------------------------.
| functions for manipulating the list of symbols |                 |
`-----------------------------------------------*/

/* Add a symbol to the list of symbols */
symboles addASymbol(symboles sym, char *var);

/* Search for a symbol in the list of symbols  */
int searchSymbol(symboles sym, char *var);

/* Delete the list of symbols */
void freeSymbol(symboles sym);

/* Print the list of symbols */
void printSymbol(symboles sym);

/*-----------------------------------------------.
|                AST - commande                  |
`-----------------------------------------------*/

/* Create a command from an expression and a semicolon */
commande_ast newCommandeExpAST(AST expression, char aff_pVirg);

/* Create a command from a semicolon */
commande_ast newCommandePVirgAST(char aff_pVirg);

/* Copy a list into another list  */
commande_ast copyList(programme_ast prog);

/* Create a command from a programme */
commande_ast newCommandeProg(programme_ast prog);

/* Create a command from a if else */
commande_ast newCommandeIfElseAST(char *iF, char *eLse, AST son, commande_ast tHen, commande_ast elseCom);

/* Create a command from a do while */
commande_ast newCommandeDoWhileAST(char *dO, char *wHile, commande_ast doCom, AST whileSon);

/* Create a command from a while */
commande_ast newCommandeWhileAST(char *wHile, AST son, commande_ast com);

/* Create a command from a for */
commande_ast newCommandeForAST(char *fOr, AST son1, AST son2, AST son3, commande_ast com);

/* Create a command from a for */
commande_ast newCommandeFunAST(char *fUn, char *ident, decl_args dArg, programme_ast prog);

/* Create a command from a for */
commande_ast newCommandeRetAST(char *rEturn, AST exp);

/* delete a command */
void freeCommande(commande_ast c);

/* print a command*/
void printCommande(commande_ast c);

/* print post-fix a command*/
void codeCommande(commande_ast c);

/* write a post-fix command in a file*/
void writeCodeCommandeInFile(commande_ast c, char const *filename);

/*-----------------------------------------------.
|                   Programme                    |
`-----------------------------------------------*/

/* Initialize a program */
programme_ast newProgramme();

/* Add a command at the end of a program */
programme_ast addComToProg(programme_ast prog, commande_ast newCommande);

/* delete a command */
void freeProg(programme_ast prog);

/* print a program*/
void printProg(programme_ast prog);

/* print post-fix a command*/
void codeProg(programme_ast prog);

/* write a post-fix command in a file*/
void writeCodeProgInFile(programme_ast prog, char const *filename);
/*-----------------------------------------------.
|                   decl_args                    |
`-----------------------------------------------*/
/* Create a command from empty */
decl_args newDeclArgEmpty();

/* Create a command from an IDENT */
decl_args newDeclArgIdent(char *ident);

/* Create a command from an IDENT and decl_args */
decl_args newDeclArgIdentDA(char *ident, decl_args dArg);

/* delete a decl_args */
void freeDeclArg(decl_args dArg);

/* print a decl_args */
void printDeclArg(decl_args dArg);

/*-----------------------------------------------.
|                    arguments                   |
`-----------------------------------------------*/
/* Create a command from empty */
arguments newArgumentsEmpty();

/* Create a command from an expression */
arguments newArgumentsExp(AST expression);

/* Create a command from an expression and arguments */
arguments newArgumentsExpArg(AST expression, arguments args);

/* delete a arguments */
void freeArguments(arguments args);

/* print a list of arguments */
void printArguments(arguments args);

#endif // !_AST_H_
