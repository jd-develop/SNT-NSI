#include <stdio.h>
#include <stdlib.h>


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


/* affiche un tableau de taille n */
void print_tab(int* T, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", T[i]);
        if (i+1 != n) printf(", ");
    }
    printf("]\n");
}


int main() {
    int n;
    printf("Entrez une taille de tableau : ");
    scanf("%d", &n);
    int* tab = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Entrez l’élément d’incide %d : ", i);
        scanf("%d", &(tab[i]));
    }

    print_tab(tab, n);
    tri(tab, n);
    print_tab(tab, n);

    return 0;
}
