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

sound_t* white(float duree, int f_ech) {
    int n = (int)f_ech*duree;

    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = n;
    res->samples = malloc(n * sizeof(int16_t));
    int16_t r;

    for (int i = 0; i < n; i++) {
        r = rand() % 65536 - 32768;
        //r = rand() % (8492) - 4096; // c’est moins fort :)
        res->samples[i] = r;
    }

    return res;
}

sound_t* sine(float freq, int amplitude, float duree, int f_ech) {
    int n = (int)f_ech*duree;

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

    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = n;
    res->samples = malloc(n * sizeof(int16_t));

    int16_t u;
    double w = 2*PI*freq*(1/(double)f_ech);

    for (int i = 0; i < n; i++) {
        // d’après wikipédia, y(x) = 2a/π * arcsin(sin(i*w))…
        u = DEUXSURPI * amplitude * asin(sin(i*w));
        res->samples[i] = u;
    }

    return res;
}

sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech) {
    int n = (int)f_ech*duree;

    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = n;
    res->samples = malloc(n * sizeof(int16_t));

    int16_t u;
    double w = freq*(1/(double)f_ech);

    for (int i = 0; i < n; i++) {
        // toujours d’après wikipédia, y(x) = 2a * (i*w - ent(1/2 + i*w))
        u = amplitude*2*(i*w - floor(0.5 + i*w));
        res->samples[i] = u;
    }

    return res;
}
