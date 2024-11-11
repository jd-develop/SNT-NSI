#include <stdio.h>
#include <assert.h>

/* Renvoie la somme des entiers lus dans le fichier `nom_fichier`.
 * Précondition : `nom_fichier` ne doit contenir que des entiers.
 */
int somme(char* nom_fichier) {
    FILE* fp = fopen(nom_fichier, "r");
    assert(fp != NULL);
    int x = 0;
    int total = 0;
    int nb_lus = 0;
    while (nb_lus != EOF) {
        total += x;
        nb_lus = fscanf(fp, "%d", &x);
        if (nb_lus == 0)
            break;
    }
    return total;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Merci de donner un fichier comme argument.\n");
        return 1;
    }
    printf("%d\n", somme(argv[1]));
    return 0;
}
