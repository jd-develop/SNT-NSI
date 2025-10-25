#include <stdlib.h>
#include <stdio.h>
#include <math.h>  // Attention à compiler avec l'option -lm
#include <assert.h>

#include "vector.h"

/* Crée et renvoie le vecteur nul de R^n, i.e. un vecteur de taille n comprenant
 * uniquement des 0. Le vecteur créé devra être libéré avec delete_vector. */
vector create_zero_vector(int n) {
    vector res = malloc(sizeof(struct vector_s));
    res->taille = n;
    res->content = malloc(n*sizeof(unsigned char));

    for (int i = 0; i < n; i++) {
        res->content[i] = 0;
    }

    return res;
}


/* Libère la mémoire allouée pour le vecteur v */
void delete_vector(vector v) {
    if (v != NULL) {
        free(v->content);
        free(v);
    }
}


/* Affiche les coordonnées du vecteur v. Par exemple, si v = {x, y, z} (n=3),
 * affiche (x, y, z). Si v = {} (n=0), affiche ()
 * N’affiche pas de retour-ligne à la fin. */
void print_vector(vector v) {
    printf("(");
    for (int i = 0; i < v->taille; i++) {
        if (i+1 == v->taille)
            printf("%d", v->content[i]);
        else
            printf("%d, ", v->content[i]);
    }
    printf(")");
}


/* Même chose que print_vector, mais avec un retour-ligne à la fin */
void print_vector_newline(vector v) {
    print_vector(v);
    printf("\n");
}


/* Renvoie la distance euclidienne entre v1 et v2 deux vecteurs de même taille
 */
double distance(vector v1, vector v2) {
    assert(v1->taille == v2->taille);
    int n = v1->taille;

    int somme_carres = 0;
    int coordonnee;
    for (int i = 0; i < n; i++) {
        coordonnee = v2->content[i] - v1->content[i];
        somme_carres += coordonnee*coordonnee;
    }

    return sqrt(somme_carres);
}

