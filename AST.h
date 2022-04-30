#ifndef _AST_H_
#define _AST_H_


/* unary-and-binary tree structure */
struct _tree {
  int taille;
  char car;                   /* char for arithmetic operation */
  char car2;                  /* second char for if then else ternaire */
  int opeBool;                /* string for boolean operation */
  double val;			            /* double for value */
  int valCal;			            /* int to know the double type (float | int | floating scientific) */
  int boolean;                /* True 1 | False 2 */
  struct _tree* left;    	    /* used for unary node but NULL if leaf */
  struct _tree* right;   	    /* NULL if unary node or leaf*/
  struct _tree* ifThenElse;   /* NULL if not if then else expresion */
};

typedef struct _tree* AST;


/* Structure of a command */
struct _commande_ast {
  AST expression;
  char* var; 
  char aff;
  char pVirg;
  struct _commande_ast *suivant;
};

typedef struct _commande_ast* commande_ast;


/* Structure of a program that is a list of commands */
typedef struct _commande_ast* programme_ast;



/*-----------------------------------------------.
|                AST - expression                |
`-----------------------------------------------*/

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right);

/* create an AST from a boolean operation and two AST sons */
AST newOpeBoolAST(int opeBool, AST left, AST right);

/* create an AST from a if then else operation and 3 AST sons */
AST newIfThenElseAST(char car1, char car2, AST ifSon, AST thenSon, AST elseSon);

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son);

/* create an AST leaf from a value */
AST newLeafAST(double val, int valCal);

/* create an AST leaf from a boolean */
AST newBooleanAST(int boolean);

/* delete an AST */
void freeAST(AST t);

/* print an AST*/
void printAST(AST t);



/*-----------------------------------------------.
|                AST - commande                  |
`-----------------------------------------------*/

/* Create a command from an expression and a semicolon */
commande_ast newCommanedeExpAST(AST expression, char aff_pVirg);

/* Creating a command from an assignment */
commande_ast newCommanedeAffAST(AST expression, char* var, char aff, char pVirg);

/* Create a command from a semicolon */
commande_ast newCommanedePVirgAST(char aff_pVirg);

/* delete a command */
void freeCommande(commande_ast c);

/* print a program*/
void printCommande(commande_ast c);



/*-----------------------------------------------.
|                   Programme                    |                  
`-----------------------------------------------*/

/* Initialize a program */
programme_ast newProgramme ();

/* Add a command at the end of a program */
programme_ast addComToProg (programme_ast prog, commande_ast newCommande);

/* delete a command */
void freeProg(programme_ast prog);

/* print a program*/
void printProg(programme_ast prog);

#endif // !_AST_H_
