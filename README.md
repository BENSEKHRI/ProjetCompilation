# Compilateur JavaScript    -   Fragement c2.0
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
Dans ce fragement c2.0 
si on execute sur console sans un fichier js, pour finir une instruction on tape ';' et pour finir le programme on tape '€'.

Les variable sont stocker dans une liste globale est à chaque ajout d'un identifiant on test si elle appartient ou non à la liste pour savoir si un appel d'une variable renvoi ou non une valeur.

# Teste des fonctionnalités
Les test de fonctionnalité qui ont été mené sont les suivants: 
Tous les tests du fragement p0, p1 plus ce qui suit:

_ Les variables commencent par une lettre minuscule et peuvent être composées de lettres, de chiffres, de caractères de soulignement "_".
— Les variables sont instanciées par l'expression 5 x = expr ; où expr est une expression quelconque. Ces variables sont toujours globales.
— Respecter les priorités et l'associativité !
— Les variables peuvent être utilisées à l'intérieur des expressions.
— Instruction d'assemblage autorisée supplémentaire : SetVar, GetVar.

Test N°01:
---------
x=12+15*314;
lex::IDENT x
lex::AFF =
lex::NOMBRE 12
lex::char +
lex::NOMBRE 15
lex::char *
lex::NOMBRE 314
lex::char ;

IDENT: x is new - Addition in progress...
IDENT = | x |

€

Parsing:: syntax OK

Root symbol:: 

/*----------.
|    AST    |
`----------*/
Program:
| [ :x: :=: [ [ :12: ] :+: [ [ :15: ] :*: [ :314: ] ] ] ] :;: | 


/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 12
CsteNb 15
CsteNb 314
MultNb
AddiNb
SetVar x
GetVar x
Halt




Test N°02:
----------
Execusion avec le fichier toto.js qui contient ceci :
x = 12;
y = True && False ? 5 * 12 - 12 : 15;

Sortie: ./main toto.js

CsteBo True
ConJmp 2
CsteBo False
Jump 1
CsteBo False
ConJmp 6
CsteNb 5
CsteNb 12
MultNb
CsteNb 12
SubiNb
Jump 1
CsteNb 15
SetVar y
GetVar y
Halt



Test N°03:
----------
c=12;
lex::IDENT c
lex::AFF =
lex::NOMBRE 12
lex::char ;

IDENT: c is new - Addition in progress...
IDENT = | c |

c=12*c;
lex::IDENT c
lex::AFF =
lex::NOMBRE 12
lex::char *
lex::IDENT c
lex::char ;

IDENT: c is already present. - Update in progress...
IDENT = | c |

True?c=41%12:False&&True;
lex::BOOLEAN True
lex::char ?
lex::IDENT c
lex::AFF =
lex::NOMBRE 41
lex::char %
lex::NOMBRE 12
lex::char :

IDENT: c is already present. - Update in progress...
IDENT = | c |

lex::BOOLEAN False
lex::OPERATIONBOOL &&
lex::BOOLEAN True
lex::char ;
newIfThenElseAST
;
lex::char ;
€

Parsing:: syntax OK

Root symbol:: 

/*----------.
|    AST    |
`----------*/
Program:
| [ :c: :=: [ :12: ] ] :;: | 
| [ :c: :=: [ [ :12: ] :*: [ :c: ] ] ] :;: | 
| [ [ :True: ] :?: [ :c: :=: [ [ :41: ] :%: [ :12: ] ] ] ::: [ [ :False: ] :&&: [ :True: ] ] ] :;: | 
| [ :;: ] :;: | 


/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 12
SetVar c
GetVar c
CsteNb 12
GetVar c
MultNb
SetVar c
GetVar c
CsteBo True
ConJmp 5
CsteNb 41
CsteNb 12
ModuNb
SetVar c
GetVar c
Jump 3
CsteBo False
ConJmp 2
CsteBo True
Jump 1
CsteBo False
Halt



Test N°04:
----------

5+(x=12+12);€
lex::NOMBRE 5
lex::char +
lex::char (
lex::IDENT x
lex::AFF =
lex::NOMBRE 12
lex::char +
lex::NOMBRE 12
lex::char )

IDENT: x is new - Addition in progress...
IDENT = | x |

lex::char ;

Parsing:: syntax OK

Root symbol:: +

/*----------.
|    AST    |
`----------*/
Program:
| [ [ :5: ] :+: [ :x: :=: [ [ :12: ] :+: [ :12: ] ] ] ] :;: | 


/*----------------.
|    POST-FIXE    |
`----------------*/
CsteNb 5
CsteNb 12
CsteNb 12
AddiNb
SetVar x
GetVar x
AddiNb
Halt



Tous les codes généré sont bien sur testé avec la machine JS.
