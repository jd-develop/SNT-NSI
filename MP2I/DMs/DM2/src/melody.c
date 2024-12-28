#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "melody.h"
#include "new_melody.h"
#include "sound.h"
#include "constants.h"

float pitch_to_freq(int pitch) {
    return 440 * pow(2, ((float)pitch)/12);
}

void test_pitch_to_freq() {
    assert(pitch_to_freq(-12) == 220);
    assert(pitch_to_freq(0) == 440);
    assert(pitch_to_freq(12) == 880);
}

track_t* read_track(FILE* file) {
    assert(file != NULL);

    // on alloue la mémoire nécessaire
    int n_notes;
    char instrument[MAX_INSTRUMENT_NAME_SIZE];

    // on initialise toutes les variables
    int pitch;
    float freq;
    float duree;
    float volume;
    int amplitude;
    sound_t* sound;

    // on commence par lire la première ligne
    if (fscanf(file, "%d %s", &n_notes, instrument) == EOF) {
        fprintf(
            stderr,
            "Erreur de lecture du fichier : nombre de notes et instrument "
            "attendus.\n"
        );
        return NULL;
    }

    /*
     * pour accélerer, on peut à chaque instrument associer un numéro (comme ça,
     * on n’aura pas à appeller strcmp à chaque tour de boucle)
     */
    char instrument_n = instrument_to_byte(instrument);
    if (instrument_n == 0) {
        return NULL;
    }

    // on initialise la piste à renvoyer
    track_t* res = malloc(sizeof(track_t));
    res->n_sounds = n_notes;
    res->sounds = malloc(n_notes * sizeof(sound_t*));

    for (int i = 0; i < n_notes; i++) {
        // on lit une ligne
        if (fscanf(file, "%d %f %f", &pitch, &duree, &volume) == EOF) {
            fprintf(
                stderr,
                "Erreur : %d notes attendues, %d réellement lues\n",
                n_notes, i
            );
            return NULL;
        }
        if (volume < 0 || volume > 1) {
            /* le volume doit être compris entre 0 et 1 */
            fprintf(
                stderr,
                "Erreur : le volume '%f' est invalide, car il n’est pas "
                "compris entre 0 et 1.\n",
                volume
            );
            return NULL;
        }
        freq = pitch_to_freq(pitch);
        amplitude = (int)(32767*volume);

        // on appelle la bonne fonction en fonction de l’instument
        switch (instrument_n) {
            case 's':
                sound = sine(freq, amplitude, duree, FREQ_ECH, false);
                break;
            case 'c':
                sound = square(freq, amplitude, duree, FREQ_ECH, false);
                break;
            case 't':
                sound = triangle(freq, amplitude, duree, FREQ_ECH, false);
                break;
            case 'd':
                sound = sawtooth(freq, amplitude, duree, FREQ_ECH, false);
                break;
            case 'S':
                sound = sine(freq, amplitude, duree, FREQ_ECH, true);
                break;
            case 'C':
                sound = square(freq, amplitude, duree, FREQ_ECH, true);
                break;
            case 'T':
                sound = triangle(freq, amplitude, duree, FREQ_ECH, true);
                break;
            case 'D':
                sound = sawtooth(freq, amplitude, duree, FREQ_ECH, true);
                break;
        }

        // on ajoute le son à la piste
        res->sounds[i] = sound;
    }

    return res;
}

char instrument_to_byte(char* instrument) {
    char instrument_n;
    if (strcmp(instrument, "sine") == 0) {
        instrument_n = 's'; // sinus
    } else if (strcmp(instrument, "square") == 0) {
        instrument_n = 'c'; // carré
    } else if (strcmp(instrument, "triangle") == 0) {
        instrument_n = 't'; // triangle
    } else if (strcmp(instrument, "sawtooth") == 0) {
        instrument_n = 'd'; // dent de scie
    } else if (strcmp(instrument, "sineadsr") == 0) {
        instrument_n = 'S'; // sinus ADSR
    } else if (strcmp(instrument, "squareadsr") == 0) {
        instrument_n = 'C'; // carré ADSR
    } else if (strcmp(instrument, "triangleadsr") == 0) {
        instrument_n = 'T'; // triangle ADSR
    } else if (strcmp(instrument, "sawtoothadsr") == 0) {
        instrument_n = 'D'; // dent de scie ADSR
    } else {
        fprintf(stderr, "Erreur, l’instrument « %s » n’existe pas !\n",
                instrument);
        return 0;
    }
    return instrument_n;
}

mix_t* load_mix(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Erreur lors de l’ouverture du fichier %s.\n",
                filename);
        fprintf(stderr, "Assurez-vous que le fichier existe et que vous avez "
                        "les permissions suffisantes pour le lire.\n");
        return NULL;
    }

    // on lit le nombre de pistes
    int n_tracks;
    if (fscanf(fp, "%d", &n_tracks) == EOF) {
        fprintf(stderr, "Erreur de lecture du fichier : la première ligne "
                        "doit être constituée du nombre de pistes (voix) du"
                        "morceau.\n");
        fclose(fp);
        return NULL;
    }

    if (n_tracks < 0) { // nouveau format de fichier : on passe la main
        return new_load_mix(fp);
    }

    float volume;
    float* volumes = malloc(n_tracks*sizeof(float));

    // on lit les volumes
    for (int i = 0; i < n_tracks; i++) {
        if (fscanf(fp, "%f", &volume) == EOF) {
            fprintf(
                stderr,
                "Erreur de lecture du fichier : il doit y avoir autant de "
                "volumes que de pistes (voix).\n"
            );
            fclose(fp);
            free(volumes);
            return NULL;
        }
        volumes[i] = volume;
    }

    track_t** tracks = malloc(n_tracks*sizeof(tracks));
    track_t* trackp;

    // on lit les pistes
    for (int i = 0; i < n_tracks; i++) {
        trackp = read_track(fp);
        if (trackp == NULL) {
            fclose(fp);
            free(volumes);
            for (int j = 0; j < i; j++)
                free_track(tracks[j]);
            free(tracks);
            return NULL;
        }
        tracks[i] = trackp;
    }

    // on créée le mix
    mix_t* mix = malloc(sizeof(mix_t));
    mix->n_tracks = n_tracks;
    mix->vols = volumes;
    mix->tracks = tracks;

    fclose(fp);
    return mix;
}
