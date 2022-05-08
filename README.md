# Compilateur JavaScript    -   Fragement p3.2
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
Dans ce fragement p3.2 
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement p0, p1, p2 et p3.1 plus ce qui suit:

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
lex::NUMBER 0
lex::char ;
lex::IDENT x
lex::OPERATIONBOOL <
lex::NUMBER 12
lex::char ;
lex::IDENT x
lex::char +
lex::NUMBER 1
lex::char )
lex::char {
lex::IDENT x
lex::AFF =
lex::IDENT x
lex::char +
lex::NUMBER 1
lex::char ;
lex::char }

Parsing:: syntax OK