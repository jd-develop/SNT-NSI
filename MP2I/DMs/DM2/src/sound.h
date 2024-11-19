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
 * i.e. un bruit blanc
 */
sound_t* white(float duree, int f_ech);

/* crée et renvoie un son sinusoïdal de fréquence freq, d’amplitude amplitude,
 * de durée duree, et de fréquence d’échantillonage f_ech
 */
sound_t* sine(float freq, int amplitude, float duree, int f_ech);

/* crée et renvoie un son en créneau de fréquence freq, d’amplitude amplitude,
 * de durée duree, et de fréquence d’échantillonage f_ech
 */
sound_t* square(float freq, int amplitude, float duree, int f_ech);

/* crée et renvoie un son en triangle de fréquence freq, d’amplitude amplitude,
 * de durée duree, et de fréquence d’échantillonage f_ech
 */
sound_t* triangle(float freq, int amplitude, float duree, int f_ech);

/* crée et renvoie un son en dent de scie de fréquence freq, d’amplitude
 * amplitude, de durée duree, et de fréquence d’échantillonage f_ech
 */
sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech);

#endif

