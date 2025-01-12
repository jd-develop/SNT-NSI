#ifndef KEY_H
#define KEY_H
/* Informations sur les clés et les valeurs. Il faut fournir des fonctions
 * pour libérer les clés et les valeurs, et des fonctions pour les afficher.
 * De plus, pour manipuler un type comme type clé, il faut fournir une
 * fonction permettant de tester l'égalité entre deux éléments. */

#include <stdbool.h>
#include <string.h>

/* À modifier en fonction des types souhaités pour les clés et valeurs */
typedef char* KEY;
typedef char* VAL;

/* Fonction de hachage, renvoie une valeur entière positive */
unsigned int hash(KEY k);

/* Renvoie true si k1 et k2 sont égaux, false sinon */
bool equal(KEY k1, KEY k2);

/* Fonctions de libération de mémoire des clés et valeurs */
void key_free(KEY k);
void val_free(VAL v);

/* Fonctions d'affichage des clés et valeurs: affichent leur argument
 * sans retour à la ligne */
void key_print(KEY k);
void val_print(VAL v);

#endif
