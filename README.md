# Compilateur JavaScript    -   Fragement c3.1
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
Dans ce fragement c3.1 
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

Les variable sont stocker dans une liste globale est à chaque ajout d'un identifiant on test si elle appartient ou non à la liste pour savoir si un appel d'une variable renvoi ou non une valeur.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement c0, c1, c2 et c3.0 plus ce qui suit:

* La boucle while : 


Test N°01:
----------

On exécute le fichier toto.js qui contient le code suivant: 
while (12 == 12) {
    c = 1 + 3;
}

./main toto.js 

lex::WHILE while
lex::char (
lex::NOMBRE 12
lex::OPERATIONBOOL ==
lex::NOMBRE 12
lex::char )
lex::char {
lex::IDENT c
lex::AFF =
lex::NOMBRE 1
lex::char +
lex::NOMBRE 3
lex::char ;

IDENT: c is new - Addition in progress...
IDENT = | c |

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
| :while: [ [ :12: ] :==: [ :12: ] ] | [ :c: :=: [ [ :1: ] :+: [ :3: ] ] ] :;: | | 


Voici le résultat dans toto.jsm :

CsteNb 12
CsteNb 12
Equals
CondJump 9
CsteNb 1
CsteNb 3
AddiNb
SetVar c
GetVar c
Jump -10
Halt

On remarque que les offset sont faux dans quelques cas. 


