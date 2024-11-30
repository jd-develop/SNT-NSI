#ifndef WAV
#define WAV
#include <stdio.h>
#include "sound.h"

/* Écrit l’entier `a` dans le fichier `f`, en convention petit-boutiste,
 * sur `size` octets (1 ⩽ size ⩽ 4)
 */
void write_int(FILE* f, int a, int size);

/* Teste la fonction write_int */
void test_write_int();

/* Écrit le header WAV dans le fichier f, qui aura n ⩾ 0 échantillons. On
 * suppose que le fichier est correctement ouvert (f != NULL) */
void write_header(FILE* f, int n);

/* Écrit dans `filename` le fichier WAV correspondant au son `s`, en écrasant
 * les données existantes. Plante si `filename` n’est pas accessible en
 * écriture.
 */
void save_sound(char* filename, sound_t* s);

#endif
