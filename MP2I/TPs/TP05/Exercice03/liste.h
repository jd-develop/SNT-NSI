#ifndef LISTE
#define LISTE
#include <stdbool.h>

struct maillon {
    struct maillon* suivant;
    int val;
};
typedef struct maillon maillon_t;

struct liste {
    unsigned int taille;
    maillon_t* tete; // premier maillon
};
typedef struct liste liste_t;

/* Renvoie une liste de n entiers aléatoires entre 0 et 99 */
liste_t* liste_aleatoire(int n);

/* Renvoie une liste chaînée dont les maillons contiennent les entiers
 * de 0 à n-1 inclus (n >= 0). Si n = 0, renvoie une liste vide.
 */
liste_t* liste_range(int n);

/* Affiche les valeurs de l dans l'ordre */
void liste_print(liste_t* l);

/* Libère la mémoire du maillon pointé par m */
void free_maillon(maillon_t* m);

/* Libère la mémoire de la liste chaînée pointée par l */
void free_liste(liste_t* l);

/* Renvoie true si le maillon pointé par m ou ses enfants contient au moins une
 * fois l’élément x, false sinon
 */
bool maillon_recherche(int x, maillon_t* m);

/* Renvoie true si la liste pointée par L contient au moins une fois l’élément
 * x, false sinon
 */
bool liste_recherche(int x, liste_t* L);

/* Ajoute l’élément val à la fin de la liste chaînée dont un maillon est pointé
 * par m
 */
void ajoute_element_fin_maillon(int val, maillon_t* m);

/* Ajoute l’élément val à la fin de la liste chaînée pointée par L */
void ajoute_element_fin(int val, liste_t* L);

/* Ajoute l’élément val au début de la liste chaînée pointée par L */
void ajoute_element_debut(int val, liste_t* L);

/* Retire le premier maillon de la liste chaînée pointée par L contenant
 * l’élément val. Ne fait rien si l’élément n’est pas dans la liste */
void retire_premier(int val, liste_t* L);

#endif
