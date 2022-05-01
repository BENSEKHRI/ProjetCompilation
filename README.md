# Compilateur JavaScript - Fragement c0.1
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
Tous les tests du fragement c0.0 plus ce qui suit:

* Une opération modulo + respect des priorités et de l'associativité + des flottants (entiers) + ModuNb :
12+12%12.45-12*12%41--41;
lex::NOMBRE 12
lex::char +
lex::NOMBRE 12
lex::char %
lex::NOMBRE 12.45
lex::char -
lex::NOMBRE 12
lex::char *
lex::NOMBRE 12
lex::char %
lex::NOMBRE 41
lex::char -
lex::char -
lex::NOMBRE 41

Parsing:: syntax OK

Root symbol:: -

/*----------.
|    AST    |
`----------*/
[ [ [ [ :12.00 : ] :+: [ [ :12.00 : ] :%: [ :12.45 : ] ] ] :-: [ [ [ :12.00 : ] :*: [ :12.00 : ] ] :%: [ :41.00 : ] ] ] :-: [ [ :41.00 : ] :-: ] ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 12.00 
CsteNb 12.00 
CsteNb 12.45 
ModuNb
AddiNb
CsteNb 12.00 
CsteNb 12.00 
MultNb
CsteNb 41.00 
ModuNb
SubiNb
CsteNb 41.00 
NegNb
SubiNb
Halt


Il y a juste un petit soucis la machine ne comprends pas le mot clé ModuNb ça le prends comme étant un MultNb :
...
...
...
Voici la fin du programme
PC : 14
Pile : [-5701.6 ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 