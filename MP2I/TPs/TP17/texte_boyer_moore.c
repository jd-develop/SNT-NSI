#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "texte.h"

int* construire_d(char* m) {
    int n = strlen(m);
    int* dm = malloc(256*sizeof(int));
    for (int i = 0; i < 256; i++) {
        dm[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        dm[(int)(m[i])] = i;
    }

    return dm;
}


int max(int a, int b) {
    if (a < b)
        return b;
    return a;
}


/* si compte = true, c’est recherche_compte, sinon c’est recherche */
int _recherche(char* t, char* m, int n, int p, bool compte) {
    int i = 0;
    int j;
    int total = 0;

    int* dm = construire_d(m);

    while (i < n-p+1) {
        j = p-1;
        while (j >= 0 && t[i+j] == m[j]) {
            j--;
        }
        if (j == -1) {
            if (compte)
                total++;
            else
                return i;
        }
        i += max(1, j-dm[(int)(t[i+j])]);
    }

    free(dm);
    if (compte)
        return total;
    else
        return -1;
}


int recherche(char* t, char* m, int n, int p) {
    return _recherche(t, m, n, p, false);
}


int recherche_compte(char* t, char* m, int n, int p) {
    return _recherche(t, m, n, p, true);
}

