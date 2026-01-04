#include "uf.h"

uf_partition_t exemple() {
    // crée la partition donnée en exemple dans l'énoncé du DM
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 11);
    for (int i = 0; i < 11; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
        res[i]->elem = i;
        res[i]->rank = 0;
    }
    res[0]->parent = res[5];
    res[1]->parent = res[2];
    res[2]->parent = res[7];
    res[3]->parent = res[7];
    res[4]->parent = res[4];
    res[5]->parent = res[5];
    res[6]->parent = res[6];
    res[7]->parent = res[7];
    res[8]->parent = res[4];
    res[9]->parent = res[4];
    res[10]->parent = res[4];

    res[2]->rank = 1;
    res[7]->rank = 2;
    res[5]->rank = 1;
    res[4]->rank = 1;

    return res;
}

int main() {
    uf_partition_t ex = exemple();
    print_uf_partition_verbose(ex, 11);
    uf_free(ex, 11);
}
