//#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pile.h"

int taille_stable(char* polymere) {
    pile_t* p = pile_vide();

    int sommet_pile;
    char c;
    char C;
    for (int i = 0; i < (int)strlen(polymere); i++) {
        printf("%d\n", i);
        c = polymere[i];
        if (est_vide(p)) {
            empiler(p, c);
            continue;
        }
        sommet_pile = depiler(p);

        if ('a' <= c && c <= 'z')
            C = c-'a' + 'A';
        else
            C = c-'A' + 'a';

        if (C != sommet_pile) {
            empiler(p, sommet_pile);
            empiler(p, c);
        }
    }
    //print_pile_char(p);
    return taille_pile(p);
}


int partie_2(char* polymere) {
    char nouveau_polymere[3000000];
    int j;
    int min = taille_stable(polymere);
    int n;
    for (char c = 'a'; c <= 'z'; c++) {
        j = 0;
        for (int i = 0; i < (int)strlen(polymere); i++) {
            if (polymere[i] != c && polymere[i] != c-'a'+'A') {
                nouveau_polymere[j] = polymere[i];
                j++;
            }
        }
        nouveau_polymere[j] = 0;
        n = taille_stable(nouveau_polymere);
        if (n < min)
            min = n;
    }
    return min;
}


int main() {
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Impossible d’ouvrir le fichier");
        return 1;
    }
    char polymere[3000000];
    if (fscanf(fp, "%s", polymere) == 0) {
        printf("Impossible de lire le fichier");
        return 2;
    }
    printf("%d\n", taille_stable(polymere));
    printf("%d\n", partie_2(polymere));

}
