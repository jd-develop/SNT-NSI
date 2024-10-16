/*
 * Programme du jeu du tri : on affiche un tableau d’entiers à l’utilisateur,
 * qui doit le trier dans l’ordre croissant en un minimum de coups, en
 * échangeant successivement des cases adjacentes
 */
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_MAXIMUM 1000

/* remplit le tableau tab de longeur n de nombres aléatoires entre 0 et 100 */
void remplir_tab_aleat(int* tab, int n) {
    for (int i = 0; i < n; i++)
        tab[i] = rand() % 101;
}

/* teste la fonction remplir_tab_aleat */
void test_remplir_tab_aleat() {
    int tab[10];
    remplir_tab_aleat(tab, 10);
    for (int i = 0; i < 10; i++)
        assert(0 <= tab[i] && tab[i] <= 100);
}

/* affiche le tableau tab de longueur n sous la forme [a, b, c, d, …] */
void affiche(int* tab, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", tab[i]);
        // si ce n’est pas le dernier élément, on veut afficher une virgule
        if (i < n-1)
            printf(", ");
    }
    printf("]\n");
}

/*
 * renvoie true si tab de longeur n est trié dans l’ordre croissant, false
 * sinon
 */
bool est_trie(int* tab, int n) {
    for (int i = 1; i < n; i++)
        if (tab[i-1] > tab[i])
            /*
             * 2 éléments sont dans le mauvais ordre : le tableau n’est
             * pas trié
             */
            return false;
    return true;
}

/* teste la fonction est_trie */
void test_est_trie() {
    int tab1[1] = {5};
    int tab2[2] = {5, 5};
    int tab3[2] = {5, 4};
    int tab4[2] = {4, 5};

    int tab5[10] = {1, 8, 9, 78, 90, 100, 107, 890, 1000, 8900};
    int tab6[10] = {1, 8, 9, 78, 9, 100, 107, 890, 1000, 8900};
    int tab7[10] = {9, 8, 9, 78, 90, 100, 107, 890, 1000, 8900};
    int tab8[10] = {1, 8, 9, 78, 90, 100, 107, 890, 1000, 0};

    assert(est_trie(tab1, 1));
    assert(est_trie(tab2, 2));
    assert(!est_trie(tab3, 2));
    assert(est_trie(tab4, 2));
    assert(est_trie(tab5, 10));

    assert(!est_trie(tab6, 10));
    assert(est_trie(tab6, 4));
    assert(est_trie(&(tab6[4]), 5));

    assert(!est_trie(tab7, 10));
    assert(est_trie(tab7, 1));

    assert(!est_trie(tab8, 10));
    assert(est_trie(tab8, 9));
    assert(est_trie(&(tab8[9]), 1));
}

/* exécute le jeu */
void jeu() {
    // boucle du jeu
    int coups = 0;
    int tab[TAILLE_MAXIMUM];
    int taille;

    printf("Bienvenue au jeu du tri. ");
    printf("Choisissez la taille du tableau : ");
    assert(scanf("%d", &taille) != 0);
    while (taille <= 1 || taille > TAILLE_MAXIMUM) {
        printf("\033[31m"); // rouge
        printf(
            "Erreur : la taille doit être comprise entre 2 et 1000 inclus."
        );
        printf("\033[0m\n"); // réinitialiser la couleur
        printf("Choisissez la taille du tableau : ");
        assert(scanf("%d", &taille) != 0);
    }

    remplir_tab_aleat(tab, taille);
    printf("Voici votre tableau : ");
    affiche(tab, taille);
    while (!est_trie(tab, taille)) {
        printf("Rentrez les indices à échanger : ")
    }
    if (coups <= 1)
        printf("Bravo ! Vous avez gagné en %d coup !\n", coups);
    else
        printf("Bravo ! Vous avez gagné en %d coups !\n", coups);
}

int main() {
    srand(time(NULL));

    // === exécution des tests avant le jeu ===
    test_remplir_tab_aleat();
    test_est_trie();
    // ========================================

    jeu();
    return 0;
}
