# Compilateur JavaScript - Fragement c1.2
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
Tous les tests du fragement c0.0, c0.1, c0.2, c1.0 et c1.1 plus ce qui suit:

* L'opérateur ternaire _ ? _ : _ qui évalue le premier, si c'est un booléen l'opérateur exécute le code du deuxième argument, sinon il exécute le code du troisième argument : c'est comme un if_then_else mais à l'intérieur des expressions. Instructions de montage supplémentaires autorisées: Jump, ConJmp.


True?12+5*2:!False;
lex::BOOLEAN True
lex::char ?
lex::NOMBRE 12
lex::char +
lex::NOMBRE 5
lex::char *
lex::NOMBRE 2
lex::char :
lex::OPERATIONBOOL !
lex::BOOLEAN False
newIfThenElseAST

Parsing:: syntax OK

Root symbol:: ?

/*----------.
|    AST    |
`----------*/
[ [ :True: ] :?: [ [ :12: ] :+: [ [ :5: ] :*: [ :2: ] ] ] ::: [ [ :False: ] :!: ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteBo True
ConJmp 6
CsteNb 12
CsteNb 5
CsteNb 2
MultNb
AddiNb
Jump 2
CsteBo False
Not
Halt

Voici le résultat dans la machine JS:
...
...
...
PC : 10
Pile : [22 ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 



12?31+2:!(12*14);
lex::NOMBRE 12
lex::char ?
lex::NOMBRE 31
lex::char +
lex::NOMBRE 2
lex::char :
lex::OPERATIONBOOL !
lex::char (
lex::NOMBRE 12
lex::char *
lex::NOMBRE 14
lex::char )
newIfThenElseAST

Parsing:: syntax OK

Root symbol:: ?

/*----------.
|    AST    |
`----------*/
[ [ :12: ] :?: [ [ :31: ] :+: [ :2: ] ] ::: [ [ [ :12: ] :*: [ :14: ] ] :!: ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 12
ConJmp 4
CsteNb 31
CsteNb 2
AddiNb
Jump 4
CsteNb 12
CsteNb 14
MultNb
Not
Halt



