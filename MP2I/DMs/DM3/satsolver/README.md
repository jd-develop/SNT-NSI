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

Pour compiler sous GNU/Linux, il faut se placer dans le répertoire `satsolver/`
puis&nbsp;:

* Utiliser `make satsolver` pour compiler le satsolver.
* Utiliser `make fnc_solver` pour compiler le satsolver spécialisé en FNC.
* Utiliser `make clear` pour nettoyer les fichiers temporaires.
* Utiliser `make mrproper` pour supprimer les fichiers temporaires et les
  exécutables.

## Exécution

Le programme s'exécute avec la commande suivante&nbsp;:
```bash
./satsolver 'entrée.txt'
```
ou
```bash
./fnc_solver 'entrée.txt'
```
avec `entrée.txt` un fichier texte (voir [Format d'entrée](#format-dentrée))

À la fin de son exécution, il affiche les solutions et le temps correspondant.
Avec `fnc_solver`, il affiche en plus si `entrée.txt` est en FNC.

## Format d'entrée

Le fichier `entrée.txt` doit contenir une formule booléenne avec&nbsp;:

* Les espaces sont autorisés mais ignorés. Les espaces insécables et insécables
fines sont considérés comme des caractères valides dans les noms de variable.
* `(...)` pour les parenthèse.
* `T` et `F` pour vrai et faux.
* `~`, `&` et `|`  pour non, et et ou
* `=` et `>` pour équivalent et implique.
* Tout le reste (i.e. tous les autres caractères unicode) sera compris comme un
  nom de variable.
* Il est toutefois conseillé de mettre les variables sous une forme lisible,
  comme : `X_0_0`

La priorité des opérations est `~`, `&`, `|`, `=` puis `>`

## Exemple
Si `entrée.txt` contient&nbsp;:
```
(V_1 | ~V_2 | ~V_3) & (~V_1 | ~V_2 | ~V_3) & (V_1 | V_2)
```

Pour `fnc_solver`&nbsp;:
```console
~/DM3/satsolver$ make fnc_solver
ocamlopt fnc_solver.ml -o fnc_solver
~/DM3/satsolver$ ./fnc_solver 'entrée.txt'
La formule est fnc
La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres :
V_2
Temps d'exécution : 0.001133 s
```
