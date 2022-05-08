# Compilateur JavaScript    -   Fragement c3.0
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

# Remarque
Dans ce fragement c3.0 
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

Les variable sont stocker dans une liste globale est à chaque ajout d'un identifiant on test si elle appartient ou non à la liste pour savoir si un appel d'une variable renvoi ou non une valeur.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement p0, p1 et p2 plus ce qui suit:

* La boucle do while : 


Test N°01:
----------
On exécute avec le fichier toto.js qui contient ceci :

do {
    12 + 12;
    13 * 13;
} while (1 < 12);

./main toto.js

lex::DO do
lex::char {
lex::NOMBRE 12
lex::char +
lex::NOMBRE 12
lex::char ;
lex::NOMBRE 13
lex::char *
lex::NOMBRE 13
lex::char ;
lex::char }
lex::WHILE while
lex::char (
lex::NOMBRE 1
lex::OPERATIONBOOL <
lex::NOMBRE 12
lex::char )
lex::char ;

Parsing:: syntax OK

Root symbol:: 

/*-------------------------------------.
|    Writing the file toto.jsm    |
`-------------------------------------*/

/*----------.
|    AST    |
`----------*/
Program:
| :do: | [ [ :12: ] :+: [ :12: ] ] :;: | 
        | [ [ :13: ] :*: [ :13: ] ] :;: | :while: [ [ :1: ] :<: [ :12: ] ] | 
| [ :;: ] :;: | 


Voici le résultat dans le ficheir toto.jsm :

CsteNb 12
CsteNb 12
AddiNb
CsteNb 13
CsteNb 13
MultNb
CsteNb 1
CsteNb 12
LoStNb
CondJump -9
Halt

Voici la sortie de la machine js: 
...
...
...
PC : 10
Pile : [ 169 , 24 ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 


Néanmois il y a quelque problème par rapport au offset dans d'autres test qu'on a effectué nous avons trouvé des problème d'offset qui sont du au calcule de la taille.

Exemple:

Exécuton le fichier toto.js qui contient maintenant ce qui suit:

do {
    x = 12;
    12 + 12;
} while (x < 12);


./main toto.js


lex::DO do
lex::char {
lex::IDENT x
lex::AFF =
lex::NOMBRE 12
lex::char ;

IDENT: x is new - Addition in progress...
IDENT = | x |

lex::NOMBRE 12
lex::char +
lex::NOMBRE 12
lex::char ;
lex::char }
lex::WHILE while
lex::char (
lex::IDENT x
lex::OPERATIONBOOL <
lex::NOMBRE 12
lex::char )
lex::char ;

Parsing:: syntax OK

Root symbol:: 

/*-------------------------------------.
|    Writing the file toto.jsm    |
`-------------------------------------*/

/*----------.
|    AST    |
`----------*/
Program:
| :do: | [ :x: :=: [ :12: ] ] :;: | 
        | [ [ :12: ] :+: [ :12: ] ] :;: | :while: [ [ :x: ] :<: [ :12: ] ] | 
| [ :;: ] :;: | 


Voici le résultat dans le fichier toto.jsm :

CsteNb 12
SetVar x
GetVar x
CsteNb 12
CsteNb 12
AddiNb
GetVar x
CsteNb 12
LoStNb
CondJump -7
Halt


Et le offset dans le condJump est faux, il doit être -10 au lieu de -7