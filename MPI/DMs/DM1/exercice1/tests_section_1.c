#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "database.h"

int main() {
    /* create_zero_vector */
    vector vecteur_nul_5 = create_zero_vector(5);
    for (int i = 0; i < 5; i++) {
        assert(vecteur_nul_5->content[i] == 0);
    }
    assert(vecteur_nul_5->taille = 5);

    vector vecteur_nul_0 = create_zero_vector(0);
    assert(vecteur_nul_0->taille == 0);
    /* On n’asserte rien sur vecteur_nul_0->content car c’est spécifique à
     * chaque implémentation de C (ça peut être NULL ou autre chose) : cf.
     * https://stackoverflow.com/questions/2022335/whats-the-point-of-malloc0
     * Une chose est sûre : le free marchera.
     */

    vector un_zero = create_zero_vector(2);
    un_zero->content[0] = 1;
    vector zero_un = create_zero_vector(2);
    zero_un->content[1] = 1;
    vector vecteur_nul_2 = create_zero_vector(2);

    /* print_vector */
    printf("print_vector devrait afficher (0, 0, 0, 0, 0) : ");
    print_vector_newline(vecteur_nul_5);
    printf("print_vector devrait afficher () : ");
    print_vector_newline(vecteur_nul_0);
    printf("print_vector devrait afficher (1, 0) : ");
    print_vector_newline(un_zero);
    printf("print_vector devrait afficher (0, 1) : ");
    print_vector_newline(zero_un);
    printf("print_vector devrait afficher (0, 0) : ");
    print_vector_newline(vecteur_nul_2);

    /* distance */
    assert(distance(un_zero, zero_un) == distance(zero_un, un_zero));
    assert(distance(un_zero, zero_un) == sqrt(2));
    assert(distance(un_zero, vecteur_nul_2) == 1);

    /* delete_vector */
    delete_vector(vecteur_nul_5);
    delete_vector(vecteur_nul_0);
    delete_vector(un_zero);
    delete_vector(zero_un);
    delete_vector(vecteur_nul_2);  // testés avec Valgrind

    /* create_empty_database */
    database db1 = create_empty_database(2);
    assert(db1->size == 2);
    db1->data[0].vector = create_zero_vector(3);
    db1->data[0].vector->content[0] = 0;
    db1->data[0].vector->content[1] = 1;
    db1->data[0].vector->content[2] = 2;
    db1->data[0].class = 1;
    db1->data[1].vector = create_zero_vector(3);
    db1->data[1].vector->content[0] = 2;
    db1->data[1].vector->content[1] = 5;
    db1->data[1].vector->content[2] = 4;
    db1->data[1].class = 0;

    /* print_database */
    print_database(db1);

    /* delete_database */
    delete_database(db1);

    printf("Les tests de la section 1 sont passés\n");

    return 0;
}
