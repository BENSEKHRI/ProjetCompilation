# Compilateur JavaScript    -   Fragement p1.2
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
Tous les tests du fragement p0.0, p0.1, p0.2, p1.0 et p1.1 plus ce qui suit:

* L'opérateur ternaire _ ? _ : _ 

12?14:12;
lex::NUMBER 12
lex::char ?
lex::NUMBER 14
lex::char :
lex::NUMBER 12

Parsing:: syntax OK



False?12:11;
lex::BOOLEAN False
lex::char ?
lex::NUMBER 12
lex::char :
lex::NUMBER 11

Parsing:: syntax OK



12:False?1;
lex::NUMBER 12
lex::char :
Parsing:: syntax error



False?12+12*5:!True;
lex::BOOLEAN False
lex::char ?
lex::NUMBER 12
lex::char +
lex::NUMBER 12
lex::char *
lex::NUMBER 5
lex::char :
lex::char !
lex::BOOLEAN True

Parsing:: syntax OK