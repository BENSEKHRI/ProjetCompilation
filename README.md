# Compilateur JavaScript - Fragement c1.0
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
Tous les tests du fragement c0.0, c0.1 et c0.2 plus ce qui suit:

* Les nombres peuvent être écrits 1.215e25 ou .485e-42 ou 485e-42. Nous ajoutons également la constante NaN :

1.215e25+.485e-42*12.12-NaN==False==!True;
lex::NOMBRE 1.215e25
lex::char +
lex::NOMBRE .485e-42
lex::char *
lex::NOMBRE 12.12
lex::char -
lex::NOMBRE NaN
lex::OPERATIONBOOL ==
lex::BOOLEAN False
lex::OPERATIONBOOL ==
lex::OPERATIONBOOL !
lex::BOOLEAN True

Parsing:: syntax OK

Root symbol:: 

/*----------.
|    AST    |
`----------*/
[ [ [ [ [ :1.21e+25: ] :+: [ [ :4.85e-43: ] :*: [ :12.12: ] ] ] :-: [ :NaN: ] ] :==: [ :False: ] ] :==: [ [ :True: ] :!: ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 1.21e+25
CsteNb 4.85e-43
CsteNb 12.12
MultNb
AddiNb
CsteNb NaN
SubiNb
CsteBo False
Equals
CsteBo True
Not
Equals
Halt


Des tests ont bien sûr été effectué via fichier js en arguments.
