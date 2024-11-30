#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "sound.h"

#define PI 3.1415926535897932384626
#define DEUXSURPI 0.6366197723675814

void free_sound(sound_t* p) {
    free(p->samples);
    free(p);
}

void free_track(track_t* p) {
    // on libère chaque son
    for (int i = 0; i < p->n_sounds; i++) {
        free_sound(p->sounds[i]);
    }
    free(p->sounds);
    free(p);
}

void free_mix(mix_t* p) {
    // on libère chaque piste
    for (int i = 0; i < p->n_tracks; i++) {
        free_track(p->tracks[i]);
    }
    free(p->tracks);
    free(p->vols);
    free(p);
}

sound_t* reduce_track(track_t* t) {
    // on calcule la taille totale que fera le son final
    int total_size = 0;
    for (int i = 0; i < t->n_sounds; i++) {
        total_size += t->sounds[i]->n_samples;
    }

    // on alloue la mémoire pour stocker le son final
    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = total_size;
    res->samples = malloc(total_size * sizeof(int16_t));

    // on ajoute les sons les uns à la suite des autres
    int total_index = 0;
    for (int i = 0; i < t->n_sounds; i++) {
        for (int j = 0; j < t->sounds[i]->n_samples; j++) {
            res->samples[total_index] = t->sounds[i]->samples[j];
            total_index++;
        }
    }
    return res;
}

sound_t* white(float duree, int f_ech) {
    int n = (int)f_ech*duree;

    // on alloue la mémoire pour stocker le son
    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = n;
    res->samples = malloc(n * sizeof(int16_t));
    int16_t r;

    for (int i = 0; i < n; i++) {
        // valeurs aléatoires
        r = rand() % 65536 - 32768;
        //r = rand() % (8492) - 4096; // c’est moins fort :)
        res->samples[i] = r;
    }

    return res;
}

sound_t* sine(float freq, int amplitude, float duree, int f_ech) {
    int n = (int)f_ech*duree;

    // on alloue la mémoire pour stocker le son
    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = n;
    res->samples = malloc(n * sizeof(int16_t));

    int16_t u;
    double w = 2*PI*freq*(1/(double)f_ech);

    for (int i = 0; i < n; i++) {
        u = amplitude * sin(i*w);
        res->samples[i] = u;
    }

    return res;
}

sound_t* square(float freq, int amplitude, float duree, int f_ech) {
    int n = (int)f_ech*duree;

    // on alloue la mémoire pour stocker le son
    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = n;
    res->samples = malloc(n * sizeof(int16_t));

    int16_t u;
    double w = 2*PI*freq*(1/(double)f_ech);

    for (int i = 0; i < n; i++) {
        // on prend le signe du sinus, i.e. le sinus sur sa valeur absolue
        u = amplitude * (sin(i*w)/fabs(sin(i*w)));
        res->samples[i] = u;
    }

    return res;
}

sound_t* triangle(float freq, int amplitude, float duree, int f_ech) {
    int n = (int)f_ech*duree;

    // on alloue la mémoire pour stocker le son
    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = n;
    res->samples = malloc(n * sizeof(int16_t));

    int16_t u;
    double w = 2*PI*freq*(1/(double)f_ech);

    for (int i = 0; i < n; i++) {
        // d’après wikipédia, y(x) = 2a/π * arcsin(sin(i×w))…
        u = DEUXSURPI * amplitude * asin(sin(i*w));
        res->samples[i] = u;
    }

    return res;
}

sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech) {
    int n = (int)f_ech*duree;

    // on alloue la mémoire pour stocker le son
    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = n;
    res->samples = malloc(n * sizeof(int16_t));

    int16_t u;
    double w = freq*(1/(double)f_ech);

    for (int i = 0; i < n; i++) {
        // toujours d’après wikipédia, y(x) = 2a * (i*w - ⌊1/2 + i*w⌋)
        u = amplitude*2*(i*w - floor(0.5 + i*w));
        res->samples[i] = u;
    }

    return res;
}
