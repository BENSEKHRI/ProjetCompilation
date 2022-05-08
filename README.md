# Compilateur JavaScript    -   Fragement c3.2
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
Dans ce fragement c3.2 
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

Les variable sont stocker dans une liste globale est à chaque ajout d'un identifiant on test si elle appartient ou non à la liste pour savoir si un appel d'une variable renvoi ou non une valeur.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement c0, c1, c2, c3.0 et c3.1 plus ce qui suit:

* La boucle for et optimisation.


Test N°01:
----------

On teste avec le fichier toto.js qui contient ce qui suit: 

for (x = 0; x < 12; x + 1) {
    x = x + 1;
}


./main toto.js 

lex::FOR for
lex::char (
lex::IDENT x
lex::AFF =
lex::NOMBRE 0
lex::char ;

IDENT: x is new - Addition in progress...
IDENT = | x |

lex::IDENT x
lex::OPERATIONBOOL <
lex::NOMBRE 12
lex::char ;
lex::IDENT x
lex::char +
lex::NOMBRE 1
lex::char )
lex::char {
lex::IDENT x
lex::AFF =
lex::IDENT x
lex::char +
lex::NOMBRE 1
lex::char ;

IDENT: x is already present. - Update in progress...
IDENT = | x |

lex::char }

Parsing:: syntax OK

Root symbol:: 

/*-------------------------------------.
|    Writing the file toto.jsm    |
`-------------------------------------*/

/*----------.
|    AST    |
`----------*/
Program:
| :for: [ :x: :=: [ :0: ] ] [ [ :x: ] :<: [ :12: ] ] [ [ :x: ] :+: [ :1: ] ] | [ :x: :=: [ [ :x: ] :+: [ :1: ] ] ] :;: | | 


Voici le contenue du fichier toto.jsm :

CsteNb 0
SetVar x
GetVar x
GetVar x
CsteNb 12
LoStNb
CondJump 9
GetVar x
CsteNb 1
AddiNb
SetVar x
GetVar x
GetVar x
CsteNb 1
AddiNb
Jump -9
Halt


Le problème est juste dans les offsets.