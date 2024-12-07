#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
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

void test_reduce_track() {
    track_t* t = malloc(sizeof(track_t));
    sound_t* sound1 = malloc(sizeof(sound_t));
    sound_t* sound2 = malloc(sizeof(sound_t));

    sound1->n_samples = 2;
    sound1->samples = malloc(2*sizeof(int16_t));
    sound1->samples[0] = 1;
    sound1->samples[1] = 2;

    sound2->n_samples = 3;
    sound2->samples = malloc(3*sizeof(int16_t));
    sound2->samples[0] = 3;
    sound2->samples[1] = 4;
    sound2->samples[2] = 5;

    t->n_sounds = 2;
    t->sounds = malloc(2*sizeof(sound_t*));
    t->sounds[0] = sound1;
    t->sounds[1] = sound2;

    sound_t* reduced = reduce_track(t);

    assert(reduced->n_samples == 5);
    for (int i = 0; i < 5; i++) {
        assert(reduced->samples[i] == i+1);
    }
    free_track(t);
    free_sound(reduced);
}

sound_t* reduce_mix(mix_t* t) {
    // il faut d’abord réduire chaque piste du morceau en un seul son
    sound_t** sounds = malloc((t->n_tracks)*sizeof(sound_t*));

    /*
     * On en profite pour trouver la longueur totale du son final, qui n’est
     * autre que la longueur maximale parmi tous les sons, et aussi pour
     * trouver la somme des volumes
     */
    int total_size = 0;
    float volume_sum = 0;
    // Cette boucle est en O(n)
    for (int i = 0; i < t->n_tracks; i++) {
        sounds[i] = reduce_track(t->tracks[i]);

        if (sounds[i]->n_samples > total_size)
            total_size = sounds[i]->n_samples;
        volume_sum += t->vols[i];
    }

    // on alloue la mémoire du nouveau son
    sound_t* res = malloc(sizeof(sound_t));
    res->n_samples = total_size;
    res->samples = malloc(total_size * sizeof(int16_t));

    // On fait la moyenne de chaque échantillon
    float volume;
    long int mean;
    // Cette boucle est en O(n*max(l₁, l₂, …))
    // on parcourt pour chaque échantillon
    for (int i = 0; i < total_size; i++) {
        /*
         * On parcourt chaque son et on rajoute à la moyenne, mais il ne faut
         * pas que la longueur totale excède celle du son !
         */
        // Cette boucle est en O(n)
        mean = 0;
        for (int j = 0; j < t->n_tracks; j++) {
            if (sounds[j]->n_samples <= i) {
                continue;
            }
            volume = t->vols[j];
            mean += volume*(sounds[j]->samples[i]);
        }
        mean /= volume_sum;
        /*
         * on s’occupe maintenant des dépassements d’entiers : si ça dépasse,
         * on met juste à la valeur maximum
         */
        if (!(-32768 <= mean && mean <= 32767)) {
            if (mean < -32768)
                mean = -32768;
            else
                mean = 32767;
        }
        res->samples[i] = mean;
    }

    // On libère toute la mémoire dont on n’a plus besoin.
    // Cette boucle est en O(n).
    for (int i = 0; i < t->n_tracks; i++) {
        free_sound(sounds[i]);
    }
    free(sounds);

    return res;
}

void test_reduce_mix() {
    mix_t* m = malloc(sizeof(mix_t));

    track_t* t1 = malloc(sizeof(track_t));
    sound_t* sound1 = malloc(sizeof(sound_t));
    sound_t* sound2 = malloc(sizeof(sound_t));

    sound1->n_samples = 2;
    sound1->samples = malloc(2*sizeof(int16_t));
    sound1->samples[0] = 1;
    sound1->samples[1] = 2;

    sound2->n_samples = 3;
    sound2->samples = malloc(3*sizeof(int16_t));
    sound2->samples[0] = 3;
    sound2->samples[1] = 4;
    sound2->samples[2] = 5;

    t1->n_sounds = 2;
    t1->sounds = malloc(2*sizeof(sound_t*));
    t1->sounds[0] = sound1;
    t1->sounds[1] = sound2;

    track_t* t2 = malloc(sizeof(track_t));
    sound_t* sound3 = malloc(sizeof(sound_t));
    sound_t* sound4 = malloc(sizeof(sound_t));

    sound3->n_samples = 1;
    sound3->samples = malloc(1*sizeof(int16_t));
    sound3->samples[0] = 3;

    sound4->n_samples = 2;
    sound4->samples = malloc(2*sizeof(int16_t));
    sound4->samples[0] = 3;
    sound4->samples[1] = 4;

    t2->n_sounds = 2;
    t2->sounds = malloc(2*sizeof(sound_t*));
    t2->sounds[0] = sound3;
    t2->sounds[1] = sound4;

    m->n_tracks = 2;
    m->vols = malloc(2*sizeof(float));
    m->vols[0] = 1;
    m->vols[1] = 2;
    m->tracks = malloc(2*sizeof(track_t*));

    m->tracks[0] = t1;
    m->tracks[1] = t2;

    sound_t* reduced = reduce_mix(m);

    assert(reduced->n_samples == 5);
    assert(reduced->samples[0] == 2); // (1+2×3)/3
    assert(reduced->samples[1] == 2); // (2+2×3)/3
    assert(reduced->samples[2] == 3); // (3+2×4)/3
    assert(reduced->samples[3] == 1); // (4+2×0)/3
    assert(reduced->samples[4] == 1); // (5+2×0)/3

    free_mix(m);
    free_sound(reduced);
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
