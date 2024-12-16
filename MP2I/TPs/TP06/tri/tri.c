#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

/*
 * Renvoie true si le tableau T de longueur n est trié dans l’ordre croissant,
 * false sinon
 */
bool est_trie(int* T, int n) {
    for (int i = 0; i < n-1; i++) {
        if (T[i] > T[i+1]) return false;
    }
    return true;
}

/* affiche le tableau T de taille n */
void print_tab(int* T, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", T[i]);
        if (i+1 != n) printf(", ");
    }
    printf("]\n");
}

/*
 * Trie en place le tableau T de taille n selon l’algorithme du tri par
 * insertion.
 */
void tri(int* T, int n) {
    int j;
    int temp;
    for (int i = 0; i < n; i++) {
        j = i;
        while (j > 0 && T[j-1] > T[j]) {
            temp = T[j-1];
            T[j-1] = T[j];
            T[j] = temp;
            j--;
        }
    }
}

/*
 * Réalise une partition de T tableau de taille n entre a et b inclus
 * (0 ⩽ a ⩽ b ⩽ n-1).
 * L’ancienne valeur de T[a] est maintenant à un indice j tel que les éléments
 * de T[a..b] inférieurs à T[j] soient avant j, et ceux qui sont supérieurs
 * soient à droite. Renvoie le nouvel indice j de T[a]
 */
int partition_entre(int* T, int n, int a, int b) {
    assert(0 <= a && a <= b && b <= n-1);
    int i = a+1;
    int s = b;
    int temp;

    while (i <= s) {
        if (T[i] <= T[a]) {
            i++;
        } else {
            temp = T[s];
            T[s] = T[i];
            T[i] = temp;
            s--;
        }
    }

    temp = T[a];
    T[a] = T[s];
    T[s] = temp;
    return s;
}

/*
 * Trie en place le tableau T de taille n entre les indices a et b inclus
 * (0 ⩽ a, b ⩽ n-1), selon l’algorithme du tri rapide
 */
void tri_rapide(int* T, int n, int a, int b) {
    assert(0 <= a && b <= n-1);
    if (a >= b) return;

    int pivot = partition_entre(T, n, a, b);
    tri_rapide(T, n, a, pivot-1);
    tri_rapide(T, n, pivot+1, b);
}

/* génère 20 tableaux aléatoires de taille n, et renvoie le temps moyen écoulé
 * pour trier un tableau avec tri_rapide */
float test_tri_rapide(int n) {
    int** tableaux = malloc(20*sizeof(int*));
    for (int i = 0; i < 20; i++) {
        tableaux[i] = malloc(n*sizeof(int));
        for (int j = 0; j < n; j++) {
            tableaux[i][j] = rand()%100;
        }
    }

    clock_t debut = clock();
    for (int i = 0; i < 20; i++) {
        tri_rapide(tableaux[i], n, 0, n-1);
    }
    clock_t fin = clock();
    float duree = (float) (fin-debut)/CLOCKS_PER_SEC;

    for (int i = 0; i < 20; i++) {
        assert(est_trie(tableaux[i], n));
        free(tableaux[i]);
    }
    free(tableaux);

    return duree / 20;
}

/* génère 20 tableaux aléatoires de taille n, et renvoie le temps moyen écoulé
 * pour trier un tableau avec le tri par insertion */
float test_tri_insertion(int n) {
    int** tableaux = malloc(20*sizeof(int*));
    for (int i = 0; i < 20; i++) {
        tableaux[i] = malloc(n*sizeof(int));
        for (int j = 0; j < n; j++) {
            tableaux[i][j] = rand();
        }
    }

    clock_t debut = clock();
    for (int i = 0; i < 20; i++) {
        tri(tableaux[i], n);
    }
    clock_t fin = clock();
    float duree = (float) (fin-debut)/CLOCKS_PER_SEC;

    for (int i = 0; i < 20; i++) {
        assert(est_trie(tableaux[i], n));
        free(tableaux[i]);
    }
    free(tableaux);

    return duree / 20;
}

int main() {
    srand(time(NULL));
    FILE* fp = fopen("valeurs.txt", "w");
    for (int i = 100; i <= 4000; i += 100) {
        fprintf(fp, "%d %f %f\n", i, test_tri_rapide(i), test_tri_insertion(i));
    }

    /* int n;
    printf("Entrez une taille de tableau : ");
    scanf("%d", &n);
    int* tab = malloc(n*sizeof(int));
    int* tab2 = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Entrez l’élément d’incide %d : ", i);
        scanf("%d", &(tab[i]));
        tab2[i] = tab[i];
    }

    print_tab(tab, n);
    tri(tab, n);
    tri_rapide(tab2, n, 0, n-1);
    print_tab(tab, n);
    print_tab(tab2, n);

    free(tab);
    free(tab2); */

    return 0;
}
