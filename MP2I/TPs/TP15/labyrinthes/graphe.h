#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// liste chainée pour stocker les voisins d'un sommet
struct adj {
    unsigned int voisin;
    struct adj* suiv;
};
typedef struct adj adj_t;

struct graphe {
    int n;
    adj_t** lv; // listes des voisins
};
typedef struct graphe graphe_t;

/* Affiche chaque sommet du graphe suivi de la liste de ses voisins */
void print_graphe(graphe_t* g);

/* Libère la mémoire allouée pour un graphe */
void free_graphe(graphe_t* g);

/* Crée un graphe avec n sommets et aucune arête */
graphe_t* graphe_vide(int n);

/* Ajoute l’arête (u, v) au graphe. Si oriente est faux, ajoute également
 * l’arête (v, u). */
void ajouter(graphe_t* g, unsigned int u, unsigned int v, bool oriente);

/* Lit le graphe stocké dans le fichier filename */
graphe_t* lire_graphe(char* filename);

#endif
