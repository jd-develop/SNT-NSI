#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "melody.h"
#include "new_melody.h"
#include "constants.h"

track_t* new_load_track(FILE* fp, int tempo) {
    assert(fp != NULL);

    // on alloue la mémoire nécessaire
    int n_notes;
    char instrument[MAX_INSTRUMENT_NAME_SIZE];

    // on initialise toutes les variables
    int pitch;
    char nom_note[50];
    float freq;
    char duree_str[50];
    float duree;
    float volume;
    int amplitude;
    sound_t* sound;

    // on commence par lire la première ligne
    if (fscanf(fp, "%d %s", &n_notes, instrument) < 2) {
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
        if (fscanf(fp, "%s %s %f", nom_note, duree_str, &volume) < 3) {
            fprintf(
                stderr,
                "Erreur : %d notes attendues, %d réellement lues\n",
                n_notes, i
            );
            return NULL;
        }
        pitch = note_to_pitch(nom_note);
        if (pitch == -10000) {
            fprintf(stderr, "Erreur : la note %s n’existe pas\n", nom_note);
            return NULL;
        }
        freq = pitch_to_freq(pitch);
        amplitude = (int)(32767*volume);
        duree = note_to_duree(duree_str, tempo);
        if (duree == -1) {
            fprintf(stderr, "Erreur : la note %s n’existe pas\n", duree_str);
            return NULL;
        }

        // on appelle la bonne fonction en fonction de l’instument
        switch (instrument_n) {
            case 's':
                sound = sine(freq, amplitude, duree, FREQ_ECH);
                break;
            case 'c':
                sound = square(freq, amplitude, duree, FREQ_ECH);
                break;
            case 't':
                sound = triangle(freq, amplitude, duree, FREQ_ECH);
                break;
            case 'd':
                sound = sawtooth(freq, amplitude, duree, FREQ_ECH);
                break;
        }

        // on ajoute le son à la piste
        res->sounds[i] = sound;
    }

    return res;
}

mix_t* new_load_mix(FILE* fp) {
    assert(fp != NULL);

    int tempo;
    char* expected = "\ntempo";
    char current;
    for (int i = 0; i < 6; i++) {
        if (fscanf(fp, "%c", &current) == EOF || current != expected[i]) {
            fprintf(stderr, "Erreur de lecture du fichier : merci d’écrire "
                            "« tempo » et de spécifier le tempo du morceau.\n");
            fclose(fp);
            return NULL;
        }
    }

    if (fscanf(fp, "%d", &tempo) == EOF) {
        fprintf(stderr, "Erreur de lecture du fichier : merci d’écrire "
                        "« tempo » et de spécifier le tempo du morceau.\n");
        fclose(fp);
        return NULL;
    }

    int n_tracks;
    if (fscanf(fp, "%d", &n_tracks) == EOF) {
        fprintf(stderr, "Erreur de lecture du fichier : la troisième ligne "
                        "doit être constituée du nombre de pistes (voix) du"
                        "morceau.\n");
        fclose(fp);
        return NULL;
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
        trackp = new_load_track(fp, tempo);
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

float note_to_duree(char* note, int tempo) {
    float duree_temps = 60.0/((float)tempo);
    float temps;
    if (strcmp(note, "ronde") == 0)
        temps = 4;
    else if (strcmp(note, "rondepointee") == 0)
        temps = 6;
    else if (strcmp(note, "blanche") == 0)
        temps = 2;
    else if (strcmp(note, "blanchepointee") == 0)
        temps = 3;
    else if (strcmp(note, "noire") == 0)
        temps = 1;
    else if (strcmp(note, "noirepointee") == 0)
        temps = 1.5;
    else if (strcmp(note, "croche") == 0)
        temps = 0.5;
    else if (strcmp(note, "crochepointee") == 0)
        temps = 0.75;
    else if (strcmp(note, "triolet") == 0)
        temps = 0.333333333333;
    else if (strcmp(note, "doublecroche") == 0)
        temps = 0.25;
    else if (strcmp(note, "doublecrochepointee") == 0)
        temps = 0.375;
    else if (strcmp(note, "triplecroche") == 0)
        temps = 0.125;
    else if (strcmp(note, "triplecrochepointee") == 0)
        temps = 0.1875;
    else if (strcmp(note, "quadruplecroche") == 0)
        temps = 0.0625;
    else if (strcmp(note, "quadruplecrochepointee") == 0)
        temps = 0.09375;
    else
        return -1;

    return temps*duree_temps;
}

int note_to_pitch(char* note) {
    int pitch_central;
    if (strlen(note) < 2) {
        return -10000;
    }
    int oct_start_idx; // l’index à lire après le nom de la note

    if (note[0] == 'd' && note[1] == 'o') {
        pitch_central = -9;
        oct_start_idx = 2;
    } else if (note[0] == 'r' && note[1] == 'e') {
        pitch_central = -7;
        oct_start_idx = 2;
    } else if (note[0] == 'm' && note[1] == 'i') {
        pitch_central = -5;
        oct_start_idx = 2;
    } else if (note[0] == 'f' && note[1] == 'a') {
        pitch_central = -4;
        oct_start_idx = 2;
    } else if (strlen(note) >= 3 && note[0] == 's' && note[1] == 'o' &&
               note[2] == 'l') {
        pitch_central = -2;
        oct_start_idx = 3;
    } else if (note[0] == 'l' && note[1] == 'a') {
        pitch_central = 0;
        oct_start_idx = 2;
    } else if (note[0] == 's' && note[1] == 'i') {
        pitch_central = 2;
        oct_start_idx = 2;
    } else {
        return -10000;
    }

    if (note[oct_start_idx] == '#') {
        pitch_central++;
        oct_start_idx++;
    } else if (note[oct_start_idx] == 'b') {
        pitch_central--;
        oct_start_idx++;
    }

    char octave[50];
    int i = oct_start_idx;
    while (note[i] != '\0') {
        octave[i-oct_start_idx] = note[i];
        i++;
    }
    octave[i-oct_start_idx] = '\0';

    int octave_i = atoi(octave); // de toute façon en cas d’erreur, ce sera 0
    int pitch = pitch_central + 12*octave_i;
    return pitch;
}

void test_note_to_pitch() {
    assert(note_to_pitch("la") == 0);
    assert(note_to_pitch("la#") == 1);
    assert(note_to_pitch("lab") == -1);
    assert(note_to_pitch("do") == -9);
    assert(note_to_pitch("do1") == note_to_pitch("si#"));
    assert(note_to_pitch("do-1")+12 == note_to_pitch("reb")-1);
    assert(note_to_pitch("do1")-12 == note_to_pitch("si#-1"));
    assert(note_to_pitch("test") == -10000);
    assert(note_to_pitch("") == -10000);
    assert(note_to_pitch("a") == -10000);
}

