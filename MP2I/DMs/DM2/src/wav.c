#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "sound.h"
#include "wav.h"
#include "constants.h"

typedef unsigned char uchar;

void write_int(FILE* f, int a, int size) {
    assert(1 <= size && size <= 4);

    /*
     * il suffit d’écrire à chaque fois les 8 derniers bits, puis de décaler à
     * droite
     */
    for (int i = 0; i < size; i++) {
        fprintf(f, "%c", a%256);
        a = a >> 8;
    }
}

void test_write_int() {
    FILE* fp = fopen("/tmp/dm2tests.write_int", "w");
    assert(fp != NULL); // normalement on a toujours le droit d’écrire dans /tmp

    write_int(fp, 0x12345678, 4);
    write_int(fp, 0xABCDEF, 3);
    write_int(fp, 0x12345, 3);
    write_int(fp, 0xABCD, 2);
    write_int(fp, 0x12, 1);
    write_int(fp, 0x1, 1);
    write_int(fp, 0, 1);

    fclose(fp);

    fp = fopen("/tmp/dm2tests.write_int", "r");
    assert(fp != NULL);

    uchar expected_bytes[15] = {0x78, 0x56, 0x34, 0x12, 0xEF, 0xCD, 0xAB, 0x45,
                                0x23, 0x01, 0xCD, 0xAB, 0x12, 0x1, 0};
    uchar current;
    for (int i = 0; i < 15; i++) {
        assert(fscanf(fp, "%c", &current) != EOF);
        assert(current == expected_bytes[i]);
    }
    fclose(fp);
}

void write_header(FILE* f, int n) {
    // RIFF
    fprintf(f, "%c%c%c%c", 'R', 'I', 'F', 'F');

    // nombre d’octets dans le fichier après ce champ
    write_int(f, 36 + 2*n, 4);

    // WAVEfmt[espace]
    fprintf(f, "%c%c%c%c%c%c%c%c", 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ');

    write_int(f, 16, 4);
    write_int(f, 1, 2);
    write_int(f, 1, 2);
    // fréquence d’échantillonage
    write_int(f, FREQ_ECH, 4);
    // octets nécessaires par seconde de son
    write_int(f, FREQ_ECH*2, 4);
    // octets par échantillon
    write_int(f, 2, 2);
    // bits par échantillon
    write_int(f, 16, 2);

    // data
    fprintf(f, "%c%c%c%c", 'd', 'a', 't', 'a');
    // nombre d’octets dans le fichier après ce champ
    write_int(f, 2*n, 4);
}

void test_write_header() {
    FILE* fp = fopen("/tmp/dm2tests.write_header", "w");
    assert(fp != NULL); // normalement on a toujours le droit d’écrire dans /tmp

    write_header(fp, 3);

    fclose(fp);

    fp = fopen("/tmp/dm2tests.write_header", "r");
    assert(fp != NULL);

    uchar expected_bytes[44] = {
        'R', 'I', 'F', 'F', 42, 0, 0, 0,
        'W', 'A', 'V', 'E', 'f', 'm', 't', ' ',
        16, 0, 0, 0,
        0x1, 0x0, 0x1, 0x0,
        0x44, 0xac, 0x0, 0x0,
        0x88, 0x58, 0x1, 0x0,
        2, 0,
        16, 0,
        'd', 'a', 't', 'a',
        6, 0, 0, 0
    };
    uchar current;
    for (int i = 0; i < 44; i++) {
        assert(fscanf(fp, "%c", &current) != EOF);
        assert(current == expected_bytes[i]);
    }

    fclose(fp);
}

int save_sound(char* filename, sound_t* s) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        return 1;
    }

    // on écrit le header puis les valeurs
    write_header(fp, s->n_samples);
    for (int i = 0; i < s->n_samples; i++) {
        // printf("i=%d samples[i]=%d\n", i, s->samples[i]);
        write_int(fp, s->samples[i], 2);
    }

    fclose(fp);
    return 0;
}

