#include <stdio.h>
#include <assert.h>
#include "pile.h"

int main() {
    pile_t* p = pile_vide();
    assert(est_vide(p));

    print_pile(p);
    empiler(p, 1);
    assert(!est_vide(p));
    print_pile(p);

    for (int i = 2; i < 15; i++) {
        empiler(p, i);
        assert(!est_vide(p));
    }
    print_pile(p);
    for (int i = 14; i > 0; i--) {
        assert(depiler(p) == i);
    }
    print_pile(p);
    assert(est_vide(p));
    free_pile(p);
}
