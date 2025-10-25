#include <stdlib.h>
#include <stdio.h>

#include "database.h"
#include "vector.h"

/* Créée une base de donnée de taille n, initialement vide (i.e. contient
 * n données classifiés par 0, dont les vecteurs sont pour l’instant des
 * pointeurs NULL) */
database create_empty_database(int n) {
    database res = malloc(sizeof(struct database_s));
    res->size = n;

    res->data = malloc(n*sizeof(struct classified_data_s));
    for (int i = 0; i < n; i++) {
        res->data[i].vector = NULL;
        res->data[i].class  = 0;
    }

    return res;
}


/* Libère la mémoire allouée à la base de données db */
void delete_database(database db) {
    for (int i = 0; i < db->size; i++) {
        delete_vector(db->data[i].vector);
    }
    free(db->data);
    free(db);
}


/* Affiche une base de données comme précisé dans le sujet ('{' sur une ligne,
 * puis sur les db->size lignes suivantes '(..., ...) ~> class' pour chaque
 * vecteur de la base, puis '}' sur une ligne, puis un retour-ligne). */
void print_database(database db) {
    printf("{\n");
    for (int i = 0; i < db->size; i++) {
        printf("  ");
        if (db->data[i].vector == NULL)
            printf("NULL");
        else
            print_vector(db->data[i].vector);
        printf(" ~> %d\n", db->data[i].class);
    }
    printf("}\n");
}

