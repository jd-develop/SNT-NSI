#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "melody.h"
#include "sound.h"

float pitch_to_freq(int pitch) {
    return 440 * pow(2, ((float)pitch)/12);
}

track_t* read_track(FILE* file) {
    assert(file != NULL);

    track_t* res = malloc(sizeof(track_t));
    int n_notes;
    char instrument[MAX_INSTRUMENT_NAME_SIZE];

    int pitch;
    float freq;
    float duree;
    float volume;
    int amplitude;
    sound_t* sound;

    // on commence par lire la première ligne
    assert(fscanf(file, "%d %s", &n_notes, instrument) != EOF);

    res->n_sounds = n_notes;
    res->sounds = malloc(n_notes * sizeof(sound_t*));

    for (int i = 0; i < n_notes; i++) {
        // on lit une ligne
        assert(fscanf(file, "%d %f %f", &pitch, &duree, &volume) != EOF);
        freq = pitch_to_freq(pitch);
        amplitude = (int)(32767*volume);

        if (strcmp(instrument, "sine") == 0) {
            sound = sine(freq, amplitude, duree, 44100);
        } else if (strcmp(instrument, "square") == 0) {
            sound = square(freq, amplitude, duree, 44100);
        } else if (strcmp(instrument, "triangle") == 0) {
            sound = triangle(freq, amplitude, duree, 44100);
        } else if (strcmp(instrument, "sawtooth") == 0) {
            sound = sawtooth(freq, amplitude, duree, 44100);
        } else {
            printf("Erreur, l’instrument « %s » n’existe pas !", instrument);
            assert(0);
        }

        res->sounds[i] = sound;
    }

    return res;
}
