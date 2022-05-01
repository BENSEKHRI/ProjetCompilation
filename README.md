<<<<<<< HEAD
# Compilateur JavaScript    -   Fragement c2.0
=======
# Compilateur JavaScript - Fragement c1.0
>>>>>>> main
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

<<<<<<< HEAD
# Remarque
Dans ce fragement p2.0 
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement p0, p1 plus ce qui suit:

_ Les variables commencent par une lettre minuscule et peuvent être composées de lettres, de chiffres, de caractères de soulignement "_".
— Les variables sont instanciées par l'expression 5 x = expr ; où expr est une expression quelconque. Ces variables sont toujours globales.
— Respecter les priorités et l'associativité !
— Les variables peuvent être utilisées à l'intérieur des expressions.

Test N°01:
---------
x=12+15*314;

Root symbol:: 
=======
- Après exécution de ces commandes, un fichier jsm contenant le code assembleur généré est créé si l'exécution est faite avec un fichier js en argument, sinon des erreurs s'afficheront si le fichier n'est pas un js ou bien qu'il n'existe pas.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement c0.0, c0.1 et c1.0 plus ce qui suit:

Les nombres peuvent être écrits 1.215e25 ou .485e-42 ou 485e-42. Nous ajoutons également la constante NaN.

1.215e25; 
lex::NOMBRE 1.215e25

Parsing:: syntax OK

>>>>>>> main

/*----------.
|    AST    |
`----------*/
<<<<<<< HEAD
[ [ :True: ] :||: [ [ [ :False: ] :!: ] :&&: [ :True: ] ] ] 
=======
[ :1.21e+25: ] 
>>>>>>> main

/*----------------.
|    POST-FIXE    |
`----------------*/
<<<<<<< HEAD
CsteBo True
ConJmp 2
CsteBo True
Jump 4
CsteBo False
Not
ConJmp 2
CsteBo True
Jump 1
CsteBo False
Halt


Test N°02:
Execusion avec le fichier toto.js qui contient ceci :
x = 12;
y = True && False ? 5 * 12 - 12 : 15;

Sortie: ./main toto.js
=======
CsteNb 1.21e+25
Halt



.485e-42;
lex::NOMBRE .485e-42

Parsing:: syntax OK


/*----------.
|    AST    |
`----------*/
[ :4.85e-43: ] 

/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 4.85e-43
Halt
>>>>>>> main
