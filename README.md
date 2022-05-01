# Compilateur JavaScript - Fragement c0.2
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
Tous les tests du fragement c0.0 et c0.1 plus ce qui suit:

* On peut utiliser True et False comme expressions constantes + ajout de opérateur binaire (_ == _) qui prend deux nombres et produit un boolèen + la négation (! _) + les opérateur <  >  <=  => + Respect des des priorités et de l'associativité:

!False == (12>=12-12.4);
lex::OPERATIONBOOL !
lex::BOOLEAN False
lex::OPERATIONBOOL ==
lex::char (
lex::NOMBRE 12
lex::OPERATIONBOOL >=
lex::NOMBRE 12
lex::char -
lex::NOMBRE 12.4
lex::char )

Parsing:: syntax OK

Root symbol:: 

/*----------.
|    AST    |
`----------*/
[ [ [ :False: ] :!: ] :==: [ [ :12.00: ] :>=: [ [ :12.00: ] :-: [ :12.40: ] ] ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteBo False
Not
CsteNb 12.00
CsteNb 12.00
CsteNb 12.40
SubiNb
GrEqNb
Equals
Halt


Voici le résultat dans la machine JS:
...
...
...
PC : 4
Pile : [True ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 




True == !False;
lex::BOOLEAN True
lex::OPERATIONBOOL ==
lex::OPERATIONBOOL !
lex::BOOLEAN False

Parsing:: syntax OK

Root symbol:: 

/*----------.
|    AST    |
`----------*/
[ [ :True: ] :==: [ [ :False: ] :!: ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteBo True
CsteBo False
Not
Equals
Halt

Voici le résultat dans la machine JS:
...
...
...
PC : 8
Pile : [True ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 


Des tests ont bien sûr été effectué via fichier js en arguments.