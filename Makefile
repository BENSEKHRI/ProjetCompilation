LEX = flex
YACC = bison -d
CC = gcc

main: main.c parseur.tab.c lex.yy.c 
		$(CC) -o main parseur.tab.c lex.yy.c main.c
parseur.tab.c: parseur.y
		$(YACC) parseur.y
lex.yy.c: lexeur.l
		$(LEX) lexeur.l