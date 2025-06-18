#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "texte.h"

#define LEN_CTFR 2500
#define LEN_ADN 30853080
#define LEN_VERNE 902909


char* lire(char* filename, int len) {
    char* contenu = malloc(len*sizeof(char));

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Erreur lors de la lecture du fichier");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        fscanf(fp, "%c", &(contenu[i]));
    }

    fclose(fp);

    return contenu;
}


int main () {
    char* ctfr = lire("ctfr.txt", LEN_CTFR);
    char* adn = lire("ADN.txt", LEN_ADN);
    char* verne = lire("vingt_mille_lieues.txt", LEN_VERNE);
    clock_t debut, fin;
    char* motifs_verne[5] = {
        "Nemo",
        "Nautilus",
        "tératologique",
        "quoicoubaka",
        "anticonstitutionnellement"
    };

    printf("Recherche de CTFR dans l’ADN…\n");
    debut = clock();
    printf("%d\n", recherche(adn, ctfr, LEN_ADN, LEN_CTFR));
    fin = clock();
    printf("Temps : %f\n", (float) (fin-debut)/CLOCKS_PER_SEC);

    printf("Recherche de Motifs dans Vingt Mille Lieues sous les Mers…\n");
    debut = clock();
    for (int i = 0; i < 5; i++) {
        printf(
            "%s : %d\n",
            motifs_verne[i],
            recherche_compte(
                verne, motifs_verne[i],
                LEN_VERNE, strlen(motifs_verne[i])
            )
        );
    }
    fin = clock();
    printf("Temps : %f\n", (float) (fin-debut)/CLOCKS_PER_SEC);

    free(ctfr);
    free(adn);
    free(verne);

    return 0;
}
