/* Ce fichier génère une formule modélisant le problème des N dames */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    char* res = exactement_une(l, n);
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

/*
 * Renvoie une formule exprimant la contrainte sur la diagonale i dans le
 * problème des n-dames. Les diagonales sont comptées ainsi :
 *
 *    DESC    ASC
 *    45678   01234
 *    34567   12345
 *    23456   23456
 *    12345   34567
 *    01234   45678
 *
 *    3456    0123
 *    2345    1234
 *    1234    2345
 *    0123    3456
 *
 *    12      01
 *    01      12
 *
 * Ainsi, i est compris entre 0 et 2n-2 inclus, où n est la taille de la grille.
 *
 * Le booléen « asc » permet d’indiquer s’il faut exprimer la formule sur la
 * i-ième diagonale ascendante (true) ou descendante (false) (voir schémas plus
 * haut)
 */
char* contrainte_une_diagonale(int i, int n, bool asc) {
    char** l = malloc(n*sizeof(char*));

    int ligne;
    if (asc) {
        ligne = (i < n) ? i : n-1;
    } else {
        ligne = (i < n) ? n-i-1 : 0;
    }
    int colonne = (i < n) ? 0 : i-n+1;
    int vraie_longueur_liste = 0;

    for (int j = 0; ligne < n && colonne < n && ligne >= 0 && colonne >= 0; j++)
    {
        l[j] = variable(ligne, colonne);
        vraie_longueur_liste++;
        if (asc) {
            ligne--;
        } else {
            ligne++;
        }
        colonne++;
    }
    char* res = au_plus_une(l, vraie_longueur_liste);
    for (int j = 0; j < vraie_longueur_liste; j++) {
        free(l[j]);
    }
    free(l);
    return res;
}


/*
 * Renvoie une formule exprimant la contrainte sur toutes les diagonales dans
 * le problème des n dames
 */
char* contrainte_toutes_diagonales(int n) {
    char** l = malloc(2*(2*n-1)*sizeof(char*));
    for (int i = 0; i < 2*(2*n-1); i += 2) {
        l[i] = contrainte_une_diagonale(i/2, n, true);
        l[i+1] = contrainte_une_diagonale(i/2, n, false);
    }
    char* res = toutes(l, 2*(2*n-1), -1);
    for (int i = 0; i < 2*(2*n-1); i++) {
        free(l[i]);
    }
    free(l);
    return res;
}


int main() {
    printfree(contrainte_toutes_lignes(3));

    printfree(contrainte_toutes_colonnes(3));

    printfree(contrainte_toutes_diagonales(3));

    /*
    printf("\n");

    for (int i = 0; i <= 2*2-2; i++) {
        printfree(contrainte_une_diagonale(i, 2, true));
    }

    printf("\n");

    for (int i = 0; i <= 2*3-2; i++) {
        printfree(contrainte_une_diagonale(i, 3, true));
    }

    printf("\n");

    for (int i = 0; i <= 2*4-2; i++) {
        printfree(contrainte_une_diagonale(i, 4, true));
    }

    printf("\n");

    for (int i = 0; i <= 2*5-2; i++) {
        printfree(contrainte_une_diagonale(i, 5, true));
    }

    printf("\n");

    for (int i = 0; i <= 2*6-2; i++) {
        printfree(contrainte_une_diagonale(i, 6, true));
    }
    */

    return 0;
}
