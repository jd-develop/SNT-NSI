#include <stdlib.h>
#include "sound.h"

void free_sound(sound_t* p) {
    free(p->samples);
    free(p);
}

