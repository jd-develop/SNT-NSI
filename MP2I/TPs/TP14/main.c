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
    char* res = malloc((n+m+1)*sizeof(char));
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
    char* res = malloc((n+m+1)*sizeof(char));
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


/* Calcule et renvoie le tableau de programmation dynamique n×m correspondant
 * à la grille g */
int** dechets_progdyn(grid_t* g) {
    int n = g->n;
    int m = g->m;
    int** res = malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        res[i] = malloc(m*sizeof(int));
    }

    res[0][0] = g->ordures[0][0];
}


int main(int argc, char** argv){
    srand(time(NULL));

    assert(argc > 1);
    grille_t* g = lire_grille(argv[1]);

    afficher_grille(g);
    char* chemin_aleat = chemin_aleatoire(g);
    printf("Aléatoire : %s : %d\n", chemin_aleat, valeur(g, chemin_aleat));

    char* chemin_g = chemin_glouton(g);
    printf("Glouton : %s : %d\n", chemin_g, valeur(g, chemin_g));

    liberer_grille(g);
    return 0;
}
