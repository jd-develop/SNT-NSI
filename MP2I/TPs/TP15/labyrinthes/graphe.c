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

void ajouter(graphe_t* g, unsigned int u, unsigned int v, bool oriente) {
    adj_t* t = (g->lv)[u];
    bool found_v = false;

    if (t == NULL) {
        (g->lv)[u] = malloc(sizeof(adj_t));
        (g->lv)[u]->voisin = v;
        (g->lv)[u]->suiv = NULL;
    } else {
        while (t->suiv != NULL) {
            if (t->voisin == v) {
                found_v = true;
                break;
            }
            t = t->suiv;
        }
        if (!found_v) {
            t->suiv = malloc(sizeof(adj_t));
            t->suiv->voisin = v;
            t->suiv->suiv = NULL;
        }
    }

    if (!oriente) {
        ajouter(g, v, u, true);
    }
}

graphe_t* lire_graphe(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Erreur : fichier invalide");
        exit(-1);
    }

    int n, m, oriente;
    unsigned int u, v;

    fscanf(fp, "%d %d %d", &n, &m, &oriente);

    graphe_t* g = graphe_vide(n);

    for (int i = 0; i < m; i++) {
        fscanf(fp, "%u %u", &u, &v);
        ajouter(g, u, v, (bool)oriente);
    }

    fclose(fp);
    return g;
}
