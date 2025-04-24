/* Ce fichier génère une formule modélisant le problème des N dames */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* Renvoie la chaîne X_i_j */
char* variable(int i, int j) {
    char* buffer = malloc(100*sizeof(char));
    sprintf(buffer, "X_%d_%d", i, j);
    return buffer;
}

/*
 * Renvoie une formule exprimant la contrainte sur la ligne i dans le problème
 * des n dames
 */
char* contrainte_une_ligne(int i, int n) {
    char** l = malloc(n*sizeof(char*));
    for (int j = 0; j < n; j++) {
        l[j] = variable(i, j);
    }
    char* res = au_plus_une(l, n);
    for (int j = 0; j < n; j++) {
        free(l[j]);
    }
    free(l);
    return res;
}

/*
 * Renvoie une formule exprimant la contrainte sur toutes les lignes dans
 * le problème des n dames
 */
char* contrainte_toutes_lignes(int n) {
    char** l = malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++) {
        l[i] = contrainte_une_ligne(i, n);
    }
    char* res = toutes(l, n, -1);
    for (int i = 0; i < n; i++) {
        free(l[i]);
    }
    free(l);
    return res;
}

/*
 * Renvoie une formule exprimant la contrainte sur la colonne i dans le problème
 * des n dames
 */
char* contrainte_une_colonne(int i, int n) {
    char** l = malloc(n*sizeof(char*));
    for (int j = 0; j < n; j++) {
        l[j] = variable(j, i);
    }
    char* res = au_plus_une(l, n);
    for (int j = 0; j < n; j++) {
        free(l[j]);
    }
    free(l);
    return res;
}

/*
 * Renvoie une formule exprimant la contrainte sur toutes les colonnes dans
 * le problème des n dames
 */
char* contrainte_toutes_colonnes(int n) {
    char** l = malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++) {
        l[i] = contrainte_une_colonne(i, n);
    }
    char* res = toutes(l, n, -1);
    for (int i = 0; i < n; i++) {
        free(l[i]);
    }
    free(l);
    return res;
}

/* TODO diagonale */

int main() {
    printf("%s\n", contrainte_toutes_lignes(3));
    printf("%s\n", contrainte_toutes_colonnes(3));
    return 0;
}
