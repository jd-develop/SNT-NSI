#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "knn.h"

int nb_class_max;
// penser à lui donner une valeur dans les fonctions main selon l'application

/* Renvoie la liste des k vecteurs de db les plus proches de input.
 * Précondition : db->size ⩾ k (cela permet que la liste de retour soit de
 * taille exactement k) */
candidats pproche_list(database db, int k, vector input) {
    assert(db->size >= k);
    candidats res = NULL;
    int r = 0;
    for (int i = 0; i < db->size; i++) {
        r = insertion_list(&res, r, k, db, i, input);
    }
    return res;
}


/* Renvoie la classe la plus présente parmi les r éléménts de db indexés par
 * les éléments de lc (lc de taille r). On suppose qu’il y a nb_class_max
 * classes (0, 1, …, nb_class_max-1). On suppose également que nb_class_max>0 */
int classe_majoritaire(database db, candidats lc, int r) {
    /* Initialisation d’un tableau contenant pour chaque classe le nombre de
     * vecteurs de lc ayant cette classe */
    int classes[nb_class_max];
    for (int i = 0; i < nb_class_max; i++) {
        classes[i] = 0;
    }

    /* Parcours de lc */
    for (candidats courant = lc; courant != NULL; courant = courant->next) {
        classes[db->data[courant->indice].class] ++;
    }

    /* Calcul de la classe ayant le plus de vecteurs */
    int max = classes[0];
    int argmax = 0;
    for (int i = 1; i < nb_class_max; i++) {
        if (classes[i] > max) {
            max = classes[i];
            argmax = i;
        }
    }

    return argmax;
}


/* Renvoie la classe la + présente parmi les k plus proches voisins de input
 * parmi les vecteurs de db, avec db->size ⩾ k */
int classify(database db, int k, vector input) {
    // On calcule les k plus proches voisins
    candidats knn = pproche_list(db, k, input);
    // On calcule la classe majoritaire
    int res = classe_majoritaire(db, knn, k);
    // On n’oublie pas de libérer la mémoire
    delete_list(knn);

    return res;
}

