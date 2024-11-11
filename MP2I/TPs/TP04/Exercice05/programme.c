#include <stdio.h>
#include <assert.h>

/* Compte le nombre d’entiers strictement positifs avant de lire un zéro dans
 * le fichier `filename`. Saute les entiers négatifs sans les compter. Renvoie
 * -1 si tout le fichier a été lu sans trouver de zéros. Renvoie -2 si une
 *  erreur est survenue lors de l’ouverture du fichier.
 * Précondition : `filename` doit être uniquement composé d’entiers
 */
int premier_zero(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return -2;
    }
    int compte = -1;
    int entier_courant = 1;
    int nb_lus = 1;
    while (nb_lus != EOF && entier_courant != 0) {
        if (entier_courant > 0)
            compte++;
        nb_lus = fscanf(fp, "%d", &entier_courant);
    }
    if (entier_courant != 0) {
        return -1;
    }
    return compte;
}

int main(int argc, char* argv[]) {
    assert(premier_zero("fichier_inexistant") == -2);
    assert(premier_zero("-1") == -1);
    assert(premier_zero("0") == 0);
    assert(premier_zero("1") == 1);
    assert(premier_zero("2") == 2);
    assert(premier_zero("3") == 3);
    assert(premier_zero("4") == 4);

    if (argc <= 1) {
        fprintf(stderr, "Merci de donner au moins un fichier comme argument\n");
        return -3;
    }
    printf("%d\n", premier_zero(argv[1]));
    return 0;
}
