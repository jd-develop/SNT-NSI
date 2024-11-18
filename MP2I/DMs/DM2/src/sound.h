#include <stdint.h>
#ifndef SOUND
#define SOUND

/* structure représentant un son */
typedef struct sound {
    int n_samples;  // nombre d’échantillons
    int16_t* samples;  // tableau des échantillons
} sound_t;

/* libère la mémoire allouée pour un élément de type sound_t */
void free_sound(sound_t* p);

/* génère un son de durée T dont tous les échantillons ont une valeur aléatoire
 */
sound_t* white(float duree, int f_ech);

#endif

