#ifndef WAV
#define WAV
#include "sound.h"

/* Écrit le header WAV dans le fichier f, qui aura n ⩾ 0 échantillons. On
 * suppose que le fichier est correctement ouvert (f != NULL) */
void write_header(FILE* f, int n);

/* Écrit dans `filename` le fichier WAV correspondant au son `s`, en écrasant
 * les données existantes. Plante si `filename` n’est pas accessible en
 * écriture.
 */
void save_sound(char* filename, sound_t* s);

#endif
