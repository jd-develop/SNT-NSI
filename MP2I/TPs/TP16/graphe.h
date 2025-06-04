#ifndef GRAPHE_H
#define GRAPHE_H

#include "stoi.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// liste chaînée de couples (voisin, poids de l'arête)
struct adj {
    int dest; // sommet d'arrivée de l'arête;
    float poids; //poids de l'arête
    struct adj* suiv; // maillon suivant
};
typedef struct adj adj_t;

struct graphe {
    int n; // nombre de sommets;
    char** sommets; // sommets[i] contient le nom du sommet d'indice i
    adj_t** voisins; // voisins[i] contient la liste des voisins du sommet d'indice i
    stoi_t* indice; // indice[u] contient l'indice du sommet de nom u
};
typedef struct graphe graphe_t;

/* Affiche la liste des sommets de g, et pour chaque sommet u, la liste de ses arêtes */
void afficher(graphe_t* g);

/* Renvoie un booléen indiquant si (u, v) est un arc de g */
bool est_arc(graphe_t* g, char* u, char* v);

/* Crée un graphe possédant n sommets (les sommets stockés dans sommets)
 * sans arcs */
graphe_t* graphe_vide(char** sommets, int n);

/* Crée un arc (u, v) dans le graphe g, de poids w. (Si un arc (u, v) existe
 * déjà, le crée quand même) */
void ajouter_arc(graphe_t* g, char* u, char* v, float w);

/* Libère toute la mémoire allouée pour un graphe */
void graphe_free(graphe_t* g);

/* Renvoie le poids de l’arc (u, v), ou inf si l’arc n’existe pas */
float valeur_arc(graphe_t* g, char* u, char* v);

#endif
