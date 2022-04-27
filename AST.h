#ifndef _AST_H_
#define _AST_H_

/* unary-and-binary tree structure */
struct _tree {
  char car;                    	/* char for arithmetic operation */
  int opeBool;                    	/* string for boolean operation */
  double val;			/* int  for value */
  int boolean;
  struct _tree* left;    	/* used for unary node but NULL if leaf */
  struct _tree* right;   	/* NULL if unary node or leaf*/
};

typedef struct _tree* AST;

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right);

/* create an AST from a boolean operation and two AST sons */
AST newOpeBoolAST(int opeBool, AST left, AST right);

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son);

/* create an AST leaf from a value */
AST newLeafAST(double val);

/* create an AST leaf from a boolean */
AST newBooleanAST(int boolean);

/* delete an AST */
void freeAST(AST t);

/* print an AST*/
void printAST(AST t);

/* print post-fix an AST*/
void code (AST t);

/* write a post-fix AST in a file*/
void echoCodeInFile (AST t, char const *filename);


#endif // !_AST_H_
