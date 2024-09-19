#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#define WIDTH 40
#define COURBE_VERTE "\033[32m#\033[0m"
#define COURBE_ROUGE "\033[91m*\033[0m"
#define TRAIT "-"
#define DELTA_I 0.09 // valeur ajoutée à i à chaque tour de boucle (sachant qu’on dessine sin(i))
#define DELTA_T 25 // temps, en millisecondes, entre chaque tour de boucle
#define EPSILON 0.0010  // marge d’erreur pour comparer sinus à 1 et -1
#define EPSILON2 0.039 // marge d’erreur pour comparer sinus à 0.5 et -0.5
#define EPSILON3 0.065 // marge d’erreur pour comparer sinus à 0.55 et -0.55


void print_sinus(double sinus, double last_sinus) {
    int debut_droite;
    int debut_gauche;
    int caracteres_a_afficher;
    int espacement;

    bool devant_puis_derriere = sinus < 0;
    //printf("\n");

    if (fabs(last_sinus) < fabs(sinus)) {
        debut_droite = (int)((fabs(last_sinus)+1) * WIDTH/2);
        caracteres_a_afficher = (int)((fabs(sinus)+1) * WIDTH/2) - debut_droite;
    } else {
        debut_droite = (int)((fabs(sinus)+1) * WIDTH/2);
        caracteres_a_afficher = (int)((fabs(last_sinus)+1) * WIDTH/2) - debut_droite;
    }
    debut_gauche = WIDTH - debut_droite - caracteres_a_afficher;
    espacement = debut_droite - (WIDTH - debut_droite);

    for (int i = 0; i < debut_gauche; i++) {
        printf(" ");
    }
    for (int i = 0; i <= caracteres_a_afficher; i++) {
        if (devant_puis_derriere)
            printf("%s", COURBE_VERTE);
        else
            printf("%s", COURBE_ROUGE);
    }
    for (int i = 0; i < espacement; i++) {
        if (espacement < 3) {
            if (devant_puis_derriere)
                printf("%s", COURBE_ROUGE);
            else
                printf("%s", COURBE_VERTE);
        } else {
            if ((sinus-EPSILON <= -1) || (1 <= sinus+EPSILON)) {
                printf(TRAIT);
            } else if ((-EPSILON2 <= sinus-0.5 && sinus-0.5 <= EPSILON2) ||
                     (-EPSILON2 <= sinus+0.5 && sinus+0.5 <= EPSILON2)) {
                if (i-1 <= espacement/2)
                    printf(TRAIT);
                else
                    printf(" ");
            } else if ((-EPSILON3 <= sinus-0.55 && sinus-0.55 <= EPSILON3) ||
                     (-EPSILON3 <= sinus+0.55 && sinus+0.55 <= EPSILON3)) {
                if (i < espacement/2)
                    printf(" ");
                else
                    printf(TRAIT);
            } else {
                printf(" ");
            }
        }
    }
    for (int i = 0; i <= caracteres_a_afficher; i++) {
        if (devant_puis_derriere)
            printf("%s", COURBE_ROUGE);
        else
            printf("%s", COURBE_VERTE);
    }
    printf("\n");
}

int main() {
    for (float i = 0; ; i += DELTA_I) {
        print_sinus(sin(i), sin(i - DELTA_I));
        usleep(DELTA_T*1000);
    }
    return 0;
}

