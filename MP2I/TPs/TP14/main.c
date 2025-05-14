#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "grille.h"

/*
 * Renvoie le score d’un chemin, ou -1 si le chemin sort de la grille ou
 * n’arrive pas en bas à droite
 */
int valeur(grille_t* g, char* chemin) {
    int n = g->n;
    int m = g->m;

    int i = 0;
    int j = 0;
    int value = g->ordures[0][0];

    for (unsigned long int k = 0; k < strlen(chemin); k++) {
        if (chemin[k] == 'D')
            i++;
        else
            j++;
        if (i >= n || j >= m) {
            printf("%d %d\n", i, j);
            printf("Le chemin sort de la grille !\n");
            return -1;
        }
        value += g->ordures[i][j];
    }

    if (i != n-1 || j != m-1) {
        printf("Le chemin n’arrive pas en bas à droite !\n");
        return -1;
    }

    return value;
}


/* Renvoie un chemin aléatoire */
char* chemin_aleatoire(grille_t* g) {
    int n = g->n;
    int m = g->m;
    char* res = malloc((n+m-1)*sizeof(char));
    res[0] = '\0';

    int i = 0;
    int j = 0;
    int r = 0;

    while (i < n-1 && j < m-1) {
        r = rand() % 2;
        if (r == 0) {
            i++;
            strcat(res, "D");
        } else {
            j++;
            strcat(res, "R");
        }
    }

    /* On est arrivés soit à la dernière ligne, soit à la dernière colonne.
     * On finit jusqu’à arriver en bas à droite */
    while (i < n-1) {
        i++;
        strcat(res, "D");
    }
    while (j < m-1) {
        j++;
        strcat(res, "R");
    }
    return res;
}


/* Renvoie true s’il vaut mieux localement aller à droite depuis la case
 * (i, j), false s’il vaut mieux aller en bas */
bool choix_glouton(grille_t* g, int i, int j) {
    int n = g->n;
    int m = g->m;
    if (i == n-1)
        return true;
    else if (j == m-1)
        return false;

    return (g->ordures[i][j+1] > g->ordures[i+1][j]);
}


/* Renvoie le meilleur chemin localement */
char* chemin_glouton(grille_t* g) {
    int n = g->n;
    int m = g->m;
    char* res = malloc((n+m-1)*sizeof(char));
    res[0] = '\0';

    int i = 0;
    int j = 0;

    while (i != n-1 || j != m-1) {
        if (choix_glouton(g, i, j)) {
            j++;
            strcat(res, "R");
        } else {
            i++;
            strcat(res, "D");
        }
    }

    return res;
}


int max(int a, int b) {
    if (a < b)
        return b;
    return a;
}


/* Calcule et renvoie le tableau de programmation dynamique n×m correspondant
 * à la grille g. Note : le tableau est alloué sur le tas, il faudra le
 * libérer */
int** dechets_progdyn(grille_t* g) {
    int n = g->n;
    int m = g->m;
    int** res = malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        res[i] = malloc(m*sizeof(int));
    }

    res[0][0] = g->ordures[0][0];
    for (int i = 1; i < n; i++) {
        res[i][0] = res[i-1][0] + g->ordures[i][0];
    }
    for (int j = 1; j < m; j++) {
        res[0][j] = res[0][j-1] + g->ordures[0][j];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            res[i][j] = max(res[i-1][j], res[i][j-1]) + g->ordures[i][j];
        }
    }

    return res;
}


/* Reconstruit le chemin depuis le tableau de prog dyn D et affiche en fonction
 * de g la quantité totale de déchets ramassés */
char* reconstruction(int** D, grille_t* g) {
    int n = g->n;
    int m = g->m;

    char* res = malloc((n+m-1)*sizeof(char));
    res[n+m-2] = '\0';

    int i = n - 1;
    int j = m - 1;
    int v;
    int total = D[i][j];
    int index_in_res = n+m-3;

    while (i != 0 || j != 0) {
        v = D[i][j] - g->ordures[i][j];

        if (i != 0 && j != 0) {
            if (v == D[i-1][j]) {
                i--;
                res[index_in_res] = 'D';
            } else {
                j--;
                res[index_in_res] = 'R';
            }
        } else if (i == 0) {
            j--;
            res[index_in_res] = 'R';
        } else {
            i--;
            res[index_in_res] = 'D';
        }

        index_in_res--;
    }

    printf("%d\n", total);
    return res;
}


int main(int argc, char** argv){
    srand(time(NULL));

    assert(argc > 1);
    grille_t* g = lire_grille(argv[1]);

    afficher_grille(g);
    char* chemin_aleat = chemin_aleatoire(g);
    printf("Aléatoire : %s : %d\n", chemin_aleat, valeur(g, chemin_aleat));
    free(chemin_aleat);

    char* chemin_g = chemin_glouton(g);
    printf("Glouton : %s : %d\n", chemin_g, valeur(g, chemin_g));
    free(chemin_g);

    int** res_progdyn = dechets_progdyn(g);
    char* chemin_progdyn = reconstruction(res_progdyn, g);
    printf("Prog. dyn. : %s : %d\n", chemin_progdyn, res_progdyn[g->n-1][g->m-1]);
    free(chemin_progdyn);

    for (int i = 0; i < g->n; i++) {
        free(res_progdyn[i]);
    }
    free(res_progdyn);

    liberer_grille(g);
    return 0;
}
