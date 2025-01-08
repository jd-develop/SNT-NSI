#include <stdio.h>
#include <assert.h>
#include "file.h"


int main() {
    file_t* f = file_vide();
    assert(est_file_vide(f));

    affiche_file(f);
    enfiler(f, 1);
    assert(!est_file_vide(f));
    affiche_file(f);

    for (int i = 2; i < 15; i++) {
        enfiler(f, i);
        assert(!est_file_vide(f));
    }
    affiche_file(f);
    for (int i = 1; i < 15; i++) {
        assert(defiler(f) == i);
    }
    affiche_file(f);
    assert(est_file_vide(f));
    free_file(f);
}
