#ifndef MELODY
#define MELODY
#define MAX_INSTRUMENT_NAME_SIZE 32
#include <stdio.h>
#include "sound.h"

/* Calcule et renvoie la fréquence de la note de hauteur `pitch` */
float pitch_to_freq(int pitch);

/*
 * Lit une piste dans le fichier file et la renvoie. Plante avec un message
 * d’erreur et renvoie NULL si le fichier n’est pas au bon format
 */
track_t* read_track(FILE* file);

/*
 * Lit un morceau dans le fichier filename et la renvoie. Plante avec un message
 * d’erreur et renvoie NULL si le fichier n’existe pas ou n’est pas au bon
 * format
 */
mix_t* load_mix(char* filename);

#endif
