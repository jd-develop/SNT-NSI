#ifndef MENU
#define MENU

#include <stdbool.h>
#define MAX_ELEMS 128

// ÉLÉMENTS DE MENUS

struct menu_elem {
    char nom[50];
    float prix_unite;
    bool vegan;
};

typedef struct menu_elem menu_elem_t;

/* Affiche l’élément de menu pointé par `e` */
void affiche_elem(menu_elem_t* e);

/* Lit un élément dans le fichier `fp` et écrit les informations lues
 * dans l’élément de menu pointé par `e`. Écrit “Erreur” dans le nom et -1 dans
 * le prix de l’élément si la fonction rencontre une fin de fichier.
 */
void lire_element(FILE* fp, menu_elem_t* e);

// MENUS

// Invariant : nb_elems ⩽ MAX_ELEMS
struct menu {
    menu_elem_t elements[MAX_ELEMS];
    int nb_elems; // nombre d’éléments du menu
};

typedef struct menu menu_t;

/* Affiche le menu pointé par `m` */
void affiche_menu(menu_t* m);

/* Ajoute un élément au menu pointé par `m`, de nom `nom`, de prix
 * à l’unité `prix_unite`, et qui est végan si `vegan` est à true.
 */
void ajouter_element(menu_t* m, char* nom, float prix_unite, bool vegan);

/* Lit les informations d’un menu dans le fichier `nom_fichier` et stocke les
 * informations dans la structure pointée par `m`
 */
void lire_menu(char* nom_fichier, menu_t* m);

// COMMANDES

/* Initialise (=remplit de zéros) le tableau `commande` représentant une
 * commande, pour un menu contenant `nb_elems` éléments
 */
void init_commande(int* commande, int nb_elements);

/* Prend commande en mettant à jour les valeurs de `commande` (de taille
 * maximum `nb_elems`) en fonction de l’entrée utilisateur. Ignore
 * une entrée si l’entrée de menu n’existe pas
 */
void prendre_commande(int* commande, int nb_elems);

/* Affiche le résumé d’une commande, i.e. affiche ce que l’utilisateur
 * a commandé, en fonction de la commande `commande` et du menu
 * pointé par `m`
 */
void resume_commande(int* commande, menu_t* m);

/* Calcule le prix total de la commande `commande` connaissant le
 * menu `m`.
 */
float total_commande(int* commande, menu_t* m);

#endif
