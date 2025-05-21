#include "graphe.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main() {
    graphe_t* g = graphe_vide(5);

    // successeurs de 0: [1, 4]
    g->lv[0] = malloc(sizeof(adj_t));
    g->lv[0]->voisin = 1;
    g->lv[0]->suiv = NULL;

    // successeurs de 1: [2, 3, 4]
    g->lv[1] = malloc(sizeof(adj_t));
    g->lv[1]->voisin = 3;
    g->lv[1]->suiv = malloc(sizeof(adj_t));
    g->lv[1]->suiv->voisin = 2;
    g->lv[1]->suiv->suiv = malloc(sizeof(adj_t));
    g->lv[1]->suiv->suiv->voisin = 4;
    g->lv[1]->suiv->suiv->suiv = NULL;

    // successeurs de 2: [0, 3]
    g->lv[2] = malloc(sizeof(adj_t));
    g->lv[2]->voisin = 0;
    g->lv[2]->suiv = malloc(sizeof(adj_t));
    g->lv[2]->suiv->voisin = 3;
    g->lv[2]->suiv->suiv = NULL;

    // successeurs de 3: [0]
    g->lv[3] = malloc(sizeof(adj_t));
    g->lv[3]->voisin = 0;
    g->lv[3]->suiv = NULL;

    // successeurs de 3: [1, 4]
    g->lv[4] = malloc(sizeof(adj_t));
    g->lv[4]->voisin = 1;
    g->lv[4]->suiv = malloc(sizeof(adj_t));
    g->lv[4]->suiv->voisin = 4;
    g->lv[4]->suiv->suiv = NULL;

    print_graphe(g);
    free_graphe(g);

    return 0;
}
