#ifndef STOI_H
#define STOI_H

#define TAILLE_HASH 64783
/* Table de hachage string -> int 
   Les clés sont de type char*
   et les valeurs de type int
*/
#include <stdbool.h>

typedef struct stoi stoi_t;

/* Crée une table de hachage vide */
stoi_t* stoi_vide();

/* Renvoie true si `clef` est une clef de t, false sinon */
bool stoi_mem(stoi_t* t, char* clef);

/* Renvoie la valeur associée à `clef` dans t. Si t ne contient pas `clef`,
   affiche un message d'erreur et arrête l'exécution. */
int stoi_get(stoi_t* t, char* clef);

/* Assigne à `clef` la valeur `valeur` dans t. Si `clef` est déjà présente,
   modifie la valeur précédente. Ne duplique pas la clef en mémoire. */
void stoi_set(stoi_t* t, char* clef, int valeur);

/* Libère l'espace alloué pour la table t. Attention: ne libère pas les clés. */
void stoi_free(stoi_t* t);

#endif
