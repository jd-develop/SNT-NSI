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


/* Affiche un caractère de la courbe. sinus est la valeur actuelle du sinus,
 * sinus_precedent est la valeur de sinus sur la ligne précédente,
 * premiere_courbe est true si on trace la courbe affichée à gauche, false
 * sinon
 */
void affiche_un_caractere(
        double sinus,
        double sinus_precedent,
        bool premiere_courbe
) {
    /* on est en train de tracer la courbe verte soit si :
     * la courbe est à gauche et sinus est négatif
     * la courbe est à droite et sinus est positif
     */
    bool courbe_verte = (premiere_courbe && sinus < 0) ||
                        (!premiere_courbe && sinus > 0);
    /* courbe_2 correspond à une courbe moins visible, c’est-à-dire paraissant
     * être derrière. On sait qu’on est dans ce cas si la courbe est localement
     * croissante
     */
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


/* affiche `caracteres_a_afficher` caractères de la bonne couleur (permet
 *     d’afficher une courbe sur une ligne).
 * `sinus` est la valeur actuelle du sinus
 * `sinus_precedent` est la valeur précédente du sinus.
 * `premiere_courbe` est true si on est en train de dessiner la courbe de
 *     gauche, et est false sinon
 */
void affiche_une_courbe(
        double sinus,
        double sinus_precedent,
        int caracteres_a_afficher,
        bool premiere_courbe
) {
    for (int i = 0; i <= caracteres_a_afficher; i++) {
        affiche_un_caractere(sinus, sinus_precedent, premiere_courbe);
    }
}


/* Affiche les deux courbes sur une ligne (est appelée par affiche_sinus)
 * `debut_gauche` est le numéro du caractère à partir duquel on dessine la
 *     première courbe.
 * `caracteres_a_afficher` est le nombre de caractères dessinés par courbe pour
 *     les deux courbes.
 * `espacement` est le nombre d’espaces à insérer entre les deux courbes
 * `sinus` est la valeur courante du sinus
 * `sinus_precedent` est la valeur précédentte du sinus
 */
void affiche_courbes(
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

/* Affiche les deux courbes sur une ligne (avec moins de paramètres que
 * affiche_courbes)
 * `sinus` est la valeur courante du sinus
 * `sinus_precedent` est la valeur précédentte du sinus
 * (En pratique, cette fonction calcule les bonnes valeurs pour affiche_courbes
 *  puis l’apelle.)
 */
void affiche_sinus(double sinus, double sinus_precedent) {
    int debut_droite;
    int debut_gauche;
    int caracteres_a_afficher;
    int espacement;
    /* on calcule les valeurs absolues des sinus, puis on ajoute 1 pour
     * qu’elles soient comprises entre 0 et 2 */
    float abs_sinus_precedent = fabs(sinus_precedent) + 1.0;
    float abs_sinus = fabs(sinus) + 1.0;

    /* Le début de la courbe dépend soit de sinus, soit de sinus_precedent
     * en fonction de qui est le plus grand (ce qu’on essaye de faire est de ne
     * pas avoir de caractères isolés de ce style :
     *
     *   *
     *       *
     *           *
     *
     * On veut donc ceci à la place :
     *   *****
     *       *****
     *           ***..
     *
     * )
     */
    if (abs_sinus_precedent < abs_sinus) {
        debut_droite =
            (int)
            (abs_sinus_precedent * WIDTH/2);
        caracteres_a_afficher =
            (int)
            (abs_sinus * WIDTH/2) - debut_droite;
    } else {
        debut_droite =
            (int)
            (abs_sinus * WIDTH/2);
        caracteres_a_afficher =
            (int)
            (abs_sinus_precedent * WIDTH/2) - debut_droite;
    }
    /* on peut ainsi calculer les valeurs du début à gauche et de l’espacement
     */
    debut_gauche = WIDTH - debut_droite - caracteres_a_afficher;
    espacement = debut_droite - (WIDTH - debut_droite);

    /* La courbe est + sympa avec un caractère en plus à chaque fois, donc
     * on l’ajoute et on enlève le bon nombre de caractères aux autres valeurs
     */
    caracteres_a_afficher += 1;
    debut_droite -= 1;
    espacement -= 2;

    /* il ne nous reste plus qu’à appeler notre fonction avec les valeurs
     * calculées
     */
    affiche_courbes(
        debut_gauche,
        caracteres_a_afficher,
        espacement,
        sinus,
        sinus_precedent
    );
}

int main() {
    for (float i = 0; ; i += DELTA_I) {
        affiche_sinus(sin(i), sin(i - DELTA_I));
        usleep(DELTA_T*1000);
    }
    return 0;
}

