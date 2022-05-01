# Compilateur JavaScript - Fragement c1.3
Compilateur JavaScript est un projet qui consiste à compiler quelques fragments de javascript en un langage d'assemblage addhoc.

# Auteur
Mohand Lounis BENSEKHRI     11710457
Salem BOUDEBABA             12017165
		
Master 1 informatique 
Université Sorbonne Paris Nord

# Date
Jeudi 04 mai 2022

# Prérequis
    * gcc
    * make
    * bison
    * flex

# Commandes d'installation des prérequis
```bash 
sudo apt update
sudo apt install build-essential
sudo apt-get install flex bison
```

# Commande de compilation
Vous pouvez compiler le projet avec la commande :
```bash 
make
```

ou bien séparément avec les commandes: 
```bash 
bison -d parseur.y
flex lexeur.l
gcc -o main main.c parseur.tab.c lex.yy.c
```

# Commande d'exécution
./main
./main fichier.js

# Explications
Vous pouvez exécuter le projet sur un fichier js existant directement, et celui-ci vous diras si les instructions contenues dans le fichier sont correctes, ou bien sans fichier en argument, et cela lancera tout simplement la main en console.

- Après exécution de ces commandes, un fichier jsm contenant le code assembleur généré est créé si l'exécution est faite avec un fichier js en argument, sinon des erreurs s'afficheront si le fichier n'est pas un js ou bien qu'il n'existe pas.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement c0, c1.0, c1.1 et c1.2 plus ce qui suit:

* Les booléens "or" et "and" => '||' et '&&' :
Test N°01 :

True||(!False&&True);
lex::BOOLEAN True
lex::OPERATIONBOOL ||
lex::char (
lex::OPERATIONBOOL !
lex::BOOLEAN False
lex::OPERATIONBOOL &&
lex::BOOLEAN True
lex::char )

Parsing:: syntax OK

Root symbol:: 

/*----------.
|    AST    |
`----------*/
[ [ :True: ] :||: [ [ [ :False: ] :!: ] :&&: [ :True: ] ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteBo True
ConJmp 2
CsteBo True
Jump 4
CsteBo False
Not
ConJmp 2
CsteBo True
Jump 1
CsteBo False
Halt


Sortie de la machine JS avec ce code assembleur:
...
...
...
PC : 10
Pile : [True ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 


Test N°02 :

Exécution avec le ficheir toto.js qui contient : True || (!False && True);
lex::BOOLEAN True
lex::OPERATIONBOOL ||
lex::char (
lex::OPERATIONBOOL !
lex::BOOLEAN False
lex::OPERATIONBOOL &&
lex::BOOLEAN True
lex::char )

Parsing:: syntax OK

Root symbol:: 

/*-------------------------------------.
|    Writing the file toto.jsm    |
`-------------------------------------*/

/*----------.
|    AST    |
`----------*/
[ [ :True: ] :||: [ [ [ :False: ] :!: ] :&&: [ :True: ] ] ]



- Contenue du fichier toto.jsm :
--------------------------------

CsteBo True
ConJmp 2
CsteBo True
Jump 4
CsteBo False
Not
ConJmp 2
CsteBo True
Jump 1
CsteBo False
Halt







Test N°03 :

True&&False?False:True&&False;
lex::BOOLEAN True
lex::OPERATIONBOOL &&
lex::BOOLEAN False
lex::char ?
lex::BOOLEAN False
lex::char :
lex::BOOLEAN True
lex::OPERATIONBOOL &&
lex::BOOLEAN False
newIfThenElseAST

Parsing:: syntax OK

Root symbol:: ?

/*----------.
|    AST    |
`----------*/
[ [ [ :True: ] :&&: [ :False: ] ] :?: [ :False: ] ::: [ [ :True: ] :&&: [ :False: ] ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteBo True
ConJmp 2
CsteBo False
Jump 1
CsteBo False
ConJmp 2
CsteBo False
Jump 3
CsteBo True
ConJmp 2
CsteBo False
Jump 1
CsteBo False
Halt


Résultat de la sortie de la machine JS:
...
...
...
PC : 13
Pile : [False ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 