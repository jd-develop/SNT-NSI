#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "file.h"


typedef struct maillon {
    int elem;
    struct maillon* suivant;
} maillon_t;


struct file {
    maillon_t* tete;
    maillon_t* queue;
};


file_t* file_vide() {
    file_t* f = malloc(sizeof(file_t));
    f->tete = NULL;
    f->queue = NULL;
    return f;
}


bool est_file_vide(file_t* f) {
    return (f->tete == NULL);
}


void enfiler(file_t* f, int x) {
    maillon_t* nouveau_maillon = malloc(sizeof(maillon_t));
    nouveau_maillon->elem = x;
    nouveau_maillon->suivant = NULL;
    if (est_file_vide(f)) {
        f->tete = nouveau_maillon;
    } else {
        f->queue->suivant = nouveau_maillon;
    }
    f->queue = nouveau_maillon;
}


int defiler(file_t* f) {
    assert(!est_file_vide(f));
    int val = f->tete->elem;

    if (f->tete->suivant == NULL) {
        free(f->tete);
        f->tete = NULL;
        f->queue = NULL;
        return val;
    }

    maillon_t* nouv_tete = f->tete->suivant;
    free(f->tete);
    f->tete = nouv_tete;
    return val;
}


void free_file(file_t* f) {
    maillon_t* m = f->tete;
    maillon_t* suiv;
    while (m != NULL) {
        suiv = m->suivant;
        free(m);
        m = suiv;
    }
    free(f);
}

void affiche_file(file_t* f) {
    bool print_arrow = false;
    for (maillon_t* m = f->tete; m != NULL; m = m->suivant) {
        if (print_arrow)
            printf(" <- ");
        print_arrow = true;
        printf("%d", m->elem);
    }
    printf("\n");
}

