/* Ce fichier génère une formule modélisant le problème des N dames */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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


/*
 * Génère la formule unique modélisant le problème à n dames et le stock dans le
 * fichier `filename`.
 * Renvoie 0 en cas de succès, 1 en cas d’échec.
 */
int gen_formule_n_dames(int n, char* filename) {
    char** l = malloc(3*sizeof(char*));
    l[0] = contrainte_toutes_lignes(n);
    l[1] = contrainte_toutes_colonnes(n);
    l[2] = contrainte_toutes_diagonales(n);
    char* res = toutes(l, 3, -1);
    for (int i = 0; i < 3; i++)
        free(l[i]);
    free(l);

    int octets = strlen(res);

    FILE* fp = fopen(filename, "w");
    if (fp == NULL)
        return 1;

    fprintf(fp, "%s\n", res);
    free(res);
    fclose(fp);

    printf("Fichier %s créé (%d octets).\n", filename, octets+1);
    return 0;
}


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Merci de donner exactement un argument : n\n");
        return 1;
    }
    char* n_str = argv[1];
    char* endptr;

    long n = strtol(n_str, &endptr, 10);

    if (n <= 0 || strlen(endptr) != 0) {
        fprintf(stderr, "Erreur : n doit être un entier strictement positif\n");
        return 2;
    }

    char* filename = malloc((strlen(n_str)+11)*sizeof(char));
    sprintf(filename, "%ld_dames.txt", n);
    int res = gen_formule_n_dames(n, filename);
    if (res != 0) {
        fprintf(stderr, "Erreur d’ouverture du fichier %s\n", filename);
        return 3;
    }

    return 0;
}
