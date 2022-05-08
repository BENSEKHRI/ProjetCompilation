# Compilateur JavaScript    -   Fragement c2.1
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
Dans ce fragement c2.1
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

Les variable sont stocker dans une liste globale est à chaque ajout d'un identifiant on test si elle appartient ou non à la liste pour savoir si un appel d'une variable renvoi ou non une valeur.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement c0, c1 et c2.0 plus ce qui suit:

Un programme est maintenant une séquence de commandes, tandis qu'une commande est soit une expression expr ; soit une nouvelle commande if(_) _ else _ .

Test N°01:
----------
if(True) False; else True; €
lex::IF if
lex::char (
lex::BOOLEAN True
lex::char )
lex::BOOLEAN False
lex::char ;
lex::ELSE else
lex::BOOLEAN True
lex::char ;

Parsing:: syntax OK


/*----------.
|    AST    |
`----------*/
Program:
| :if: [ :True: ] | [ :False: ] :;: | :else: | [ :True: ] :;: | | 


/*----------------.
|    POST-FIXE    |
`----------------*/
CsteBo True
CondJump 2
CsteBo False
Jump 1
CsteBo True
Halt

Voici la sortie de la machine JS:
...
...
...
PC : 5
Pile : [False ]
Contexte : |
Instruction : Halt

Programme exécuté avec succes 




Test N°02: 
----------
Exécution avec le fichier toto.js qui contient : 
if(12 < 12 * 12) c = 2 + 3;

./main toto.js

else c = 41 % 12;
lex::IF if
lex::char (
lex::NOMBRE 12
lex::OPERATIONBOOL <
lex::NOMBRE 12
lex::char *
lex::NOMBRE 12
lex::char )
lex::IDENT c
lex::AFF =
lex::NOMBRE 2
lex::char +
lex::NOMBRE 3
lex::char ;

IDENT: c is new - Addition in progress...
IDENT = | c |

lex::ELSE else
lex::IDENT c
lex::AFF =
lex::NOMBRE 41
lex::char -
lex::NOMBRE 12
lex::char ;

IDENT: c is already present. - Update in progress...
IDENT = | c |


Parsing:: syntax OK

Root symbol:: 

/*-------------------------------------.
|    Writing the file toto.jsm    |
`-------------------------------------*/

/*----------.
|    AST    |
`----------*/
Program:
| :if: [ [ :12: ] :<: [ [ :12: ] :*: [ :12: ] ] ] | [ :c: :=: [ [ :2: ] :+: [ :3: ] ] ] :;: | :else: | [ :c: :=: [ [ :41: ] :-: [ :12: ] ] ] :;: | | 



Voici le contenu du fichier toto.jsm:

CsteNb 12
CsteNb 12
CsteNb 12
MultNb
LoStNb
CondJump 5
CsteNb 2
CsteNb 3
AddiNb
SetVar c
GetVar c
Jump 5
CsteNb 41
CsteNb 12
SubiNb
SetVar c
GetVar c
Halt



Voici la sortie de la machine JS: 
...
...
...
PC : 17
Pile : [5 ]
Contexte : ( c => 5 ),  |
Instruction : Halt

Programme exécuté avec succes 
