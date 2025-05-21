#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graphe.h"

void print_graphe(graphe_t* g) {
    printf("Graphe à %d sommets :\n", g->n);
    adj_t* sommet;
    bool premier_voisin = true;

    for (int i = 0; i < g->n; i++) {
        printf("%d -> ", i);
        sommet = g->lv[i];
        if (sommet == NULL) {
            printf("-");
        }

        premier_voisin = true;
        while (sommet != NULL) {
            if (premier_voisin) {
                premier_voisin = false;
            } else {
                printf(", ");
            }
            printf("%d", sommet->voisin);
            sommet = sommet->suiv;
        }
        printf("\n");
    }
}

void free_graphe(graphe_t* g) {
    adj_t* suivant;
    adj_t* courant;
    for (int i = 0; i < g->n; i++) {
        courant = g->lv[i];
        while (courant != NULL) {
            suivant = courant->suiv;
            free(courant);
            courant = suivant;
        }
    }
    free(g->lv);
    free(g);
}

graphe_t* graphe_vide(int n) {
    graphe_t* g = malloc(sizeof(graphe_t));
    g->n = n;
    g->lv = calloc(n, sizeof(adj_t*));
    return g;
}
