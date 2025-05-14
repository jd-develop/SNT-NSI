#include <stdio.h>
#include <stdlib.h>
#include "grille.h"


/* Lit dans fn une grille d'ordures */
grille_t* lire_grille(char* fn){
    FILE* f = fopen(fn, "r");
    grille_t* g = malloc(sizeof(grille_t));
    fscanf(f, "%d %d", &g->n, &g->m);

    // n lignes
    g->ordures = malloc(g->n * sizeof(int*));

    for (int i = 0; i < g->n; ++i){
        // n colonnes pour chaque ligne
        g->ordures[i] = malloc(g->m * sizeof(int));
        for (int j = 0; j < g->m; ++j){
            fscanf(f, "%d", &g->ordures[i][j]);
        }
    }
    fclose(f);
    return g;
}


void liberer_grille(grille_t* g){
    for (int i = 0; i < g->n; ++i){
        free(g->ordures[i]);
    }
    free(g->ordures);
    free(g);
}

void afficher_grille(grille_t* g){
    for (int i = 0; i < g->n; ++i){
        for (int j = 0; j < g->m; ++j){
            printf("%d ", g->ordures[i][j]);
        }
        printf("\n");
    }
}
