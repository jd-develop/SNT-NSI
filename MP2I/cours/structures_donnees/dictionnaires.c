#include <stdio.h>
#include <stdlib.h>

#define K int
#define V int

typedef struct maillon {
    K key;
    V value;
    struct maillon* suiv;
    struct maillon* prec;
} maillon_t;

typedef struct dict {
    maillon_t* tete;
} dict_t;

typedef struct dict liste_t;

// renvoie le maillon contenant k dans l, NULL, s’il n’y en a pas
maillon_t* cherche_maillon(liste_t* l, K k) {
    maillon_t* m = l->tete;
    while (m != NULL) {
        if (m->key == k)
            return m;
        m = m->suiv;
    }
    return NULL;
}

void ajouter(liste_t* l, K k, V v) {
    maillon_t* m = cherche_maillon(l, k);
    if (m != NULL) {
        m -> value = v;
    } else {
        m = malloc(sizeof(maillon_t));
        m->key = k;
        m->value = v;
        m->prec = NULL;
        m->suiv = l->tete;
        l->tete = m;
    }
}

// en exercice : recherche et suppression


int main() {
    return 0;
}
