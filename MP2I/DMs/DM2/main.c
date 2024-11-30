#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "src/run_tests.h"
#include "src/sound.h"
#include "src/wav.h"
#include "src/melody.h"

int main(int argc, char* argv[]) {
    srand(time(NULL)); // au cas où on utilise la fonction « white »
    run_tests();

    if (argc != 3) {
        fprintf(stderr, "Merci de donner exactement 2 paramètres (fichier "
                        "source et fichier destination)\n");
        return 1;
    }
    char* src_file = argv[1];
    char* dst_file = argv[2];

    mix_t* mix = load_mix(src_file);
    if (mix == NULL) {
        return 1;
    }

    sound_t* sound = reduce_mix(mix);

    if (save_sound(dst_file, sound) == 1) {
        fprintf(
            stderr,
            "Erreur d’ouverture de « %s » : assurez-vous que vous avez "
            "les permissions d’écrire dans ce fichier.\n",
            dst_file
        );
        free_mix(mix);
        free_sound(sound);
        return 1;
    }

    free_mix(mix);
    free_sound(sound);

    return 0;
}

    /* à partir d’ici, tous les petits tests avant l’implémentation de la
     * lecture des arguments en ligne de commande (c’était dans la fonction
     * main)
     *

    int16_t* samples = malloc(3*sizeof(int16_t));
    samples[0] = 15387;
    samples[1] = 815;
    samples[2] = -6337;

    sound_t* s_test = malloc(sizeof(sound_t));
    s_test->n_samples = 3;
    s_test->samples = samples;

    save_sound("test.wav", s_test);

    free_sound(s_test);

    sound_t* s_white = white(5.0, 44100);
    save_sound("white.wav", s_white);
    free_sound(s_white);

    sound_t* s_440 = sine(440, 8000, 5.0, 44100);
    save_sound("la440.wav", s_440);
    free_sound(s_440);

    sound_t* s_440s = square(440, 8000, 5.0, 44100);
    save_sound("la440s.wav", s_440s);
    free_sound(s_440s);

    sound_t* s_440t = triangle(440, 8000, 5.0, 44100);
    save_sound("la440t.wav", s_440t);
    free_sound(s_440t);

    sound_t* s_440sa = sawtooth(440, 8000, 5.0, 44100);
    save_sound("la440sa.wav", s_440sa);
    free_sound(s_440sa);

    sound_t** lune_sounds = malloc(9*sizeof(sound_t));
    lune_sounds[0] = sawtooth(440, 0,     0.5, 44100);
    lune_sounds[1] = sawtooth(440, 16000, 0.4, 44100);
    lune_sounds[2] = sawtooth(440, 0,     0.1, 44100);
    lune_sounds[3] = sawtooth(440, 16000, 0.4, 44100);
    lune_sounds[4] = sawtooth(440, 0,     0.1, 44100);
    lune_sounds[5] = sawtooth(440, 16000, 0.5, 44100);

    lune_sounds[6] = sawtooth(493.88, 16000, 0.5, 44100);
    lune_sounds[7] = sawtooth(554.36, 16000, 1, 44100);
    lune_sounds[8] = sawtooth(493.88, 16000, 1, 44100);

    track_t* au_clair_de_la_lune = malloc(sizeof(track_t));

    au_clair_de_la_lune->n_sounds = 9;
    au_clair_de_la_lune->sounds = lune_sounds;

    sound_t* au_clair_de_la_lune_one_sound = reduce_track(au_clair_de_la_lune);
    save_sound("au_clair_de_la_lune.wav", au_clair_de_la_lune_one_sound);

    free_track(au_clair_de_la_lune);
    free_sound(au_clair_de_la_lune_one_sound);

    FILE* sonata_fp = fopen("../examples/sonata_1_piste.txt", "r");
    track_t* sonata = read_track(sonata_fp);
    sound_t* sonata_s = reduce_track(sonata);
    save_sound("sonata.wav", sonata_s);
    free_track(sonata);
    free_sound(sonata_s);

    mix_t* sonata_2v = load_mix("../examples/sonata_2_pistes.txt");
    sound_t* sonata_2vs = reduce_mix(sonata_2v);
    save_sound("sonata2v.wav", sonata_2vs);
    free_mix(sonata_2v);
    free_sound(sonata_2vs);

    *
    */
