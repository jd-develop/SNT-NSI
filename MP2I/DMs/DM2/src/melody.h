#ifndef MELODY
#define MELODY
#define MAX_INSTRUMENT_NAME_SIZE 32
#include <stdio.h>
#include "sound.h"

/* Calcule et renvoie la fréquence de la note de hauteur `pitch` */
float pitch_to_freq(int pitch);

/* Teste la fonction pitch_to_freq */
void test_pitch_to_freq();

/* Convertit un nom d’instrument en octet. Renvoie 0 et affiche un message
 * d’erreur si l’instrument n’existe pas.
 * Renvoie :
 * * 's' pour un sinus (sinus)
 * * 'S' pour un sinus avec enveloppe ADSR (sinusadsr)
 * * 'c' pour un carré (square)
 * * 'C' pour un carré avec enveloppe ADSR (squareadsr)
 * * 't' pour un triangle (triangle)
 * * 'T' pour un triangle avec enveloppe ADSR (triangleadsr)
 * * 'd' pour un signal en dents de scie (sawtooth)
 * * 'D' pour un signal en dents de scie avec enveloppe ADSR (sawtoothadsr)
 */
char instrument_to_byte(char* instrument);

/*
 * Lit une piste dans le fichier file et la renvoie. Plante avec un message
 * d’erreur et renvoie NULL si le fichier n’est pas au bon format
 */
track_t* read_track(FILE* file);

/*
 * Lit un morceau dans le fichier filename et le renvoie. Plante avec un message
 * d’erreur et renvoie NULL si le fichier n’existe pas ou n’est pas au bon
 * format
 */
mix_t* load_mix(char* filename);

#endif
