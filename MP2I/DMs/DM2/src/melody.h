#ifndef MELODY
#define MELODY
#define MAX_INSTRUMENT_NAME_SIZE 32
#include <stdio.h>
#include "sound.h"

/* Calcule et renvoie la fréquence de la note de hauteur `pitch` */
float pitch_to_freq(int pitch);

/* Lit une piste dans le fichier file et la renvoie. Plante si le fichier
 * n’est pas au bon format
 */
track_t* read_track(FILE* file);

#endif
