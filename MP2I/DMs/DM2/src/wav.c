#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "file_management.h"
#include "sound.h"
#define FREQ_ECH 44100

void write_header(FILE* f, int n) {
    fprintf(f, "%c%c%c%c", 'R', 'I', 'F', 'F');

    write_int(f, 36 + 2*n, 4);
    fprintf(f, "%c%c%c%c%c%c%c%c", 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ');

    write_int(f, 16, 4);
    write_int(f, 1, 2);
    write_int(f, 1, 2);
    write_int(f, FREQ_ECH, 4);
    write_int(f, FREQ_ECH*2, 4);
    write_int(f, 2, 2);
    write_int(f, 16, 2);

    fprintf(f, "%c%c%c%c", 'd', 'a', 't', 'a');
    write_int(f, 2*n, 4);
}

void save_sound(char* filename, sound_t* s) {
    FILE* fp = fopen(filename, "w");
    assert(fp != NULL);
    write_header(fp, s->n_samples);
    for (int i = 0; i < s->n_samples; i++) {
        // printf("i=%d samples[i]=%d\n", i, s->samples[i]);
        write_int(fp, s->samples[i], 2);
    }
    fclose(fp);
}

