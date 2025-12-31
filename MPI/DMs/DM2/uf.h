#ifndef UF_H
#define UF_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

struct uf_elem_s {
    int rank;
    int elem;
    struct uf_elem_s *parent;
};

typedef struct uf_elem_s *uf_elem_t;

typedef uf_elem_t *uf_partition_t;

/* déjà donné dans uf.c */
void print_uf_partition_verbose(uf_partition_t p, int n);

/* à implémenter dans uf.c */
uf_partition_t uf_initialize(int size);
void uf_free(uf_partition_t p, int size);
uf_elem_t uf_find_no(uf_elem_t x);
uf_elem_t uf_find(uf_elem_t x);
void uf_union(uf_elem_t x, uf_elem_t y);
uf_elem_t uf_find_no(uf_elem_t x);

/* --------------- bonus --------------- */
int find_idx_parent(uf_partition_t part, int i, int size);
void affiche_very_verbose(char *name, uf_partition_t part, int size);
#endif
