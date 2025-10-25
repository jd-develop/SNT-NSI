#ifndef DATABASE_H
#define DATABASE_H

#include "vector.h"

struct classified_data_s {
    vector vector;                   /* le vecteur */
    int    class;                   /* sa classe */
};

struct database_s {
    int size;                        /* taille du jeu de données */
    struct classified_data_s* data;  /* tableau contenant les données
                                      * classifiées */
};

typedef struct database_s * database;

database create_empty_database(int n);
void delete_database(database db);
void print_database(database db);

#endif
