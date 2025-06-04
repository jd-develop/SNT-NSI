#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <stdlib.h>
#include <assert.h>

#include "graphe.h"

float longueur(graphe_t* g, char** chemin, int n) {
    float total = 0.0;
    for (int i = 1; i < n; i++) {
        total += valeur_arc(g, chemin[i-1], chemin[i]);
    }
    return total;
}

int extraire_min(float* d, bool* q, int n) {
    float min_actuel = INFINITY;
    int indice_min_actuel = -1;

    for (int i = 0; i < n; i++) {
        if (!q[i])
            continue;
        if (d[i] < min_actuel) {
            min_actuel = d[i];
            indice_min_actuel = i;
        }
    }

    if (indice_min_actuel != -1) {
        q[indice_min_actuel] = false;
    }

    return indice_min_actuel;
}

int* dijkstra(graphe_t* g, char* s) {
    assert(stoi_mem(g->indice, s));
    int indice_s = stoi_get(g->indice, s);

    int n = g->n;
    float* d = malloc(n*sizeof(float));
    int* pred = malloc(n*sizeof(int));
    bool* q = malloc(n*sizeof(bool));
    for (int j = 0; j < n; j++) {
        d[j] = INFINITY;
        pred[j] = -1;
        q[j] = true;
    }

    d[indice_s] = 0;
    int v;
    float w;
    for (int u = extraire_min(d, q, n); u >= 0; u = extraire_min(d, q, n)) {
        for (
                adj_t* maillon = g->voisins[u];
                maillon != NULL;
                maillon = maillon->suiv
        ) {
            v = maillon->dest;
            w = maillon->poids;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pred[v] = u;
            }
        }
    }
    return pred;
}

char** pcc(graphe_t* g, char* s, char* t) {
    assert(stoi_mem(g->indice, s));
    assert(stoi_mem(g->indice, t));

    int depart = stoi_get(g->indice, s);
    int arrivee = stoi_get(g->indice, t);

    int* pred = dijkstra(g, s);

    int n = 1;
    int sommet;
    for (sommet = arrivee; sommet != depart && sommet != -1; sommet = pred[sommet]) {
        n++;
    }
    if (sommet == -1) {
        return NULL;
    }

    int* chemin_a_lenvers = malloc(n*sizeof(int));

    sommet = arrivee;
    for (int i = 0; i < n; i++) {
        chemin_a_lenvers[i] = sommet;
        sommet = pred[sommet];
    }

    char** chemin = malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++) {
        chemin[i] = g->sommets[chemin_a_lenvers[n-i-1]];
    }

    free(chemin_a_lenvers);
    return chemin;
}

