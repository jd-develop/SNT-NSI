#ifndef BFS_H
#define BFS_H
#include <stdbool.h>
#include "graphe.h"

typedef struct {
    unsigned int* file;
    int tete;
    int queue;
} file_t;

/* Crée et renvoie une file vide de taille n */
file_t* file_vide(int n);

/* Enfile l’élément element dans la file file */
void enfiler(file_t* file, unsigned int element);

/* Défile et renvoie un élément de la file file */
unsigned int defiler(file_t* file);

/* Renvoie true si la file file est vide */
bool est_vide(file_t* file);

/* Libère l’espace mémoire utilisé pour file */
void free_file(file_t* file);

/* Applique un parcours en largeur et renvoie l’arborescence construite */
int* bfs(graphe_t* g, unsigned int s);

#endif
