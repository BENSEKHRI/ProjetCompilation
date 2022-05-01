# Compilateur JavaScript - Fragement c0.0
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

* Nous avons effectué plusieurs tests avec fichier en argument. Il faut que le fichier qu'on passe en argot soit un js, sinon une erreur est affichée et le programme s'arrête, lors de l'exécution avec un fichier js un fichier jsm contenant le code assembleur généré est créé.

** Voici les différents tests sur console et c'est exactement le résultat profix qui est écrit dans le fichier jsm:

* Un type de base unic : Nombre => entiers
12;
lex::NOMBRE 12

Parsing:: syntax OK


/*----------.
|    AST    |
`----------*/
[ :12: ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 12
Halt



-12;
lex::char -
lex::NOMBRE 12

Parsing:: syntax OK

Root symbol:: -

/*----------.
|    AST    |
`----------*/
[ :-: [ :12: ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 12
NegNb
Halt


* Opérations arithmétiques ("+", "-" et "*").
1+9;
lex::NOMBRE 1
lex::char +
lex::NOMBRE 9

Parsing:: syntax OK

Root symbol:: +

/*----------.
|    AST    |
`----------*/
[ [ :1: ] :+: [ :9: ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 1
CsteNb 9
AddiNb
Halt

* Aucune variable n'est prise en compte.
x;
lex::char x
Parsing:: syntax error

* Un programme ne peut être que de la forme " expression ; "
2+3+5;
lex::NOMBRE 2
lex::char +
lex::NOMBRE 3
lex::char +
lex::NOMBRE 5

Parsing:: syntax OK

Root symbol:: +

/*----------.
|    AST    |
`----------*/
[ [ [ :2: ] :+: [ :3: ] ] :+: [ :5: ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 2
CsteNb 3
AddiNb
CsteNb 5
AddiNb
Halt



2*(3+2);
lex::NOMBRE 2
lex::char *
lex::char (
lex::NOMBRE 3
lex::char +
lex::NOMBRE 2
lex::char )

Parsing:: syntax OK

Root symbol:: *

/*----------.
|    AST    |
`----------*/
[ [ :2: ] :*: [ [ :3: ] :+: [ :2: ] ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 2
CsteNb 3
CsteNb 2
AddiNb
MultNb
Halt



2+3*2;
lex::NOMBRE 2
lex::char +
lex::NOMBRE 3
lex::char *
lex::NOMBRE 2

Parsing:: syntax OK

Root symbol:: +

/*----------.
|    AST    |
`----------*/
[ [ :2: ] :+: [ [ :3: ] :*: [ :2: ] ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 2
CsteNb 3
CsteNb 2
MultNb
AddiNb
Halt


Des tests ont été bien sûr effectué sur l'écriture directement en fichier.jsm.

Et aussi des tests par rapport au résultats obtenues si il est lisible est compréhensible par la machine js.

Voici un exemple:
dans un fichier js:
--12 * 30 + 12--12 * (3 + 12)

dans le fichier jsm:
CsteNb 12
NegNb
NegNb
CsteNb 30
MultNb
CsteNb 12
AddiNb
CsteNb 12
NegNb
CsteNb 3
CsteNb 12
AddiNb
MultNb
SubiNb
Halt

Le résultat de la machine JS:
...
...
...
Voici la fin :
PC : 14
Pile : [552 ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 