# TP10

## Exercice 4

4. Il semblerait que l’ordre par défaut de OCaml regarde si deux éléments sont
   de même valeur (par exemple s’il s’agit de deux nombres). Si c’est
   le cas, il regarde chaque « argument » dans l’ordre jusqu’à trouver deux
   arguments différents à comparer. S’il trouve deux éléments différents,
   il compare l’ordre dans lequel ils sont déclarés dans le type somme (donc par
   exemple si on a :
    ```ocaml
    type Lorem = | Ipsum | Dolor | Sit | Amet
    ```
   alors on aura `Ipsum` < `Dolor` < `Sit` < `Amet`)
