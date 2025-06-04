#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <stdbool.h>

/*
 * Calcule la longueur totale du chemin `chemin` de longueur `n` dans le graphe
 * `g`. Renvoie +inf si le chemin est invalide.
 */
float longueur(graphe_t* g, char** chemin, int n);

/* Cherche et renvoie un entier i entre 0 inclus et n exclus tel que q[i] = 1
 * pour lequel d[i] est minimal. Avant de renvoyer l’entier, q[i] est changé
 * à 0. Si q est vide (tous les éléments sont faux), renvoie -1 */
int extraire_min(float* d, bool* q, int n);

/* Effectue l’algorithme de Dijkstra depuis le sommet s dans le graphe g et
 * renvoie l’arborescence du parcours sous la forme du tableau des prédeceseurs
 */
int* dijkstra(graphe_t* g, char* s);

/* Renvoie le plus court chemin de s à t sous la forme d’un tableau dont s
 * et t sont le premier et le dernier élément. */
char** pcc(graphe_t* g, char* s, char* t);

#endif
