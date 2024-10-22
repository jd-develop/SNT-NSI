/*
 * Simule une petite mémoire RAM. Ne peut stocker que des entiers. Permet
 * d’accéder à une valeur à partir de son adresse mémoire, de stocker une
 * valeur à une adresse mémoire, de faire des additions, des multiplications,
 * des modulos, mais aussi d’afficher des caractères ASCII, de n’exécuter des
 * instructions que sous certaines conditions…
 *
 * Un mode silencieux est disponible en passant l’argument « quiet » dans la
 * ligne de commande : pratique pour écrire des programmes en « langage
 * machine » puis de les envoyer dans l’entrée standard :) – cf. exemples
 * (par exemple pour « fibo » : `cat examples/fibo | ./a.out quiet`)
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

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
    int i, bool* deja_vu, int taille, bool lecture, bool quiet
) {
    if (i < 0 || i >= taille) {
        if (!quiet) {
            printf("\033[31m"); // rouge
            printf("Segmentation fault");
            printf("\033[0m\n"); // réinitialiser la couleur
        }
        return 1;
    } else if (lecture && !deja_vu[i]) {
        if (!quiet) {
            printf("\033[31m"); // rouge
            printf("Erreur : aucune valeur n’a été écrite à cette adresse");
            printf("\033[0m\n"); // réinitialiser la couleur
        }
        return 2;
    }
    return 0;
}

/*
 * Teste la fonction verifie_case_memoire
 */
void tests_verifie_case_memoire() {
    bool deja_vu[6] = {true, false, false, true, true, false};
    assert(verifie_case_memoire(1, deja_vu, 6, false, true) == 0);
    assert(verifie_case_memoire(0, deja_vu, 6, false, true) == 0);
    assert(verifie_case_memoire(-7, deja_vu, 6, false, true) == 1);
    assert(verifie_case_memoire(6, deja_vu, 6, false, true) == 1);
    assert(verifie_case_memoire(6, deja_vu, 6, true, true) == 1);
    assert(verifie_case_memoire(5, deja_vu, 6, true, true) == 2);
    assert(verifie_case_memoire(4, deja_vu, 6, true, true) == 0);
}

/*
 * Affiche la case numéro i de la mémoire (tableau ram), de taille taille.
 * Si la valeur est en-dehors de la mémoire ou que l’utilisateur n’a jamais
 * écrit dans cette case mémoire (i.e. l’élément correspondant dans deja_vu est
 * à false), affiche une erreur.
 */
void affiche_case_memoire(int i, int* ram, bool* deja_vu, int taille, bool quiet) {
    if (verifie_case_memoire(i, deja_vu, taille, true, quiet) == 0)
        printf("%d\n", ram[i]);
}

/*
 * Exactement comme affiche_case_memoire, mais sans afficher de retour-ligne
 */
void affiche_case_memoire_sans_retour_ligne(
    int i, int* ram, bool* deja_vu, int taille, bool quiet
) {
    if (verifie_case_memoire(i, deja_vu, taille, true, quiet) == 0)
        printf("%d", ram[i]);
}

/*
 * Renvoie true si la case i de la mémoire (tableau ram), de taille taille, est
 * égale à 0, false sinon ou si une erreur est survenue (par exemple si la
 * valeur est en-dehors de la mémoire ou que l’utilisateur n’a jamais écrit
 * dans cette case mémoire, i.e. l’élément correspondant dans deja_vu est à
 * false).
 */
bool case_memoire_egale_zero(int i, int* ram, bool* deja_vu, int taille, bool quiet) {
    if (verifie_case_memoire(i, deja_vu, taille, true, quiet) != 0)
        return false;
    return (ram[i] == 0);
}

/*
 * Teste la fonction case_memoire_egale_zero
 */
void tests_case_memoire_egale_zero() {
    int ram[6] = {-6, 0, 4, -9, 0, 7};
    bool deja_vu1[6] = {true, false, false, true, true, false};
    bool deja_vu2[6] = {true, true, true, true, true, true};

    assert(!case_memoire_egale_zero(-1, ram, deja_vu1, 6, true));
    assert(!case_memoire_egale_zero(0, ram, deja_vu1, 6, true));
    assert(!case_memoire_egale_zero(1, ram, deja_vu1, 6, true));
    assert(!case_memoire_egale_zero(2, ram, deja_vu1, 6, true));
    assert(!case_memoire_egale_zero(3, ram, deja_vu1, 6, true));
    assert(case_memoire_egale_zero(4, ram, deja_vu1, 6, true));
    assert(!case_memoire_egale_zero(5, ram, deja_vu1, 6, true));
    assert(!case_memoire_egale_zero(6, ram, deja_vu1, 6, true));

    assert(!case_memoire_egale_zero(-1, ram, deja_vu2, 6, true));
    assert(!case_memoire_egale_zero(0, ram, deja_vu2, 6, true));
    assert(case_memoire_egale_zero(1, ram, deja_vu2, 6, true));
    assert(!case_memoire_egale_zero(2, ram, deja_vu2, 6, true));
    assert(!case_memoire_egale_zero(3, ram, deja_vu2, 6, true));
    assert(case_memoire_egale_zero(4, ram, deja_vu2, 6, true));
    assert(!case_memoire_egale_zero(5, ram, deja_vu2, 6, true));
    assert(!case_memoire_egale_zero(6, ram, deja_vu1, 6, true));
}

/*
 * Renvoie true si la case i de la mémoire (tableau ram), de taille taille, est
 * ⩽ 0, false sinon ou si une erreur est survenue (par exemple si la
 * valeur est en-dehors de la mémoire ou que l’utilisateur n’a jamais écrit
 * dans cette case mémoire, i.e. l’élément correspondant dans deja_vu est à
 * false).
 */
bool case_memoire_negative_ou_nulle(int i, int* ram, bool* deja_vu, int taille, bool quiet) {
    if (verifie_case_memoire(i, deja_vu, taille, true, quiet) != 0)
        return false;
    return (ram[i] <= 0);
}

/*
 * Teste la fonction case_memoire_negative_ou_nulle
 */
void tests_case_memoire_negative_ou_nulle() {
    int ram[6] = {-6, 0, 4, -9, 0, 7};
    bool deja_vu1[6] = {true, false, true, false, true, false};
    bool deja_vu2[6] = {true, true, true, true, true, true};

    assert(!case_memoire_negative_ou_nulle(-1, ram, deja_vu1, 6, true));
    assert(case_memoire_negative_ou_nulle(0, ram, deja_vu1, 6, true));
    assert(!case_memoire_negative_ou_nulle(1, ram, deja_vu1, 6, true));
    assert(!case_memoire_negative_ou_nulle(2, ram, deja_vu1, 6, true));
    assert(!case_memoire_negative_ou_nulle(3, ram, deja_vu1, 6, true));
    assert(case_memoire_negative_ou_nulle(4, ram, deja_vu1, 6, true));
    assert(!case_memoire_negative_ou_nulle(5, ram, deja_vu1, 6, true));
    assert(!case_memoire_negative_ou_nulle(6, ram, deja_vu1, 6, true));

    assert(!case_memoire_negative_ou_nulle(-1, ram, deja_vu2, 6, true));
    assert(case_memoire_negative_ou_nulle(0, ram, deja_vu2, 6, true));
    assert(case_memoire_negative_ou_nulle(1, ram, deja_vu2, 6, true));
    assert(!case_memoire_negative_ou_nulle(2, ram, deja_vu2, 6, true));
    assert(case_memoire_negative_ou_nulle(3, ram, deja_vu2, 6, true));
    assert(case_memoire_negative_ou_nulle(4, ram, deja_vu2, 6, true));
    assert(!case_memoire_negative_ou_nulle(5, ram, deja_vu2, 6, true));
    assert(!case_memoire_negative_ou_nulle(6, ram, deja_vu1, 6, true));
}

/*
 * Stocke la valeur n à l’adresse i de la mémoire (tableau ram) de taille
 * taille. Met à jour le tableau deja_vu des cases déjà modifiées. Si
 * l’adresse est en-dehors de la mémoire, affiche une erreur.
 */
void stocke_dans_case_memoire(
    int n, int i, int* ram, bool* deja_vu, int taille, bool quiet
) {
    if (verifie_case_memoire(i, deja_vu, taille, false, quiet) != 0)
        return;
    deja_vu[i] = true;
    ram[i] = n;
    if (!quiet)
        printf("%d est stocké à l’adresse %d.\n", n, i);
}

/*
 * Teste la fonction stocke_dans_case_memoire
 */
void tests_stocke_dans_case_memoire() {
    int ram[6] = {-6, 0, 4, -9, 0, 7};
    bool deja_vu[6] = {true, false, true, false, true, false};

    stocke_dans_case_memoire(8, -1, ram, deja_vu, 6, true);
    stocke_dans_case_memoire(10, 0, ram, deja_vu, 6, true);
    stocke_dans_case_memoire(12, 2, ram, deja_vu, 6, true);
    stocke_dans_case_memoire(15, 5, ram, deja_vu, 6, true);
    stocke_dans_case_memoire(17, 6, ram, deja_vu, 6, true);
    stocke_dans_case_memoire(19, 565, ram, deja_vu, 6, true);

    assert(ram[0] == 10);
    assert(ram[1] == 0);
    assert(ram[2] == 12);
    assert(ram[3] == -9);
    assert(ram[4] == 0);
    assert(ram[5] == 15);
}

/*
 * Calcule la somme des valeurs stockées dans les adresses mémoires a et b
 * du tableau ram de taille taille, et stocke cette valeur dans la case c.
 * Affiche une erreur si une de ces adresses est invalide (hors de la mémoire
 * ou, dans le cas de a et b, n’a jamais été écrite ; i.e. l’élément
 * correspondant dans deja_vu est à false)
 */
void addition(
    int a, int b, int c, int ram[], bool deja_vu[], int taille, bool quiet
) {
    if (verifie_case_memoire(a, deja_vu, taille, true, quiet) != 0)
        return;
    if (verifie_case_memoire(b, deja_vu, taille, true, quiet) != 0)
        return;
    if (verifie_case_memoire(c, deja_vu, taille, false, quiet) != 0)
        return;

    deja_vu[c] = true;
    ram[c] = ram[a] + ram[b];
}

/*
 * Teste la fonction addition
 */
void tests_addition() {
    int ram[6] = {-6, 0, 4, -9, 0, 7};
    bool deja_vu[6] = {true, false, true, false, true, false};

    addition(0, 2, 1, ram, deja_vu, 6, true);
    assert(ram[0] == -6);
    assert(ram[2] == 4);
    assert(ram[1] == -2);
    assert(deja_vu[0]);
    assert(deja_vu[1]);
    assert(deja_vu[2]);

    addition(0, 3, 1, ram, deja_vu, 6, true);
    assert(ram[0] == -6);
    assert(ram[3] == -9);
    assert(ram[1] == -2);
    assert(deja_vu[0]);
    assert(deja_vu[1]);
    assert(deja_vu[2]);
    assert(!deja_vu[3]);
}

/*
 * Calcule le produit des valeurs stockées dans les adresses mémoires a et b
 * du tableau ram de taille taille, et stocke cette valeur dans la case c.
 * Affiche une erreur si une de ces adresses est invalide (hors de la mémoire
 * ou, dans le cas de a et b, n’a jamais été écrite ; i.e. l’élément
 * correspondant dans deja_vu est à false)
 */
void multiplication(
    int a, int b, int c, int ram[], bool deja_vu[], int taille, bool quiet
) {
    if (verifie_case_memoire(a, deja_vu, taille, true, quiet) != 0)
        return;
    if (verifie_case_memoire(b, deja_vu, taille, true, quiet) != 0)
        return;
    if (verifie_case_memoire(c, deja_vu, taille, false, quiet) != 0)
        return;

    deja_vu[c] = true;
    ram[c] = ram[a] * ram[b];
}

/*
 * Teste la fonction multiplication
 */
void tests_multiplication() {
    int ram[6] = {-6, 0, 4, -9, 0, 7};
    bool deja_vu[6] = {true, false, true, false, true, false};

    multiplication(0, 2, 1, ram, deja_vu, 6, true);
    assert(ram[0] == -6);
    assert(ram[2] == 4);
    assert(ram[1] == -24);
    assert(deja_vu[0]);
    assert(deja_vu[1]);
    assert(deja_vu[2]);

    multiplication(0, 3, 1, ram, deja_vu, 6, true);
    assert(ram[0] == -6);
    assert(ram[3] == -9);
    assert(ram[1] == -24);
    assert(deja_vu[0]);
    assert(deja_vu[1]);
    assert(deja_vu[2]);
    assert(!deja_vu[3]);
}

/*
 * Calcule le modulo des valeurs stockées dans les adresses mémoires a et b
 * du tableau ram de taille taille, et stocke cette valeur dans la case c.
 * Affiche une erreur si une de ces adresses est invalide (hors de la mémoire
 * ou, dans le cas de a et b, n’a jamais été écrite ; i.e. l’élément
 * correspondant dans deja_vu est à false)
 */
void modulo(
    int a, int b, int c, int ram[], bool deja_vu[], int taille, bool quiet
) {
    if (verifie_case_memoire(a, deja_vu, taille, true, quiet) != 0)
        return;
    if (verifie_case_memoire(b, deja_vu, taille, true, quiet) != 0)
        return;
    if (verifie_case_memoire(c, deja_vu, taille, false, quiet) != 0)
        return;

    deja_vu[c] = true;
    ram[c] = ram[a] % ram[b];
}

/*
 * Teste la fonction modulo
 */
void tests_modulo() {
    int ram[6] = {-6, 0, 4, -9, 0, 7};
    bool deja_vu[6] = {true, false, true, false, true, false};

    modulo(0, 2, 1, ram, deja_vu, 6, true);
    assert(ram[0] == -6);
    assert(ram[2] == 4);
    assert(ram[1] == -2);
    assert(deja_vu[0]);
    assert(deja_vu[1]);
    assert(deja_vu[2]);

    modulo(0, 3, 1, ram, deja_vu, 6, true);
    assert(ram[0] == -6);
    assert(ram[3] == -9);
    assert(ram[1] == -2);
    assert(deja_vu[0]);
    assert(deja_vu[1]);
    assert(deja_vu[2]);
    assert(!deja_vu[3]);
}

/*
 * Calcule le quotient par division euclidienne des valeurs stockées dans les
 * adresses mémoires a et b du tableau ram de taille taille, et stocke cette
 * valeur dans la case c.
 * Affiche une erreur si une de ces adresses est invalide (hors de la mémoire
 * ou, dans le cas de a et b, n’a jamais été écrite ; i.e. l’élément
 * correspondant dans deja_vu est à false)
 */
void quotient(
    int a, int b, int c, int ram[], bool deja_vu[], int taille, bool quiet
) {
    if (verifie_case_memoire(a, deja_vu, taille, true, quiet) != 0)
        return;
    if (verifie_case_memoire(b, deja_vu, taille, true, quiet) != 0)
        return;
    if (verifie_case_memoire(c, deja_vu, taille, false, quiet) != 0)
        return;

    deja_vu[c] = true;
    ram[c] = ram[a] / ram[b];
}

/*
 * Teste la fonction quotient
 */
void tests_quotient() {
    int ram[6] = {-6, 0, 4, -9, 0, 7};
    bool deja_vu[6] = {true, false, true, false, true, false};

    quotient(0, 2, 1, ram, deja_vu, 6, true);
    assert(ram[0] == -6);
    assert(ram[2] == 4);
    assert(ram[1] == -1);
    assert(deja_vu[0]);
    assert(deja_vu[1]);
    assert(deja_vu[2]);

    quotient(0, 3, 1, ram, deja_vu, 6, true);
    assert(ram[0] == -6);
    assert(ram[3] == -9);
    assert(ram[1] == -1);
    assert(deja_vu[0]);
    assert(deja_vu[1]);
    assert(deja_vu[2]);
    assert(!deja_vu[3]);
}

/*
 * Affiche le caractère ASCII représenté par les 8 derniers bits de la case
 * numéro i de la mémoire (tableau ram), de taille taille.
 * Si la valeur est en-dehors de la mémoire ou que l’utilisateur n’a jamais
 * écrit dans cette case mémoire (i.e. l’élément correspondant dans deja_vu est
 * à false), affiche une erreur.
 */
void affiche_ascii(int i, int* ram, bool* deja_vu, int taille, bool quiet) {
    if (verifie_case_memoire(i, deja_vu, taille, true, quiet) == 0)
        printf("%c", (char)(ram[i]%256));
}

int main(int argc, char *argv[]) {
    /* TESTS */
    tests_verifie_case_memoire();
    tests_case_memoire_egale_zero();
    tests_case_memoire_negative_ou_nulle();
    tests_stocke_dans_case_memoire();
    tests_addition();
    tests_multiplication();
    tests_modulo();
    tests_quotient();
    /* ----- */

    int ram[MAX_LEN];
    bool deja_vu[MAX_LEN]; // true si une valeur a déjà été écrite, false sinon
    int taille;
    int choix;
    int adresse1;
    int adresse2;
    int adresse3;
    bool executer_instruction = true;

    bool quiet = (argc > 1 && strcmp(argv[1], "quiet") == 0);

    if (!quiet)
        printf("Choisir la taille de la mémoire : ");
    if (scanf("%d", &taille) == 0) {
        if (!quiet) {
            printf("\033[31m"); // rouge
            printf( "Taille invalide");
            printf("\033[0m\n"); // réinitialiser la couleur
        }
        return 1;
    }
    if (taille < 0 || taille > 1024) {
        if (!quiet) {
            printf("\033[31m"); // rouge
            printf(
                "La taille de la mémoire doit être comprise entre 0 et 1024 inclus"
            );
            printf("\033[0m\n"); // réinitialiser la couleur
        }
        return 2;
    }

    if (!quiet)
        printf("Note : les adresses commencent à 0.\n");

    while (true) {
        if (!quiet) {
            printf("\n");
            printf("Que voulez-vous faire ?\n");
            printf("1. Accéder à une valeur\n");
            printf("2. Stocker une valeur\n");
            printf("3. Faire une addition\n");
            printf("5. Faire une multiplication\n");
            printf("6. Afficher des options supplémentaires\n");
            printf("4. Quitter le programme\n");
            printf("? ");
        }

        if (scanf("%d", &choix) == 0)
            break;

        if (choix == 1) {
            if (!quiet)
                printf("Rentrez l’adresse mémoire : ");
            if (scanf("%d", &adresse1) == 0)
                break;

            if (executer_instruction)
                affiche_case_memoire(adresse1, ram, deja_vu, taille, quiet);

        } else if (choix == 2) {
            if (!quiet)
                printf("Rentrer l’adresse mémoire puis la valeur à stocker : ");
            if (scanf("%d %d", &adresse1, &adresse2) == 0)
                break;

            if (executer_instruction)
                stocke_dans_case_memoire(adresse2, adresse1, ram, deja_vu, taille, quiet);

        } else if (choix == 3) {
            if (!quiet)
                printf("Rentrer les deux adresses mémoire à additioner : ");
            if (scanf("%d %d", &adresse1, &adresse2) == 0)
                break;
            if (!quiet)
                printf("Rentrer l’adresse mémoire à laquelle stocker le résultat : ");
            if (scanf("%d", &adresse3) == 0)
                break;

            if (executer_instruction)
                addition(adresse1, adresse2, adresse3, ram, deja_vu, taille, quiet);

        } else if (choix == 5) {
            if (!quiet)
                printf("Rentrer les deux adresses mémoire à multiplier : ");
            if (scanf("%d %d", &adresse1, &adresse2) == 0)
                break;
            if (!quiet)
                printf("Rentrer l’adresse mémoire à laquelle stocker le résultat : ");
            if (scanf("%d", &adresse3) == 0)
                break;

            if (executer_instruction)
                multiplication(adresse1, adresse2, adresse3, ram, deja_vu, taille, quiet);

        } else if (choix == 6) {
            if (!quiet) {
                printf("Choix supplémentaires :\n");
                printf("7. Afficher une valeur sans afficher de retour-ligne\n");
                printf("8. Afficher le caractère ASCII représenté par les 8 ");
                printf("derniers bits du nombre stocké à une certaine adresse\n");
                printf("9. Calculer un modulo\n");
                printf("10. Calculer un quotient par division euclidienne\n");
                printf("11. Effectuer l’instruction suivante si une certaine ");
                printf("adresse vaut 0\n");
                printf("12. Effectuer l’instruction suivante si une certaine ");
                printf("adresse est négative ou nulle\n");
            }
        } else if (choix == 7) {
            if (!quiet)
                printf("Rentrez l’adresse mémoire : ");
            if (scanf("%d", &adresse1) == 0)
                break;

            if (executer_instruction)
                affiche_case_memoire_sans_retour_ligne(adresse1, ram, deja_vu, taille, quiet);
        } else if (choix == 8) {
            if (!quiet)
                printf("Rentrez l’adresse mémoire : ");
            if (scanf("%d", &adresse1) == 0)
                break;

            if (executer_instruction)
                affiche_ascii(adresse1, ram, deja_vu, taille, quiet);

        } else if (choix == 9) {
            if (!quiet)
                printf("Rentrer les deux adresses mémoire dont vous souhaitez calculer le modulo : ");
            if (scanf("%d %d", &adresse1, &adresse2) == 0)
                break;
            if (!quiet)
                printf("Rentrer l’adresse mémoire à laquelle stocker le résultat : ");
            if (scanf("%d", &adresse3) == 0)
                break;

            if (executer_instruction)
                modulo(adresse1, adresse2, adresse3, ram, deja_vu, taille, quiet);

        } else if (choix == 10) {
            if (!quiet)
                printf("Rentrer les deux adresses mémoire dont vous souhaitez calculer le quotient : ");
            if (scanf("%d %d", &adresse1, &adresse2) == 0)
                break;
            if (!quiet)
                printf("Rentrer l’adresse mémoire à laquelle stocker le résultat : ");
            if (scanf("%d", &adresse3) == 0)
                break;

            if (executer_instruction)
                quotient(adresse1, adresse2, adresse3, ram, deja_vu, taille, quiet);

        } else if (choix == 11) {
            if (!quiet)
                printf("Rentrer la case mémoire condition (si =0, l’instruction suivante est exécutée) : ");
            if (scanf("%d", &adresse1) == 0)
                break;

            if (executer_instruction)
                executer_instruction = case_memoire_egale_zero(adresse1, ram, deja_vu, taille, quiet);

            printf("%d\n", executer_instruction);
        } else if (choix == 12) {
            if (!quiet)
                printf("Rentrer la case mémoire condition (si <=0, l’instruction suivante est exécutée) : ");
            if (scanf("%d", &adresse1) == 0)
                break;

            if (executer_instruction)
                executer_instruction = case_memoire_negative_ou_nulle(adresse1, ram, deja_vu, taille, quiet);
        } else if (choix == 4) {
            if (executer_instruction)
                break;
        } else {
            break;
        }
        if (choix != 11 && choix != 12)
            executer_instruction = true;
    }

    return 0;
}

