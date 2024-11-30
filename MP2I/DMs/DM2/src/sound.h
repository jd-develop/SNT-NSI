#ifndef SOUND
#define SOUND
#include <stdint.h>

/* structure représentant un son */
typedef struct sound {
    int n_samples;  // nombre d’échantillons
    int16_t* samples;  // tableau des échantillons
} sound_t;

/* structure représentant une piste */
typedef struct track {
    int n_sounds;  // nombre de sons dans la piste
    sound_t** sounds;  // liste des sons
} track_t;

/* structure représentant un morceau */
typedef struct mix {
    int n_tracks; // nombre de pistes
    track_t** tracks; // liste des pistes
    float* vols; // liste des volumes des pistes
} mix_t;

/* libère la mémoire allouée pour le son pointé par `p` */
void free_sound(sound_t* p);

/* libère la mémoire allouée pour la piste pointée par `p` */
void free_track(track_t* p);

/* libère la mémoire allouée pour le morceau pointé par `p` */
void free_mix(mix_t* p);

/* réduit un morceau en un seul son */
sound_t* reduce_track(track_t* t);

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

