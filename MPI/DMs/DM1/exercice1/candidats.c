#include <stdlib.h>
#include <stdio.h>

#include "candidats.h"


/* Créée une liste contenant un seul élément : un candidat d’indice ind et de
 * distance dist */
candidats create_list(int ind, double dist) {
    candidats res = malloc(sizeof(struct s_cellule));
    res->indice = ind;
    res->distance = dist;
    res->next = NULL;
    return res;
}


/* Libère la mémoire allouée à la liste de candidats lc */
void delete_list(candidats lc) {
    candidats courant = lc;
    /* Il faut stokcer le suivant quelque part avant de libérer le courant */
    candidats suivant;

    while (courant != NULL) {
        suivant = courant->next;
        free(courant);
        courant = suivant;
    }
}


/* Affiche la liste de canditats l sous la forme [(idx, distance), (idx,
 * distance), ...], sans retour-ligne à la fin */
void print_list(candidats l) {
    candidats courant;

    printf("[");
    /* On affiche d’abord le premier sans virgule avant */
    if (l != NULL) {
        printf("(%d, %f)", l->indice, l->distance);
        courant = l->next;
    } else {
        courant = NULL;
    }

    /* On traite les suivants au premier à part pour rajouter une virgule */
    while (courant != NULL) {
        printf(", (%d, %f)", courant->indice, courant->distance);
        courant = courant->next;
    }
    printf("]");
}


/* Pareil que print_list mais avec un retour-ligne à la fin */
void print_list_newline(candidats l) {
    print_list(l);
    printf("\n");
}


/* Insère dans la liste pointée par pl de taille r et de taille maximum k
 * l’élément d’indice i dans la bade de donnée db, telle que pl reste de taille
 * maximum k et qu’elle soit triée par distance à input décroissante. Renvoie
 * la nouvelle taille de la liste */
int insertion_list(
    candidats* pl, int r, int k, database db, int i, vector input
) {
    float distance_a_input = distance(db->data[i].vector, input);
    /* Liste vide : on crée une liste contenant notre élément. */
    if (r == 0) {
        if (k == 0)
            return 0;
        *pl = create_list(i, distance_a_input);
        return 1;
    }
    /* Liste non vide */
    /* db−>data[i] doit figurer dans la liste si r < k ou si la distance entre
     * db->data[i] et input est strictement inférieure à la distance entre
     * db->data[(*pl)->indice] et input */
    if (r == k && distance_a_input >= (*pl)->distance) {
        return k;
    }
    /* Insertion : tant que notre distance est inférieure, on regarde le
     * suivant. */
    candidats prec = NULL;
    candidats courant = *pl;
    candidats tete = *pl;
    while (courant != NULL && distance_a_input < courant->distance) {
        prec = courant;
        courant = courant->next;
    }
    /* On doit alors s’insérer entre prec et courant. Soit prec = NULL, auquel
     * cas il faut s’insérer au début, soit courant = NULL, auquel cas il faut
     * s’insérer à la fin, soit les deux ne sont pas NULL, auquel cas il faut
     * s’insérer entre les deux. Les deux ne peuvent pas être NULL à la fois
     * car r ≠ 0 */
    if (prec == NULL) {
        *pl = create_list(i, distance_a_input);
        if (r == k) {
            /* le nombre d’éléments de la liste est déjà au max : on remplace
             * le premier de la liste */
            (*pl)->next = courant->next;
            free(courant);
        } else {
            /* Sinon, on peut garder le premier */
            (*pl)->next = courant;
        }
    } else if (courant == NULL) {
        prec->next = create_list(i, distance_a_input);
        if (r == k) { // liste pleine : il faut supprimer la tête
            *pl = (*pl)->next;
            free(tete);
        }
    } else {
        prec->next = create_list(i, distance_a_input);
        prec->next->next = courant;
        if (r == k) { // liste pleine : il faut supprimer la tête
            *pl = (*pl)->next;
            free(tete);
        }
    }

    if (r == k)
        return k;
    else
        return r+1;
}

