#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "liste.h"

int main() {
    srand(time(NULL));
    liste_t* aleat = liste_aleatoire(10);
    liste_print(aleat);

    liste_t* range = liste_range(10);
    liste_print(range);
    assert(range->taille == 10);

    assert(liste_recherche(0, range));
    assert(liste_recherche(1, range));
    assert(liste_recherche(9, range));
    assert(!liste_recherche(10, range));

    ajoute_element_fin(56, range);
    liste_print(range);

    assert(liste_recherche(9, range));
    assert(liste_recherche(56, range));
    assert(!liste_recherche(42, range));
    assert(range->taille == 11);

    ajoute_element_debut(128, range);
    liste_print(range);

    assert(liste_recherche(9, range));
    assert(liste_recherche(56, range));
    assert(liste_recherche(128, range));
    assert(!liste_recherche(42, range));
    assert(range->taille == 12);

    retire_premier(9, range);
    liste_print(range);

    assert(!liste_recherche(9, range));
    assert(liste_recherche(56, range));
    assert(liste_recherche(128, range));
    assert(!liste_recherche(42, range));
    assert(range->taille == 11);

    retire_premier(128, range);
    liste_print(range);

    assert(!liste_recherche(9, range));
    assert(liste_recherche(56, range));
    assert(!liste_recherche(128, range));
    assert(!liste_recherche(42, range));
    assert(range->taille == 10);

    retire_premier(56, range);
    liste_print(range);

    assert(liste_recherche(8, range));
    assert(!liste_recherche(9, range));
    assert(!liste_recherche(56, range));
    assert(!liste_recherche(128, range));
    assert(!liste_recherche(42, range));
    assert(range->taille == 9);

    free_liste(aleat);
    free_liste(range);
    return 0;
}
