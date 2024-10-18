/*
 * Simule une petite mémoire RAM. Ne peut stocker que des entiers. Permet
 * d’accéder à une valeur à partir de son adresse mémoire, de stocker une
 * valeur à une adresse mémoire, et de faire une addition.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


/*
 * Affiche la case numéro i de la mémoire (tableau ram), de taille taille.
 * Si la valeur est en-dehors de la mémoire ou que l’utilisateur n’a jamais
 * écrit dans cette case mémoire (i.e. l’élément correspondant dans deja_vu est
 * à false), affiche une erreur.
 */
void affiche_case_memoire(int i, int[] ram, bool[] deja_vu, int taille) {
    if (i < 0 || i >= taille) {
        printf("\033[31m"); // rouge
        printf("Segmentation fault");
        printf("\033[0m\n"); // réinitialiser la couleur
        return;
    } else if (!deja_vu[i]) {
        printf("\033[31m"); // rouge
        printf("Erreur : aucune valeur n’a été écrite à cette adresse");
        printf("\033[0m\n"); // réinitialiser la couleur
        return;
    }
}

int main() {
    int[1024] ram;
    bool[1024] deja_vu; // true si une valeur a déjà été écrite, false sinon
    int taille;

    printf("Choisir la taille de la mémoire : ");
    assert(scanf("%d", &taille) != 0);
    assert(0 < taille <= 1024);
    while (true) {
    }

    return 0;
}

