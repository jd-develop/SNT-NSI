#ifndef GRILLE_H
#define GRILLE_H

/* Grilles d'ordures */

struct grille {
    int n; // nombre de lignes
    int m; // nombre de colonnes
    int** ordures; // ordures[i][j] donne la quantité d'ordures en (i, j)
};
typedef struct grille grille_t;

/* Lit dans fn une grille d'ordures */
grille_t* lire_grille(char* fn);

/* Libère la mémoire allouée à g */
void liberer_grille(grille_t* g);

/* Affiche g */
void afficher_grille(grille_t* g);

#endif
