#include "graphe.h"
#include "parser.h"
#include "dijkstra.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



// int main(int argc, char const *argv[]) {
int main() {
    // graphe exemple du sujet
    int n = 4;
    char** sommets = malloc(n*sizeof(char*));
    sommets[0] = strdup("CHAT"); // strdup fait un malloc ET un strcpy 
    sommets[1] = strdup("CHIEN");
    sommets[2] = strdup("OISEAU");
    sommets[3] = strdup("VACHE");

    graphe_t* g = graphe_vide(sommets, n);

    ajouter_arc(g, "CHAT", "CHIEN", 1);

    ajouter_arc(g, "CHIEN", "OISEAU", 7);
    ajouter_arc(g, "CHIEN", "VACHE", 3);

    ajouter_arc(g, "OISEAU", "CHAT", 1);

    ajouter_arc(g, "VACHE", "OISEAU", 2);

    assert(est_arc(g, "CHIEN", "OISEAU"));
    assert(!est_arc(g, "OISEAU", "CHIEN"));

    afficher(g);

    printf("%f\n", longueur(g, sommets, 4));  // infinity
    printf("%f\n", longueur(g, sommets, 3));  // 8

    char* depart = sommets[0];
    char* arrivee = sommets[2];
    char** pcc1 = pcc(g, depart, arrivee);
    if (pcc1 == NULL) {
        printf("Pas de chemin !\n");
    } else {
        int i = 0;
        while (pcc1[i] != arrivee) {
            printf("%s\n", pcc1[i]);
            i++;
        }
        printf("%s\n", pcc1[i]);
        free(pcc1);
    }

    graphe_free(g);

    for (int i = 0; i < n; i++) {
        free(sommets[i]);
    }
    free(sommets);

    return 0;
}
