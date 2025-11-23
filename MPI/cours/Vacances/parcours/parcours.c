#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    int* deg;
    int** succ;
} graphe_t;

/*
let g1: graphe =
  [|
    [1; 2; 3]; (* 0 ou a*)
    [4];       (* 1 ou b*)
    [3; 4];    (* 2 ou c*)
    [5];       (* 3 ou d*)
    [5];       (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g2: graphe =
  [|
    [1];       (* 0 ou a*)
    [2; 4];    (* 1 ou b*)
    [3];       (* 2 ou c*)
    [];        (* 3 ou d*)
    [0];       (* 4 ou e*)
    [3]        (* 5 ou f*)
  |]

let g3: graphe =
  [|
    [1; 4];    (* 0 ou a*)
    [5; 6];    (* 1 ou b*)
    [1];       (* 2 ou c*)
    [0];       (* 3 ou d*)
    [3; 5];    (* 4 ou e*)
    [6];       (* 5 ou f*)
    [2; 7];    (* 6 ou g*)
    [2]        (* 7 ou h*)
  |]

let g4: graphe =
  [|
    [5];       (* 0 ou a*)
    [0; 2];    (* 1 ou b*)
    [3];       (* 2 ou c*)
    [1];       (* 3 ou d*)
    [0; 3];    (* 4 ou e*)
    [4]        (* 5 ou f*)
  |]

let g5: graphe =
  [|
    [2; 3];    (* 0 ou a*)
    [0];       (* 1 ou b*)
    [5];       (* 2 ou c*)
    [2; 4];    (* 3 ou d*)
    [];        (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g6: graphe =
  [|
    [];        (* 0 *)
    [0; 2];    (* 1 *)
    [1; 3];    (* 2 *)
    [4];       (* 3 *)
    [2];       (* 4 *)
    [3];       (* 5 *)
    [4; 7];    (* 6 *)
    [5; 6];    (* 7 *)
  |]
*/

/* Créée un graphe vide. Les degrés sont initalisés à 0 et les successeurs à
 * NULL */
graphe_t* create_graph(int n) {
    graphe_t* g = malloc(sizeof(graphe_t));
    g->n = n;
    g->deg = malloc(n*sizeof(int));
    g->succ = malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        g->deg[i] = 0;
        g->succ[i] = NULL;
    }

    return g;
}


/* Change le degré du sommet sommet à degre dans le graphe g. succ[sommet] est
 * désalloué puis réalloué à un tableau de taille degre initialisé à 0.
 * Valeur de retour :
 * * 0 si tout s’est bien déroulé
 * * 1 si sommet est supérieur ou égal au nombre n de sommets */
int set_degree(graphe_t* g, int sommet, int degre) {
    if (sommet >= g->n) {
        return 1;
    }
    g->deg[sommet] = degre;

    if (g->succ[sommet] != NULL) {
        free(g->succ[sommet]);
    }
    g->succ[sommet] = malloc(degre*sizeof(int));

    for (int i = 0; i < degre; i++) {
        g->succ[sommet][i] = 0;
    }

    return 0;
}


/* Libère le graphe g */
void free_graphe(graphe_t* g) {
    for (int i = 0; i < n; i++) {
        if (g->succ[i] != NULL) {
            free(g->succ[i]);
        }
    }
    free(g->succ);
    free(g->deg);
    free(g);
}


int main() {
    

    return 0;
}
