#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

liste_t* liste_aleatoire(int n){
    assert(n >= 0);
    liste_t* res = malloc(sizeof(liste_t));
    res->taille = n;
    // si n = 0, on renvoie une liste vide
    if (n == 0){
        res->tete = NULL;
        return res;
    }
    // sinon, on crée un premier maillon (la tête),
    // et on ajoute les n-1 maillons suivants à la suite
    res->tete = malloc(sizeof(maillon_t));

    // courant représente le dernier maillon ajouté
    maillon_t* courant = res->tete;
    courant->val = rand()%100;
    for (int i = 1; i < n; ++i){
        // créer un nouveau maillon et s'y positionner,
        // puis rentrer la valeur
        courant->suivant = malloc(sizeof(maillon_t));
        courant = courant->suivant;
        courant->val = rand()%100;
    }
    // marquer la fin de la liste avec NULL
    courant->suivant = NULL;
    return res;
}

liste_t* liste_range(int n) {
    assert(n > 0);
    liste_t* res = malloc(sizeof(liste_t));
    res->taille = n;
    // si n == 0, on renvoie une liste vide
    if (n == 0) {
        res->tete = NULL;
        return res;
    }

    res->tete = malloc(sizeof(maillon_t));
    maillon_t* courant = res->tete;
    for (int i = 0; i < n-1; i++) {
        courant->val = i;
        courant->suivant = malloc(sizeof(maillon_t));
        courant = courant->suivant;
    }
    courant->val = n-1;
    courant->suivant = NULL;

    return res;
}

void liste_print(liste_t* l){
    assert(l != NULL);
    // parcourir la liste depuis la tête, en s'arrêtant
    // lorsque l'on atteint le NULL marquant la fin de liste
    maillon_t* m = l->tete;
    while (m != NULL){
        printf("%d ", m->val);
        m = m->suivant;
    }
    printf("\n");
}

void free_maillon(maillon_t* m) {
    // on fait ça récursivement
    if (m == NULL)
        return;
    free_maillon(m->suivant);
    free(m);
}

void free_liste(liste_t* l) {
    assert(l != NULL);
    // on fait ça récursivement
    free_maillon(l->tete);
    free(l);
}

bool maillon_recherche(int x, maillon_t* m) {
    if (m == NULL)
        return false;
    else if (m->val == x)
        return true;
    else
        return maillon_recherche(x, m->suivant);
}

bool liste_recherche(int x, liste_t* L) {
    assert(L != NULL);
    return maillon_recherche(x, L->tete);
}

void ajoute_element_fin_maillon(int val, maillon_t* m) {
    if (m->suivant == NULL) {
        maillon_t* nouveau_maillon = malloc(sizeof(maillon_t));
        nouveau_maillon->suivant = NULL;
        nouveau_maillon->val = val;
        m->suivant = nouveau_maillon;
        return;
    }
    ajoute_element_fin_maillon(val, m->suivant);
}

void ajoute_element_fin(int val, liste_t* L) {
    assert(L != NULL);
    if (L->tete == NULL) {
        maillon_t* nouveau_maillon = malloc(sizeof(maillon_t));
        nouveau_maillon->suivant = NULL;
        nouveau_maillon->val = val;
        L->tete = nouveau_maillon;
        return;
    }
    ajoute_element_fin_maillon(val, L->tete);
    L->taille++;
}

void ajoute_element_debut(int val, liste_t* L) {
    assert(L != NULL);

    maillon_t* nouveau_maillon = malloc(sizeof(maillon_t));
    nouveau_maillon->suivant = L->tete;
    nouveau_maillon->val = val;

    L->tete = nouveau_maillon;
    L->taille++;
}

void retire_premier(int val, liste_t* L) {
    assert(L != NULL);

    maillon_t* prec = NULL;
    maillon_t* m = L->tete;
    while (m != NULL) {
        if (m->val == val) {
            if (prec == NULL) {
                L->tete = m->suivant;
            } else {
                prec->suivant = m->suivant;
            }
            free(m);
            L->taille--;
            return;
        } else {
            prec = m;
            m = m->suivant;
        }
    }
}

