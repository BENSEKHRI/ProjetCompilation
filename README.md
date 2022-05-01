# Compilateur JavaScript    -   Fragement p1.0
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

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement p0.0 et p0.1 et p0.2 plus ce qui suit:

* Les nombres peuvent être écrits 1.215e25 ou .485e-42 ou 485e-42. Nous ajoutons également la constante NaN.

1.215e25;
lex::NUMBER 1.215e25

Parsing:: syntax OK



.485e-42;
lex::NUMBER .485e-42

Parsing:: syntax OK



485e-42;
lex::NUMBER 485e-42

Parsing:: syntax OK



NaN;
lex::NUMBER NaN

Parsing:: syntax OK