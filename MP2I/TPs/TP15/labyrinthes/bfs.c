#include <stdio.h>

#include "bfs.h"
#include "graphe.h"


file_t* file_vide(int n) {
    file = malloc(sizeof(file_t));
    tableau = malloc(n*sizeof(unsigned int));
    for (int i = 0; i < n; i++) {
        tableau[i] = 0;
    }
    file->file = tableau
    return file;
}

void free_file(file_t* file) {
    
}


int* bfs(graphe_t* g, unsigned int s) {
    int n = g->n;
    int* d[n];
    int* pred = malloc(n*sizeof(int));

    for (int i = 0; i < n; i++) {
        d[i] = 0;
        pred[i] = 0;
    }
    // TODO
    return 0;
}
