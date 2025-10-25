#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "jeu_quadrant.h"
#include "database.h"

/* Renvoie le quadrant du vecteur v : 0 pour le coin inférieur gauche,
 * 1 pour le coin inférieur droit, 2 pour le coin supérieur gauche,
 * 3 pour le coin supérieur droit (avec « gauche/droite » = 1re coordonnée
 * et « inférieur/supérieur » = 2nde coordonnée)
 * v doit être un vecteur à 2 coordonnées ! */
int quadrant(vector v) {
    assert(v->taille == 2);
    if (v->content[0] <= 127) {
        if (v->content[1] <= 127)
            return 0;
        else
            return 2;
    } else {
        if (v->content[1] <= 127)
            return 1;
        else
            return 3;
    }
}

/* Fabrique une base de données classifiée de db_size vecteurs de
 * [0, 255]×[0, 255] aléatoires. Il faut initialiser la graine de génération de
 * nombres pseudo-aléatoires avant d’appeler cette fonction */
database fabrique_jeu_donnees(int db_size) {
    database res = malloc(sizeof(struct database_s));
    res->size = db_size;
    res->data = malloc(db_size*sizeof(struct classified_data_s));
    for (int i = 0; i < db_size; i++) {
        res->data[i].vector = create_zero_vector(2);
        res->data[i].vector->content[0] = rand()%256;
        res->data[i].vector->content[1] = rand()%256;
        res->data[i].class = quadrant(res->data[i].vector);
    }
    return res;
}

