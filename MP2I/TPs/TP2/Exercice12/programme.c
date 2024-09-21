#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#define WIDTH 40
#define COURBE_VERTE "\033[32m#\033[0m"
#define COURBE_ROUGE "\033[91m*\033[0m"
#define COURBE_VERTE2 "\033[92m*\033[0m"
#define COURBE_ROUGE2 "\033[31m#\033[0m"
#define DELTA_I 0.09 // valeur ajoutée à i à chaque tour de boucle (sachant qu’on dessine sin(i))
#define DELTA_T 25 // temps, en millisecondes, entre chaque tour de boucle


void affiche_un_caractere(double sinus, double sinus_precedent, bool premiere_courbe) {
    bool courbe_verte = (premiere_courbe && sinus < 0) || (!premiere_courbe && sinus > 0);
    bool courbe2 = (sinus_precedent < sinus);
    if (courbe_verte) {
        if (courbe2)
            printf("%s", COURBE_VERTE);
        else
            printf("%s", COURBE_VERTE2);
    } else {
        if (courbe2)
            printf("%s", COURBE_ROUGE);
        else
            printf("%s", COURBE_ROUGE2);
    }
}


void affiche_une_courbe(double sinus, double sinus_precedent, int caracteres_a_afficher, bool premiere_courbe) {
    for (int i = 0; i <= caracteres_a_afficher; i++) {
        affiche_un_caractere(sinus, sinus_precedent, premiere_courbe);
    }
}


void print_courbes(
   int debut_gauche,
    int caracteres_a_afficher,
    int espacement,
    double sinus,
    double sinus_precedent
) {
    for (int i = 0; i < debut_gauche; i++) {
        printf(" ");
    }
    affiche_une_courbe(sinus, sinus_precedent, caracteres_a_afficher, true);
    for (int i = 0; i < espacement; i++) {
        printf(" ");
    }
    affiche_une_courbe(sinus, sinus_precedent, caracteres_a_afficher, false);

    printf("\n");
}

void affiche_sinus(double sinus, double sinus_precedent) {
    int debut_droite;
    int debut_gauche;
    int caracteres_a_afficher;
    int espacement;

    if (fabs(sinus_precedent) < fabs(sinus)) {
        debut_droite = (int)((fabs(sinus_precedent)+1) * WIDTH/2);
        caracteres_a_afficher = (int)((fabs(sinus)+1) * WIDTH/2) - debut_droite;
    } else {
        debut_droite = (int)((fabs(sinus)+1) * WIDTH/2);
        caracteres_a_afficher = (int)((fabs(sinus_precedent)+1) * WIDTH/2) - debut_droite;
    }
    debut_gauche = WIDTH - debut_droite - caracteres_a_afficher;
    espacement = debut_droite - (WIDTH - debut_droite);

    caracteres_a_afficher += 1;
    debut_droite -= 1;
    espacement -= 2;

    print_courbes(debut_gauche, caracteres_a_afficher, espacement, sinus, sinus_precedent);
}

int main() {
    for (float i = 0; ; i += DELTA_I) {
        affiche_sinus(sin(i), sin(i - DELTA_I));
        usleep(DELTA_T*1000);
    }
    return 0;
}

