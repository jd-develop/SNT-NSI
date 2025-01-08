/* SDA: File */
#ifndef file_h
#define file_h

#include <stdbool.h>
#include <stdio.h>

typedef struct file file_t;

/* Renvoie une file vide */
file_t* file_vide();

/* Renvoie un booléen indiquant si f est vide */
bool est_file_vide(file_t* f);

/* Enfile x à la queue de f */
void enfiler(file_t* f, int x);

/* Défile la tête de f et la renvoie */
int defiler(file_t* f);

/* Libère l'espace alloué à f */
void free_file(file_t* f);

/* Affiche les éléments de f de la tête vers la queue.
Par exemple si la file contient (de la tête vers la
queue) 2, 3, 4 et 5, alors affiche:
2 <- 3 <- 4 <- 5 */
void affiche_file(file_t* f);

#endif
