#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "src/file_management.h"
#include "src/run_tests.h"
#include "src/sound.h"
#include "src/wav.h"

int main() {
    srand(time(NULL));
    run_tests();

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
}
