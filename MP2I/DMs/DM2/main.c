#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "src/file_management.h"
#include "src/run_tests.h"
#include "src/sound.h"
#include "src/wav.h"

int main() {
    printf("Hello, world!\n");
    printf("%f\n", sin(2*3.14159265));

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
}
