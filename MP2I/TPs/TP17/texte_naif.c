#include <stdio.h>

#include "texte.h"

int recherche(char* texte, char* motif, int n, int p) {
    int j;
    for (int i = 0; i < n-p+1; i++) {
        j = 0;
        while (j < p && texte[i+j] == motif[j])
            j++;
        if (j == p)
            return i;
    }
    return -1;
}


int recherche_compte(char* texte, char* motif, int n, int p) {
    int count = 0;
    int j;
    for (int i = 0; i < n-p+1; i++) {
        j = 0;
        while (j < p && texte[i+j] == motif[j])
            j++;
        if (j == p)
            count++;
    }
    return count;
}
