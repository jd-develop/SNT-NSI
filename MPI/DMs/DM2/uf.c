#include "uf.h"

void print_uf_partition_verbose(uf_partition_t p, int n) {
    // hypothèse : p est une partition de [0..n[
    // affiche pour chaque élém de [0..n[ la remontée jusqu'à une racine
    // dans la structure union find p
    for (int i = 0; i < n; i++) {
        uf_elem_t cursor = p[i];
        for (; cursor->parent != cursor; cursor = cursor->parent) {
            printf("%d ~> ", cursor->elem);
        };
        printf("%d", cursor->elem);
        printf("\n");
    }
}
