#include "graphe.h"
#include "stoi.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <float.h>

void afficher(graphe_t* g){
    for (int i = 0; i < g->n; ++i)
    {
        printf("%s -> ", g->sommets[i]);
        // parcourir la liste chaînée des voisins du sommet i
        adj_t* maillon = g->voisins[i];
        while (maillon != NULL){
            char* nom_voisin = g->sommets[maillon->dest];
            printf("(%s, %f), ", nom_voisin, maillon->poids);
            maillon = maillon->suiv;
        }
        printf("\n");
    }
}

bool est_arc(graphe_t* g, char* u, char* v){
    assert(stoi_mem(g->indice, u));
    assert(stoi_mem(g->indice, v));

    // retrouver les indices des sommets
    int i = stoi_get(g->indice, u);
    int j = stoi_get(g->indice, v);

    // chercher j dans la liste des voisins de i
    adj_t* maillon = g->voisins[i];
    while (maillon != NULL && maillon->dest != j){
        maillon = maillon->suiv;
    }
    // en sortie: soit maillon vaut NULL, soit maillon représente un arc (i, j)
    return (maillon != NULL);
}

graphe_t* graphe_vide(char** sommets, int n) {
    graphe_t* res = malloc(sizeof(graphe_t));

    res->n = n;
    res->sommets = sommets;

    res->voisins = malloc(n*sizeof(adj_t*));
    res->indice = stoi_vide();
    for (int i = 0; i < n; i++) {
        res->voisins[i] = NULL;
        stoi_set(res->indice, sommets[i], i);
    }
    return res;
}

void ajouter_arc(graphe_t* g, char* u, char* v, float w) {
    assert(stoi_mem(g->indice, u));
    assert(stoi_mem(g->indice, v));

    // indice des sommets
    int i = stoi_get(g->indice, u);
    int j = stoi_get(g->indice, v);

    adj_t* maillon = g->voisins[i];
    if (maillon == NULL) {
        g->voisins[i] = malloc(sizeof(adj_t));
        g->voisins[i]->dest = j;
        g->voisins[i]->poids = w;
        g->voisins[i]->suiv = NULL;

        return;
    }
    while (maillon->suiv != NULL) {
        maillon = maillon->suiv;
    }
    maillon->suiv = malloc(sizeof(adj_t));
    maillon->suiv->dest = j;
    maillon->suiv->poids = w;
    maillon->suiv->suiv = NULL;
}

/* Note : on ne libère pas le tableau de sommets */
void graphe_free(graphe_t* g) {
    adj_t* maillon;
    adj_t* maillon_temporaire;

    stoi_free(g->indice);
    for (int i = 0; i < g->n; i++) {
        maillon = g->voisins[i];
        while (maillon != NULL) {
            maillon_temporaire = maillon->suiv;
            free(maillon);
            maillon = maillon_temporaire;
        }
    }
    free(g->voisins);
    free(g);
}

float valeur_arc(graphe_t* g, char* u, char* v) {
    assert(stoi_mem(g->indice, u));
    assert(stoi_mem(g->indice, v));

    // retrouver les indices des sommets
    int i = stoi_get(g->indice, u);
    int j = stoi_get(g->indice, v);

    // chercher j dans la liste des voisins de i
    adj_t* maillon = g->voisins[i];
    while (maillon != NULL && maillon->dest != j){
        maillon = maillon->suiv;
    }
    // en sortie: soit maillon vaut NULL, soit maillon représente un arc (i, j)
    if (maillon == NULL) {
        return INFINITY;
    }
    return maillon->poids;
}
