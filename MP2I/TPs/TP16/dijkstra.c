#include <stdio.h>
#include "graphe.h"

float longueur(graphe_t* g, char** chemin, int n) {
    float total = 0.0;
    for (int i = 1; i < n; i++) {
        total += valeur_arc(g, chemin[i-1], chemin[i]);
    }
    return total;
}
