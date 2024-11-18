#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "sound.h"

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

