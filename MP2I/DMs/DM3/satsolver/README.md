# DM3 : SAT solver

## Contenu de l'archive
- README.md
- Makefile
- satsolver.ml
- fnc_solver.ml
- tests/
    + test1
    + test2
    + test3
    + test4
    + test5
    + test_impossible
    + zerowidthspace

## Compilation

Pour compiler sur Linux, on se place dans le répertoire `satsolver/` puis :

Utiliser `make satsolver` pour compiler le satsolver.

Utiliser `make fnc_solver` pour compiler le satsolver spécialiser en FNC.

Utiliser `make clear` pour nettoyer les fichiers temporaires.

Utiliser `make mrproper` pour supprimer les fichiers temporaires et exécutables.

## Exécution

le programme s'exécute dans la forme
```
./satsolver 'entrée.txt'
```
ou
```
./fnc_solver 'entrée.txt'
```
avec `entrée.txt` un fichier texte (voir [Format d'entrée](#format-dentrée))

A la fin de son exécution, il affiche les solutions et le temps correspondant.
Avec `fnc_solver`, il affiche en plus si `entrée.txt` est en FNC.

## Format d'entrée

Le fichier d' `entrée.txt` doit contenir une formule booléen avec :

Les espaces sont autoriser mais ignorer.

`(...)` pour les parenthèse.

`T` et `F` pour vrai et faux.

`~`, `&` et `|`  pour non, et et ou

`=` et `>` pour équivalent et implique.

Tout le reste sera compris comme une variable.
Il est toutefois conseiller de mettre les variables sous une forme lisible,
comme : `X_0_0`

La priorité des opérations sont `~`, `&`, `|`, `=` puis `>`

### Exemple
Pour `entrée.txt` :
```
(V_1 | ~V_2 | ~V_3) & (~V_1 | ~V_2 | ~V_3) & (V_1 | V_2)
```

Pour `fnc_solver` :
```
~/DM3/problemes$ make fnc_solver 
ocamlopt fnc_solver.ml -o fnc_solver
~/DM3/problemes$ ./fnc_solver 'entrée.txt' 
La formule est fnc
La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres :
V_2
Temps d'exécution : 0.001133 s
```
