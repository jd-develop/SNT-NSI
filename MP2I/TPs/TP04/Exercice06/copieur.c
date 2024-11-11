#include <stdio.h>

int main(int argc, char* argv[]) {
    if (!(argc == 3)) {
        printf("Merci de donner deux noms de fichier comme arguments.\n");
        return 1;
    }

    FILE* fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        printf("Erreur lors de l’ouverture de %s.\n", argv[1]);
        return 1;
    }

    FILE* fp2 = fopen(argv[2], "w");
    if (fp2 == NULL) {
        printf("Erreur lors de l’ouverture de %s "
               "(permissions insuffisantes ?)\n", argv[2]);
        return 1;
    }

    char caractere_courant;
    int nb_lus = fscanf(fp1, "%c", &caractere_courant);
    while (nb_lus != EOF) {
        fprintf(fp2, "%c", caractere_courant);
        nb_lus = fscanf(fp1, "%c", &caractere_courant);
    }
    return 0;
}
