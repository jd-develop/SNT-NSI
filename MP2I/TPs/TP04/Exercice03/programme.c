#include <stdio.h>
#include <assert.h>

/* Renvoie la somme des deux premiers entiers lus dans le fichier `nom_fichier`.
 * Précondition : `nom_fichier` doit commencer par au moins deux entiers
 */
int somme2(char* nom_fichier) {
    FILE* fp = fopen(nom_fichier, "r");
    assert(fp != NULL);
    int x, y;
    int nb_lus = fscanf(fp, "%d %d", &x, &y);
    assert(nb_lus == 2);
    fclose(fp);
    return x+y;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr,
            "Merci de donner comme argument le nom d’un fichier comportant "
            "deux entiers\n"
        );
        return 1;
    }
    printf("%d\n", somme2(argv[1]));
    return 0;
}
