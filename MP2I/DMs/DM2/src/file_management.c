#include <stdio.h>
#include <assert.h>

typedef unsigned char uchar;

void write_int(FILE* f, int a, int size) {
    assert(1 <= size && size <= 4);

    for (int i = 0; i < size; i++) {
        fprintf(f, "%c", a%256);
        a = a >> 8;
    }
}

void test_write_int() {
    FILE* fp = fopen("/tmp/vlc++tests.write_int", "w");
    assert(fp != NULL); // normalement on a toujours le droit d’écrire dans /tmp

    write_int(fp, 0x12345678, 4);
    write_int(fp, 0xABCDEF, 3);
    write_int(fp, 0x12345, 3);
    write_int(fp, 0xABCD, 2);
    write_int(fp, 0x12, 1);
    write_int(fp, 0x1, 1);
    write_int(fp, 0, 1);

    fclose(fp);

    fp = fopen("/tmp/vlc++tests.write_int", "r");
    assert(fp != NULL);

    uchar expected_bytes[15] = {0x78, 0x56, 0x34, 0x12, 0xEF, 0xCD, 0xAB, 0x45,
                                0x23, 0x01, 0xCD, 0xAB, 0x12, 0x1, 0};
    uchar current;
    for (int i = 0; i < 15; i++) {
        assert(fscanf(fp, "%c", &current) != EOF);
        printf("c %d e %d\n", current, expected_bytes[i]);
        assert(current == expected_bytes[i]);
    }
    fclose(fp);
}

