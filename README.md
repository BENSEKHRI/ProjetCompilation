# Compilateur JavaScript    -   Fragement c4.1
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
Dans ce fragement c4.1
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

Les variable sont stocker dans une liste globale est à chaque ajout d'un identifiant on test si elle appartient ou non à la liste pour savoir si un appel d'une variable renvoi ou non une valeur.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement c0, c1, c2, c3 et c4.0 plus ce qui suit:

* les mots clé en minuscules, les variable peuvent être en maj et min et ne sont pas des mots clés: 


Test N°01:
----------
On test avec le fichier toto.js qui contient le code suivant: 

if (12 < 4) {
    x = 12;
    TOTO = 113;
} else {
    TOTO = 1224;
    toto = 12;
    x = 4;
}

./main toto.js

lex::IF if
lex::char (
lex::NOMBRE 12
lex::OPERATIONBOOL <
lex::NOMBRE 4
lex::char )
lex::char {
lex::IDENT x
lex::AFF =
lex::NOMBRE 12
lex::char ;

IDENT: x is new - Addition in progress...
IDENT = | x |

lex::IDENT TOTO
lex::AFF =
lex::NOMBRE 113
lex::char ;

IDENT: TOTO is new - Addition in progress...
IDENT = | TOTO | x |

lex::char }
lex::ELSE else
lex::char {
lex::IDENT TOTO
lex::AFF =
lex::NOMBRE 1224
lex::char ;

IDENT: TOTO is already present. - Update in progress...
IDENT = | TOTO | x |

lex::IDENT toto
lex::AFF =
lex::NOMBRE 12
lex::char ;

IDENT: toto is new - Addition in progress...
IDENT = | toto | TOTO | x |

lex::IDENT x
lex::AFF =
lex::NOMBRE 4
lex::char ;

IDENT: x is already present. - Update in progress...
IDENT = | toto | TOTO | x |

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
| :if: [ [ :12: ] :<: [ :4: ] ] | [ :x: :=: [ :12: ] ] :;: | 
        | [ :TOTO: :=: [ :113: ] ] :;: | :else: | [ :TOTO: :=: [ :1224: ] ] :;: | 
        | [ :toto: :=: [ :12: ] ] :;: | 
        | [ :x: :=: [ :4: ] ] :;: | | 

Voici le contenu du fichier toto.jsm :

CsteNb 12
CsteNb 4
LoStNb
CondJump 7
CsteNb 12
SetVar x
GetVar x
CsteNb 113
SetVar TOTO
GetVar TOTO
Jump 3
CsteNb 1224
SetVar TOTO
GetVar TOTO
CsteNb 12
SetVar toto
GetVar toto
CsteNb 4
SetVar x
GetVar x
Halt



Test N°02:
----------
On test avec le fichier toto.js qui contient maintenant le code suivante: 

if = 12;

./main toto.js

lex::IF if
lex::AFF =
Parsing:: syntax error
