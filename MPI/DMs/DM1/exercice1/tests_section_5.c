#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "knn.h"
#include "jeu_quadrant.h"

int main (){
    srand(time(NULL));
    /* remplacer -1 par la valeur adéquate */
    nb_class_max = 4;

    vector v = create_zero_vector(2);
    assert(quadrant(v) == 0);
    v->content[0] = 100;
    v->content[1] = 200;
    assert(quadrant(v) == 2);
    v->content[0] = 200;
    v->content[1] = 127;
    assert(quadrant(v) == 1);
    v->content[1] = 128;
    assert(quadrant(v) == 3);

    delete_vector(v);

    /* fabrique_jea_donnees */
    int db_size = 2000;
    database db = fabrique_jeu_donnees(db_size);
    // print_database(db);

    assert(db->size == db_size);
    for (int i = 0; i < db_size; i++) {
        assert(db->data[i].vector->content[0] >= 0);
        assert(db->data[i].vector->content[0] <= 255);
        assert(db->data[i].vector->content[1] >= 0);
        assert(db->data[i].vector->content[1] <= 255);
    }

    /* classify */
    for (int i = 0; i < db_size; i++) {
        assert(classify(db, 1, db->data[i].vector) == db->data[i].class);
    }

    vector rand_v = create_zero_vector(2);
    int ok = 0;  /* compte le nombre de succès de classify */
    for (int i = 0; i < 1000; i++) {
        rand_v->content[0] = rand()%256;
        rand_v->content[1] = rand()%256;
        if (quadrant(rand_v) == classify(db, 3, rand_v))
            ok++;
    }
    double taux = (double)ok / 1000.0;
    printf("Taux de classification correcte : %f %\n", 100*taux);

    delete_vector(rand_v);
    delete_database(db);

    return 0;
}
