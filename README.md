# Compilateur JavaScript    -   Fragement c2.2
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
Dans ce fragement c2.2
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

Les variable sont stocker dans une liste globale est à chaque ajout d'un identifiant on test si elle appartient ou non à la liste pour savoir si un appel d'une variable renvoi ou non une valeur.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement p0, p1, p2.0 et p2.1 plus ce qui suit:

* Nous ajoutons la commande vide " ;".
* De plus, nous pouvons compacter une séquence de commandes en un seul command en appliquant les paniers {com1 ... comk}.

Test N°01:
----------
;€
lex::char ;

Parsing:: syntax OK


/*----------.
|    AST    |
`----------*/
Program:
| [ :;: ] :;: | 


/*----------------.
|    POST-FIXE    |
`----------------*/
Halt


Test N°03:
----------
On exécute avec le fichier toto.js qui contient ceci :

{
    x = 12 * 12 + 12;
    if (x == 12) {
        c = 12;
    } else {
        c = 14;
        y = 12;
    }
}

./main toto.js

lex::char {
lex::IDENT x
lex::AFF =
lex::NOMBRE 12
lex::char *
lex::NOMBRE 12
lex::char +
lex::NOMBRE 12
lex::char ;

IDENT: x is new - Addition in progress...
IDENT = | x |

lex::IF if
lex::char (
lex::IDENT x
lex::OPERATIONBOOL ==
lex::NOMBRE 12
lex::char )
lex::char {
lex::IDENT c
lex::AFF =
lex::NOMBRE 12
lex::char ;

IDENT: c is new - Addition in progress...
IDENT = | c | x |

lex::char }
lex::ELSE else
lex::char {
lex::IDENT c
lex::AFF =
lex::NOMBRE 14
lex::char ;

IDENT: c is already present. - Update in progress...
IDENT = | c | x |

lex::IDENT y
lex::AFF =
lex::NOMBRE 12
lex::char ;

IDENT: y is new - Addition in progress...
IDENT = | y | c | x |

lex::char }
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
{ 
        | [ :x: :=: [ [ [ :12: ] :*: [ :12: ] ] :+: [ :12: ] ] ] :;: | 
        | :If: [ [ :x: ] :==: [ :12: ] ] | [ :c: :=: [ :12: ] ] :;: | :Else: | [ :c: :=: [ :14: ] ] :;: | 
        | [ :y: :=: [ :12: ] ] :;: | | 
}

Voici la sortie de la machine js:

...
...
...
PC : 21
Pile : [ 12 , 156 ]
Contexte : ( x => 156 ),  ( y => 12 ),  |
Instruction : Halt

Programme exécuté avec succes 