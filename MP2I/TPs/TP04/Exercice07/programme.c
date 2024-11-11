#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

/* Renvoie true si les tableaux t1 et t2, tous deux de taille n⩾0, contiennent
 * les mêmes valeurs, false sinon
 */
bool egaux(int* t1, int* t2, int n) {
    for (int i = 0; i < n; i++) {
        if (t1[i] != t2[i]) {
            return false;
        }
    }
    return true;
}

/* Crée et renvoie un tableau de n zéros dans le tas. */
int* zeros(int n) {
    int* tab = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        tab[i] = 0;
    }
    return tab;
}

/* Crée et renvoie un tableau de n false puis de m true dans le tas. */
bool* zeros_uns(int n, int m) {
    bool* tab = malloc((n+m)*sizeof(bool));
    for (int i = 0; i < n; i++) {
        tab[i] = false;
    }
    for (int i = 0; i < m; i++) {
        tab[n+i] = true;
    }
    return tab;
}

int main() {
    int tab1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tab2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tab3[10] = {1, 2, 3, 4, 5, 5, 7, 8, 9, 10};
    assert(egaux(tab1, tab2, 10));
    assert(!egaux(tab1, tab3, 10));
    assert(!egaux(tab2, tab3, 10));
    assert(egaux(tab1, tab3, 5));
    assert(egaux(tab1, tab3, 0));

    int* tab_5entiers = malloc(5*sizeof(int));
    for (int i = 0; i < 5; i++) {
        tab_5entiers[i] = i;
    }
    int tab4[5] = {0, 1, 2, 3, 4};
    assert(egaux(tab_5entiers, tab4, 5));
    free(tab_5entiers);

    int zeros_reference[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int* zeros_1 = zeros(10);
    int* zeros_2 = zeros(5);
    assert(egaux(zeros_1, zeros_reference, 10));
    assert(egaux(zeros_2, zeros_reference, 5));
    assert(egaux(zeros_2, zeros_1, 5));
    free(zeros_2);
    free(zeros_1);

    for (int i = 0; i < 10; i++) {
        bool* zeros_uns_1 = zeros_uns(i, 10-i);
        for (int j = 0; j < i; j++) {
            assert(!zeros_uns_1[j]);
        }
        for (int j = i; j < 10; j++) {
            assert(zeros_uns_1[j]);
        }
        free(zeros_uns_1);
    }
}
