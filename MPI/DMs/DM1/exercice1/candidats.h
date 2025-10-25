#ifndef CANDIDATS_H
#define CANDIDATS_H

#include "database.h"

typedef struct s_cellule* candidats;
struct s_cellule {
    int       indice;              /* indice du point dans le jeu de donnée */
    double    distance;            /* distance au point de recherche */
    candidats next;
};


candidats create_list(int ind, double dist);
void delete_list(candidats lc);
void print_list(candidats l);
void print_list_newline(candidats l);
int insertion_list(
    candidats* pl, int r, int k, database db, int i, vector input
);

#endif
