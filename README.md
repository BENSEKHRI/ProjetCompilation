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
lex::NUMBER 12

Parsing:: syntax OK

* Opérations arithmétiques ("+", "-" et "*").
1+9;     
lex::NUMBER 1
lex::char +
lex::NUMBER 9

Parsing:: syntax OK

* Aucune variable n'est prise en compte.
x;
lex::char x
Parsing:: syntax error

* Un programme ne peut être que de la forme " expression ; "
2*(3+2);
lex::NUMBER 2
lex::char *
lex::char (
lex::NUMBER 3
lex::char +
lex::NUMBER 2
lex::char )

Parsing:: syntax OK

