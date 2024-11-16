#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>


/* Crée et renvoie une matrice nulle de dimensions n×m */
int** zeros(int n, int m) {
    int** mat = malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = malloc(m*sizeof(int));
        for (int j = 0; j < m; j++) {
            mat[i][j] = 0;
        }
    }
    return mat;
}

/* Crée et renvoie une matrice de dimensions n×m dont chaque valeur est un
 * nombre aléatoire entre a et b
 */
int** rand_mat(int n, int m, int a, int b) {
    int** mat = zeros(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat[i][j] = rand() % (b-a+1) + a;
        }
    }
    return mat;
}

/* Libère la mémoire allouée pour une matrice g de n lignes */
void free_mat(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(g[i]);
    }
    free(g);
}

/* renvoie le nombre de chifres dans l’écriture en base 10 de n */
int nb_chiffres(int n) {
    if (n == 0)
        return 1;
    int longueur = log10(abs(n))+1;
    if (n < 0)
        longueur++;
    return longueur;
}

/* Affiche le contenu d’une matrice g de dimensions n×m */
void print_mat(int** g, int n, int m) {
    int* taille_max_nombre_par_colonne = malloc(m*sizeof(int));
    int max;
    int long_actuelle;
    for (int j = 0; j < m; j++) {
        max = nb_chiffres(g[0][j]);
        for (int i = 0; i < n; i++) {
            long_actuelle = nb_chiffres(g[i][j]);
            if (long_actuelle > max) {
                max = long_actuelle;
            }
        }
        taille_max_nombre_par_colonne[j] = max;
    }
    for (int i = 0; i < n; i++) {
        if (i == 0)
            printf("⎡ ");
        else if (i == n-1)
            printf("⎣ ");
        else
            printf("⎢ ");

        for (int j = 0; j < m; j++) {
            int taille_nombre = nb_chiffres(g[i][j]);
            int max_colonne = taille_max_nombre_par_colonne[j];
            int espaces_a_rajouter = max_colonne - taille_nombre;
            for (int _ = 0; _ < espaces_a_rajouter; _++) {
                printf(" ");
            }
            printf("%d ", g[i][j]);
        }

        if (i == 0)
            printf("⎤\n");
        else if (i == n-1)
            printf("⎦\n");
        else
            printf("⎥\n");
    }
    free(taille_max_nombre_par_colonne);
}

/* renvoie la somme des deux matrices g1 et g2 de taille n×m */
int** somme_matrices(int** g1, int** g2, int n, int m) {
    int** somme = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        somme[i] = malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            somme[i][j] = g1[i][j] + g2[i][j];
        }
    }
    return somme;
}

/* renvoie le produit de deux matrices g1 de taille l×m et g2 de taille m×n */
int** produit_matrices(int** g1, int** g2, int l, int m, int n) {
    int** produit = malloc(l * sizeof(int*));
    for (int i = 0; i < l; i++) {
        produit[i] = malloc(n*sizeof(int));
        for (int j = 0; j < n; j++) {
            produit[i][j] = 0;
            for (int k = 0; k < m; k++) {
                produit[i][j] += g1[i][k] * g2[k][j];
            }
        }
    }
    return produit;
}

int main() {
    srand(time(NULL));
    int** mat_rand = rand_mat(3, 4, -190, 19);
    int** mat_rand2 = rand_mat(3, 4, 0, 100);
    int** somme = somme_matrices(mat_rand, mat_rand2, 3, 4);

    print_mat(mat_rand, 3, 4);
    printf("+\n");
    print_mat(mat_rand2, 3, 4);
    printf("=\n");
    print_mat(somme, 3, 4);

    free_mat(mat_rand, 3);
    free_mat(mat_rand2, 3);
    free_mat(somme, 3);

    printf("\n");

    mat_rand = rand_mat(2, 5, -190, 19);
    mat_rand2 = rand_mat(5, 3, 0, 100);
    int** produit = produit_matrices(mat_rand, mat_rand2, 2, 5, 3);

    print_mat(mat_rand, 2, 5);
    printf("*\n");
    print_mat(mat_rand2, 5, 3);
    printf("=\n");
    print_mat(produit, 2, 3);

    free_mat(mat_rand, 2);
    free_mat(mat_rand2, 5);
    free_mat(produit, 2);

    return 0;
}
