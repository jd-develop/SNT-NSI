#include "uf.h"
#include <stdlib.h>

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

/* Crée et renvoie une structure UnionFind représentant la partition de
 * [[0, size-1]] en singletons. */
uf_partition_t uf_initialize(int size) {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * size);
    for (int i = 0; i < size; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
        res[i]->rank = 0;
        res[i]->parent = res[i];
        res[i]->elem = i;
    }
    return res;
}

/* Libère toute la mémoire allouée à l’UnionFind tab de taille size */
void uf_free(uf_partition_t tab, int size) {
    for (int i = 0; i < size; i++) {
        free(tab[i]);
    }
    free(tab);
}

/* Renvoie le nœud du représentant de la classe de x, sans modifier la
 * structure */
uf_elem_t uf_find_no(uf_elem_t x) {
    if (x->parent == x) {
        return x;
    } else {
        return uf_find_no(x->parent);
    }
}

/* Renvoie le nœud du représentant de la classe de x, en modifiant la structure
 * en faisant de la compression de chemins */
uf_elem_t uf_find(uf_elem_t x) {
    if (x->parent == x) {
        return x;
    } else {
        uf_elem_t rep = uf_find(x->parent);
        if (rep != x->parent)
            x->parent = rep;
        return rep;
    }
}

/* Réunit les classes de a et de b */
void uf_union(uf_elem_t a, uf_elem_t b) {
    uf_elem_t x = uf_find(a);
    uf_elem_t y = uf_find(b);
    if (x != y) {
        if (x->rank == y->rank) {
            x->parent = y;
            y->rank++;
        } else if (x->rank < y->rank) {
            x->parent = y;
        } else {
            y->parent = x;
        }
    }
}
