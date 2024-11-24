#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "menu.h"

// ÉLÉMENTS DE MENUS
void affiche_elem(menu_elem_t* e) {
    assert(e != NULL);
    printf("%s ", e->nom);
    if (e->vegan) {
        printf("(V) ");
    }
    printf(": %.2f€\n", e->prix_unite);
}

void lire_element(FILE* fp, menu_elem_t* e) {
    assert(fp != NULL);
    float prix;
    int vegan;
    char nom[50];

    int lus = fscanf(fp, "%f %d ", &prix, &vegan);
    if (lus == EOF) {
        strcpy(e->nom, "Erreur");
        e->prix_unite = -1;
        return;
    }

    assert(fgets(nom, sizeof(nom), fp) != NULL);
    nom[strlen(nom) - 1] = '\0';  // sinon le retour ligne est pris en compte

    strcpy(e->nom, nom);
    e->vegan = (bool)vegan;
    e->prix_unite = prix;
}

// MENUS

void affiche_menu(menu_t* m) {
    assert(m != NULL);
    printf("Menu :\n");
    for (int i = 0; i < m->nb_elems; i++) {
        printf("%d. ", i+1);
        affiche_elem(&(m->elements[i]));
    }
}

void ajouter_element(menu_t* m, char* nom, float prix_unite, bool vegan) {
    assert(m != NULL);
    assert(m->nb_elems < MAX_ELEMS);

    menu_elem_t res;
    strcpy(res.nom, nom);
    res.prix_unite = prix_unite;
    res.vegan = vegan;

    m->elements[m->nb_elems] = res;
    m->nb_elems++;
}

void lire_menu(char* nom_fichier, menu_t* m) {
    assert(m != NULL);
    FILE* fp = fopen(nom_fichier, "r");
    assert(fp != NULL);

    m->nb_elems = 0;
    menu_elem_t element;
    for (int i = 0; i < MAX_ELEMS; i++) {
        lire_element(fp, &element);
        if (strcmp(element.nom, "Erreur") == 0 && element.prix_unite == -1) {
            break;
        }
        m->nb_elems++;
        m->elements[i] = element;
    }

    fclose(fp);
}

// COMMANDES

void init_commande(int* commande, int nb_elements) {
    for (int i = 0; i < nb_elements; i++) {
        commande[i] = 0;
    }
}

void prendre_commande(int* commande, int nb_elems) {
    printf("Choisissez les plats à commander en notant leurs numéros,\n");
    printf("puis '#' pour marquer la fin :\n");
    int c;
    int nb_lus = scanf("%d", &c);
    while (nb_lus != EOF && nb_lus != 0) {
        if (0 >= c || c > nb_elems)
            printf("Le plat numéro %d n’existe pas !\n", c);
        else
            commande[c-1] ++;
        nb_lus = scanf("%d", &c);
    }
}

void resume_commande(int* commande, menu_t* m) {
    assert(m != NULL);
    printf("Vous avez commandé :\n");
    for (int i = 0; i < m->nb_elems; i++) {
        if (commande[i] != 0) {
            printf("%d× %s\n", commande[i], m->elements[i].nom);
        }
    }
}

float total_commande(int* commande, menu_t* m) {
    assert(m != NULL);
    float prix = 0;
    for (int i = 0; i < m->nb_elems; i++) {
        prix += commande[i] * m->elements[i].prix_unite;
    }
    return prix;
}
