#ifndef _AST_H_
#define _AST_H_

/* unary-and-binary tree structure */
struct _tree {
  int taille;             /* Taille pour calcul des offset */
  char car;               /* char for arithmetic operation */
  char car2;              /* second char for if then else ternaire */
  double val;			        /* int for value */
  int valCal;			        /* int for type value */
  int boolean;            /* int for boolean */
  int opeBool;            /* string for boolean operation */
  struct _tree* left;    	/* used for unary node but NULL if leaf */
  struct _tree* right;   	/* NULL if unary node or leaf*/
  struct _tree* ifThenElse;   	/* NULL if not if then else expresion */
};

typedef struct _tree* AST;

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

/* delete an AST */
void freeAST(AST t);

/* print an AST*/
void printAST(AST t);

/* print post-fix an AST*/
void code (AST t);

/* write a post-fix AST in a file*/
void echoCodeInFile (AST t, char const *filename);


#endif // !_AST_H_
