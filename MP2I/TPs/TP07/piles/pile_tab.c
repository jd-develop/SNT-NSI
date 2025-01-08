#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "pile.h"

#define TAILLE_INITIALE 10

struct pile {
    int nb_elem;
    int taille_max;
    int* tab;
};


pile_t* pile_vide() {
    pile_t* pile = malloc(sizeof(pile_t));
    pile->nb_elem = 0;
    pile->taille_max = TAILLE_INITIALE;
    pile->tab = malloc(TAILLE_INITIALE*sizeof(int));

    return pile;
}


bool est_vide(pile_t* p) {
    return p->nb_elem == 0;
}


void empiler(pile_t* p, int x) {
    if (p->nb_elem+1 > p->taille_max) {
        p->taille_max *= 2;
        p->tab = realloc(p->tab, p->taille_max * sizeof(int));
    }
    p->tab[p->nb_elem] = x;
    p->nb_elem++;
}


int depiler(pile_t* p) {
    assert(!est_vide(p));
    p->nb_elem--;
    return p->tab[p->nb_elem];
}


void free_pile(pile_t* p) {
    free(p->tab);
    free(p);
}


void print_pile(pile_t* p) {
    printf("###\n");
    for (int i = 0; i < p->nb_elem; i++) {
        printf("%d\n", p->tab[i]);
    }
    printf("===\n");
}

void print_pile_char(pile_t* p) {
    for (int i = 0; i < p->nb_elem; i++) {
        printf("%c", p->tab[i]);
    }
    printf("\n");
}

int taille_pile(pile_t* p) {
    return p->nb_elem;
}
