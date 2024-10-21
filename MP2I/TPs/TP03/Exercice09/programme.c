/*
 * Simule une petite mémoire RAM. Ne peut stocker que des entiers. Permet
 * d’accéder à une valeur à partir de son adresse mémoire, de stocker une
 * valeur à une adresse mémoire, et de faire une addition.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_LEN 1024

/*
 * Vérifie que l’adresse i est valide pour la mémoire ram de taille taille.
 * A besoin du tableau deja_vu (pour vérifier si l’utilisateur a déjà écrit
 * dans cette case, cf. codes d’erreurs)
 * Si elle ne l’est pas, affiche un message d’erreur et renvoie une certaine
 * valeur (voir plus bas). Si tout se passe bien, renvoie 0.
 *
 * Codes d’erreur :
 * * 1 : l’adresse est en-dehors de la mémoire (segfault)
 * * 2 : l’adresse n’a jamais été écrite (cette erreur n’est pas renvoyée si
 *       lecture est à false)
 */
char verifie_case_memoire(
    int i, bool* deja_vu, int taille, bool lecture
) {
    if (i < 0 || i >= taille) {
        printf("\033[31m"); // rouge
        printf("Segmentation fault");
        printf("\033[0m\n"); // réinitialiser la couleur
        return 1;
    } else if (lecture && !deja_vu[i]) {
        printf("\033[31m"); // rouge
        printf("Erreur : aucune valeur n’a été écrite à cette adresse");
        printf("\033[0m\n"); // réinitialiser la couleur
        return 2;
    }
    return 0;
}

/*
 * Affiche la case numéro i de la mémoire (tableau ram), de taille taille.
 * Si la valeur est en-dehors de la mémoire ou que l’utilisateur n’a jamais
 * écrit dans cette case mémoire (i.e. l’élément correspondant dans deja_vu est
 * à false), affiche une erreur.
 */
void affiche_case_memoire(int i, int* ram, bool* deja_vu, int taille) {
    if (verifie_case_memoire(i, deja_vu, taille, true) == 0)
        printf("%d\n", ram[i]);
}

/*
 * Stocke la valeur n à l’adresse i de la mémoire (tableau ram) de taille
 * taille. Met à jour le tableau deja_vu des cases déjà modifiées. Si
 * l’adresse est en-dehors de la mémoire, affiche une erreur.
 */
void stocke_dans_case_memoire(
    int n, int i, int* ram, bool* deja_vu, int taille
) {
    if (verifie_case_memoire(i, deja_vu, taille, false) != 0)
        return;
    deja_vu[i] = true;
    ram[i] = n;
    printf("%d est stocké à l’adresse %d.\n", n, i);
}

/*
 * Calcule la somme des valeurs stockées dans les adresses mémoires a et b
 * du tableau ram de taille taille, et stocke cette valeur dans la case c.
 * Affiche une erreur si une de ces adresses est invalide (hors de la mémoire
 * ou, dans le cas de a et b, n’a jamais été écrite ; i.e. l’élément
 * correspondant dans deja_vu est à false)
 */
void addition(
    int a, int b, int c, int ram[], bool deja_vu[], int taille
) {
    if (verifie_case_memoire(a, deja_vu, taille, true) != 0)
        return;
    if (verifie_case_memoire(b, deja_vu, taille, true) != 0)
        return;
    if (verifie_case_memoire(c, deja_vu, taille, false) != 0)
        return;

    deja_vu[c] = true;
    ram[c] = ram[a] + ram[b];
}

int main() {
    int ram[MAX_LEN];
    bool deja_vu[MAX_LEN]; // true si une valeur a déjà été écrite, false sinon
    int taille;
    int choix;
    int adresse1;
    int adresse2;
    int adresse3;

    printf("Choisir la taille de la mémoire : ");
    if (scanf("%d", &taille) == 0) {
        printf("\033[31m"); // rouge
        printf( "Taille invalide"); printf("\033[0m\n"); // réinitialiser la couleur
        return 1;
    }
    if (taille < 0 || taille > 1024) {
        printf("\033[31m"); // rouge
        printf(
            "La taille de la mémoire doit être comprise entre 0 et 1024 inclus"
        );
        printf("\033[0m\n"); // réinitialiser la couleur
        return 2;
    }

    printf("Note : les adresses commencent à 0.\n");

    while (true) {
        printf("\n");
        printf("Que voulez-vous faire ?\n");
        printf("1. Accéder à une valeur\n");
        printf("2. Stocker une valeur\n");
        printf("3. Faire une addition\n");
        printf("4. Quitter le programme\n");
        printf("? ");

        if (scanf("%d", &choix) == 0)
            break;

        if (choix == 1) {
            printf("Rentrez l’adresse mémoire : ");
            if (scanf("%d", &adresse1) == 0)
                break;
            affiche_case_memoire(adresse1, ram, deja_vu, taille);
        } else if (choix == 2) {
            printf("Rentrer l’adresse mémoire puis la valeur à stocker : ");
            if (scanf("%d %d", &adresse1, &adresse2) == 0)
                break;
            stocke_dans_case_memoire(adresse2, adresse1, ram, deja_vu, taille);
        } else if (choix == 3) {
            printf("Rentrer les deux adresses mémoire à additioner : ");
            if (scanf("%d %d", &adresse1, &adresse2) == 0)
                break;
            printf("Rentrer l’adresse mémoire à laquelle stocker le résultat : ");
            if (scanf("%d", &adresse3) == 0)
                break;
            addition(adresse1, adresse2, adresse3, ram, deja_vu, taille);
        } else {
            break;
        }
    }

    return 0;
}

