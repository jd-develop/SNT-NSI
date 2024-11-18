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

#endif

