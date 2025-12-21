#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* N’ayant pas trouvé le corrigé de la question 7, j’ai repris mon code de la
 * semaine dernière. */
struct liste {
    int valeur;
    struct liste* suivant;
};
typedef struct liste * liste_t;


/* Question 11 */
/* Renvoie une liste chaînée réduite à une cellule contenant `n` */
liste_t creer_liste(int n) {
    liste_t res = malloc(sizeof(struct liste));
    res->valeur = n;
    res->suivant = NULL;
    return res;
}

/* Question 12 */
/* Affiche la liste chaînée d’entiers l, sous la forme [v1, v2, ..., vn] */
void affiche_liste(liste_t l) {
    printf("[");
    for (liste_t courant = l; courant != NULL; courant = courant->suivant) {
        if (courant->suivant == NULL)
            printf("%d", courant->valeur);
        else
            printf("%d, ", courant->valeur);
    }
    printf("]\n");
}

/* Question 13 */
/* Renvoie la liste contenant les n premiers entiers naturels. Renvoie une liste
 * vide (i.e. NULL) si jamais n est négatif ou nul. */
liste_t range(int n) {
    if (n <= 0) {
        return NULL;
    }

    liste_t res = malloc(sizeof(struct liste));

    liste_t courant = res;
    courant->valeur = 0;
    for (int i = 1; i < n; i++) {
        courant->suivant = malloc(sizeof(struct liste));
        courant = courant->suivant;
        courant->valeur = i;
    }
    courant->suivant = NULL;

    return res;
}

/* Question 14 */
/* Libère l’espace mémoire alloué à la liste chaînée l */
void free_liste(liste_t l) {
    liste_t courant = l;
    liste_t temp;
    while (courant != NULL) {
        temp = courant->suivant;
        free(courant);
        courant = temp;
    }
}

/* Question 15 */
/* Créée une liste d’entiers à partir du tableau t, de taille n */
liste_t list_of_array(int* t, int n) {
    if (n <= 0) {
        return NULL;
    }

    liste_t res = malloc(sizeof(struct liste));

    liste_t courant = res;
    courant->valeur = t[0];
    for (int i = 1; i < n; i++) {
        courant->suivant = malloc(sizeof(struct liste));
        courant = courant->suivant;
        courant->valeur = t[i];
    }
    courant->suivant = NULL;

    return res;
}

/* Question 16 */
/* Renvoie la longueur de la liste l */
int longueur(liste_t l) {
    int res = 0;
    for (liste_t courant = l; courant != NULL; courant = courant->suivant) {
        res++;
    }
    return res;
}

/* Crée un tableau d’entiers à partir de la liste chaînée d’entiers l */
int* array_of_list(liste_t l) {
    int n = longueur(l);
    int* res = malloc(n*sizeof(int));
    int i = 0;
    for (liste_t courant = l; courant != NULL; courant = courant->suivant) {
        res[i++] = courant->valeur;
    }
    return res;
}

/* Question 17 */
/* Renvoie une liste contenant d’abord les éléments de l1 en ordre inverse
 * puis les éléments de l2 dans le bon ordre. Ne modifie ni l1 ni l2. */
liste_t renverse_concat(liste_t l1, liste_t l2) {
    liste_t res;
    /* On copie l2 */
    if (l2 == NULL) {
        res = NULL;
    } else {
        res = malloc(sizeof(struct liste));
        res->valeur = l2->valeur;
        liste_t courant_res = res;
        for (liste_t courant_l2 = l2->suivant; courant_l2 != NULL;
             courant_l2 = courant_l2->suivant)
        {
            courant_res->suivant = malloc(sizeof(struct liste));
            courant_res = courant_res->suivant;
            courant_res->valeur = courant_l2->valeur;
        }
        courant_res->suivant = NULL;
    }
    /* On copie l1 dans l’ordre inverse */
    liste_t temp;
    for (liste_t courant = l1; courant != NULL; courant = courant->suivant) {
        temp = malloc(sizeof(struct liste));
        temp->valeur = courant->valeur;
        temp->suivant = res;
        res = temp;
    }
    return res;
}

/* Question 18 */
/* Renvoie le miroir de l, sans dégrader l */
liste_t miroir(liste_t l) {
    liste_t res = NULL;
    liste_t temp;
    for (liste_t courant = l; courant != NULL; courant = courant->suivant) {
        temp = malloc(sizeof(struct liste));
        temp->valeur = courant->valeur;
        temp->suivant = res;
        res = temp;
    }
    return res;
}

/* Question 19 */
/* Renvoie une copie de l (i.e. réécrit l à un autre endroit dans le tas et
 * renvoie le pointeur) */
liste_t copy(liste_t l) {
    if (l == NULL) {
        return NULL;
    }

    liste_t res = malloc(sizeof(struct liste));
    res->valeur = l->valeur;
    liste_t courant_res = res;

    for (liste_t courant_l = l->suivant; courant_l != NULL;
         courant_l = courant_l->suivant)
    {
        courant_res->suivant = malloc(sizeof(struct liste));
        courant_res = courant_res->suivant;
        courant_res->valeur = courant_l->valeur;
    }
    courant_res->suivant = NULL;
    return res;
}

/* Question 20 */
/* Supprime les éléments de l au-delà des k premiers, avec k inférieur à la
 * taille de l. Plante si k est supérieur ou égal à la taille de l. */
void supprime_apres_k(liste_t l, int k) {
    liste_t courant = l;
    for (int i = 1; i < k; i++) {
        courant = courant->suivant;
    }
    free_liste(courant->suivant);
    courant->suivant = NULL;
}

/* Question 21 */
/* Supprime les éléments de l au-delà des k premiers, s’il y en a (si k est
 * plus grand que la longueur de l, ne fait rien) */
void supprime_apres_k_safe(liste_t l, int k) {
    liste_t courant = l;
    for (int i = 1; i < k && courant->suivant != NULL; i++) {
        courant = courant->suivant;
    }
    free_liste(courant->suivant);
    courant->suivant = NULL;
}

/* Question 22 */
/* Transforme la liste pointée par lp en son miroir, tel que le suivant de
 * l’ancien premier élément (i.e. le nouveau dernier élément) ait pour suivant
 * `prec`. Renvoie un pointeur vers le nouveau premier élément (i.e. l’ancien
 * dernier élément) */
liste_t miroir_aux(liste_t l, liste_t prec) {
    if (l != NULL) {
        liste_t temp = l->suivant;
        l->suivant = prec;
        return miroir_aux(temp, l);
    } else {
        return prec;
    }
}

/* Transforme la liste pointée par lp en son miroir, en place */
void miroir_en_place(liste_t* lp) {
    *lp = miroir_aux(*lp, NULL);
}

int main () {
    liste_t l = creer_liste(3);
    assert(l->valeur == 3);
    assert(l->suivant == NULL);

    affiche_liste(NULL);
    affiche_liste(l);

    liste_t range10 = range(10);
    affiche_liste(range10);

    assert(list_of_array(NULL, 0) == NULL);
    int tableau[10] = {7, 3, 0, 9, -5, 11, -78, 90, 12, 9};
    liste_t l2 = list_of_array(tableau, 10);
    affiche_liste(l2);

    assert(longueur(l2) == 10);
    assert(longueur(range10) == 10);
    assert(longueur(NULL) == 0);

    int* a = array_of_list(range10);
    for (int i = 0; i < 10; i++) {
        assert(a[i] == i);
    }

    liste_t l3 = renverse_concat(range10, l2);
    affiche_liste(l3);

    liste_t l4 = copy(range10);
    affiche_liste(l4);

    liste_t l5 = miroir(range10);
    affiche_liste(l5);
    affiche_liste(miroir(NULL));

    supprime_apres_k(range10, 5);
    affiche_liste(range10);

    supprime_apres_k_safe(range10, 8);
    affiche_liste(range10);
    supprime_apres_k_safe(l4, 8);
    affiche_liste(l4);

    miroir_en_place(&l4);
    affiche_liste(l4);

    free_liste(l);
    free_liste(range10);
    free_liste(l2);
    free_liste(l3);
    free_liste(l4);
    free_liste(l5);
    free(a);

    return 0;
}
