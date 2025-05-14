# DM3 : SAT solver

## Contenu de l'archive
- README.md
- Makefile
- utils.c
- utils.h
- n_dames.c
- maisons.c
- piece.c
- piece.h
- calendrier.c
- calendrier_n_pieces.c
- print_tab.c

## Compilation

Pour compiler sur Linux, on se place dans le répertoire `problemes/` puis :

Utiliser `make n_dames` pour compiler le problèmes des n_dames.

Utiliser `make maisons` pour compiler le problèmes des maisons.

Utiliser `make calendrier` pour compiler le problèmes du calendrier.

Utiliser `make calendrier_n_pieces` pour compiler le problèmes du calendrier partiel.

Utiliser `make print_tab` pour compiler l'affichage de tableau.

Utiliser `make mrproper` pour supprimer les fichiers temporaires et exécutables.

L'option `debug=1` pour compiler avec les options de débogage.

## Exécution n_dames

le programme s'exécute dans la forme
```
./n_dames 'n'
```
avec `n` le nombre de dames.

Il crée un fichier de nom `'n'_dames.txt` qui peut être utiliser avec un satsolver
(voir [Satsolver](../satsolver/README.md))

## Exécution maisons

le programme s'exécute dans la forme
```
./maisons
```

Il crée un fichier de nom `5maisons.txt` qui peut être utiliser avec un satsolver
(voir [Satsolver](../satsolver/README.md))

## Exécution calendrier et calendrier_n_pieces

le programme s'exécute dans la forme
```
./calendrier 'j_semaine' 'jour' 'mois'
```
avec `j_semaine`, `jour` et `mois` qui sont le jour de la semaine [1-7],
le jour [1-31] et le mois [1-12], ou
```
./calendrier_n_pieces 'n'
```
avec `n` le nombre de pièces a tester.

Il crée un fichier de nom `calendrier.txt` ou `calendrier_'n'_pieces.txt`
qui peut être utiliser avec un satsolver (voir [Satsolver](../satsolver/README.md))

## Exécution print_tab

le programme s'exécute dans la forme
```
./print_tab 'n' <'liste_varibles.txt'
```
ou
```
'satsolver' | ./print_tab 'n'
```
avec `n` la taille du tableau.

Il affiche la liste `liste_varibles.txt` ou
la sortie de `satsolver` sous la forme d'un tableau.

Chaque variable doit être sur une ligne et de la forme :
```
X_i_j
```
avec `X` le caractère de la pièces, `i` la ligne et `j` la colonne.
Il ignore toute les autres ligne.

## Exemple

Pour `n_dames` et `print_tab` :
```
~/DM3/problemes$ make n_dames print_tab 
gcc n_dames.c utils.c utils.h -Wextra -Wall -lm -o n_dames
gcc print_tab.c -Wextra -Wall -lm -o print_tab
~/DM3/problemes$ ./n_dames 15
Fichier '15_dames.txt' généré.
Taille du fichier : 112521 octets.
~/DM3/problemes$ ../satsolver/fnc_solver 15_dames.txt | ./print_tab 15
La formule est sous FNC.
La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres :
X_0_9
X_10_8
X_11_6
X_12_4
X_13_7
X_14_13
X_6_2
X_1_3
X_2_12
X_3_10
X_5_5
X_9_14
X_7_0
X_8_11
X_4_1
Temps d'exécution : 0.053628 s
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                          |  |              |
+        +--+              +--+              +
|        |  |                                |
+        +--+                       +--+     +
|                                   |  |     |
+                             +--+  +--+     +
|                             |  |           |
+  +--+                       +--+           +
|  |  |                                      |
+  +--+        +--+                          +
|              |  |                          |
+     +--+     +--+                          +
|     |  |                                   |
+--+  +--+                                   +
|  |                                         |
+--+                             +--+        +
|                                |  |        |
+                                +--+     +--+
|                                         |  |
+                       +--+              +--+
|                       |  |                 |
+                 +--+  +--+                 +
|                 |  |                       |
+           +--+  +--+                       +
|           |  |                             |
+           +--+     +--+                    +
|                    |  |                    |
+                    +--+              +--+  +
|                                      |  |  |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
```
