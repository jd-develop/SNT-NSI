#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

/* calcule la somme des éléments de tab, tableau de taille n */
int somme(int* tab, int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += tab[i];
    }
    return res;
}

/* calcule la somme des éléments de tab, tableau de taille n */
float somme_float(float* tab, int n) {
    float res = 0;
    for (int i = 0; i < n; i++) {
        res += tab[i];
    }
    return res;
}

/* affiche toutes les cases du tableau tab de taille n, sous la forme :
 * a, b, c, d
 */
void affiche_tab(int* tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", tab[i]);
        if (i < n-1)
            printf(", ");
    }
    printf("\n");
}

/* affiche toutes les cases du tableau tab de taille n, sous la forme :
 * a, b, c, d
 */
void affiche_tab_float(float* tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f", tab[i]);
        if (i < n-1)
            printf(", ");
    }
    printf("\n");
}

/* remplit les n premières cases du tableau T de taille ⩾ n avec des valeurs
 * aléatoires comprises entre -10 et 10. On suppose que la graines des nombres
 * aléatoires a été spécifiée avant l’exécution de cette fonction.
 */
void remplit_aleatoirement_tab(int* T, int n) {
    for (int i = 0; i < n; i++) {
        T[i] = rand() % 21 - 10;
    }
}

/* remplit les n+1 premières cases de U avec, pour chaque case i, la somme des
 * i premières cases de T
 */
void somme_cumulative(float* T, float* U, int n) {
    for (int i = 0; i <= n; i++)
        U[i] = somme_float(T, i);
}

int main() {
    srand(time(NULL));

    int t[6] = {2, 3, 5, 1, -3, 3};
    int somme_t = somme(t, 6);
    assert(somme_t == 11);
    printf("%d\n", somme_t);
    affiche_tab(t, 6);

    int t_aleat[10];
    remplit_aleatoirement_tab(t_aleat, 10);
    affiche_tab(t_aleat, 10);

    float tf[10] = {-90.9, 8.3, 9.1, -7.9, 10.0, 10.4, 11.0, 10.0, 10.0, 30.0};
    float u[11];
    somme_cumulative(tf, u, 10);
    assert(u[0] == 0);
    affiche_tab_float(u, 11);

    return 0;
}
