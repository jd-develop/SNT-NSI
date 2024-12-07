#include "melody.h"
#include "wav.h"
#include "sound.h"
#include "new_melody.h"

void run_tests() {
    // src/melody
    test_pitch_to_freq();

    // src/new_melody
    test_note_to_pitch();

    // src/sound
    test_reduce_track();
    test_reduce_mix();

    // src/wav
    test_write_int();
    test_write_header();
}
