# Compilateur JavaScript    -   Fragement p2.1
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
Dans ce fragement p2.0 
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement p0, p1 et p2.0 plus ce qui suit:

* Un programme est maintenant une séquence de commandes, tandis  qu'une commande est soit une expression expr ; soit une nouvelle commande If(_) _ Else _ .

Test N°01:
----------
If(12*12>21) x=12; Else c=14;
lex::IF If
lex::char (
lex::NUMBER 12
lex::char *
lex::NUMBER 12
lex::OPERATIONBOOL >
lex::NUMBER 21
lex::char )
lex::IDENT x
lex::AFF =
lex::NUMBER 12
lex::char ;
lex::ELSE Else
lex::IDENT c
lex::AFF =
lex::NUMBER 14
lex::char ;

x=12*12%1;
lex::IDENT x
lex::AFF =
lex::NUMBER 12
lex::char *
lex::NUMBER 12
lex::char %
lex::NUMBER 1
lex::char ;
€

Parsing:: syntax OK


Test N°02:
----------

Test avec le contenu du fichier toto.js qui contient ceci :  

If(True) c = 41 % 12;
Else False && True;

./main toto.js

lex::IF If
lex::char (
lex::BOOLEAN True
lex::char )
lex::IDENT c
lex::AFF =
lex::NUMBER 41
lex::char %
lex::NUMBER 12
lex::char ;
lex::ELSE Else
lex::BOOLEAN False
lex::OPERATIONBOOL &&
lex::BOOLEAN True
lex::char ;

Parsing:: syntax OK
