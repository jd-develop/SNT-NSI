#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "vector.h"
#include "database.h"
#include "candidats.h"
#include "knn.h"


int main() {
    /* create_list */
    candidats lc = create_list(0, 4.0);
    lc->next = create_list(3, 3.141592);
    lc->next->next = create_list(5, 2.5);
    lc->next->next->next = create_list(2, 1.0);
    lc->next->next->next->next = create_list(6, 0.1);

    /* print_list */
    printf("Il devrait y avoir écrit [(0, 4.0), (3, 3.141592), (5, 2.5), (2, ");
    printf("1.0), (6, 0.1)] (avec des 0 en plus) :\n");
    print_list_newline(lc);

    /* delete_list */
    delete_list(lc);

    /* insertion_list */
    database example_db = create_empty_database(5);
    for (int i = 0; i < 5; i++) {
        example_db->data[i].vector = create_zero_vector(2);
    }
    /* j’ai ajouté des classes aux vecteurs. La classe majoritaire des 3 plus
     * proches voisins de input (vecteur (1, 1)) est 1 */
    example_db->data[0].vector->content[0] = 3;
    example_db->data[0].vector->content[1] = 0;
    example_db->data[0].class = 2;
    example_db->data[1].vector->content[0] = 3;
    example_db->data[1].vector->content[1] = 1;
    example_db->data[1].class = 0;
    example_db->data[2].vector->content[0] = 2;
    example_db->data[2].vector->content[1] = 4;
    example_db->data[2].class = 2;
    example_db->data[3].vector->content[0] = 0;
    example_db->data[3].vector->content[1] = 1;
    example_db->data[3].class = 1;
    example_db->data[4].vector->content[0] = 0;
    example_db->data[4].vector->content[1] = 2;
    example_db->data[4].class = 1;

    vector input = create_zero_vector(2);
    input->content[0] = 1;
    input->content[1] = 1;

    /* le code suivant devrait afficher le même tableau que la page 4 du sujet
     */
    candidats lc2 = NULL;
    int r = 0;
    for (int i = 0; i < 5; i++) {
        print_list_newline(lc2);
        r = insertion_list(&lc2, r, 3, example_db, i, input);
    }
    print_list_newline(lc2);

    /* « Tests » de la section 4 (déjà pour voir si ça compile et si Valgrind
     * est content) */
    /* pproche_list */
    candidats lc3 = pproche_list(example_db, 3, input);
    printf("Il faut que la ligne suivante affiche la même chose que la ligne ");
    printf("précédente :\n");
    print_list_newline(lc3);

    /* classe_majoritaire et classify */
    nb_class_max = 3;
    assert(classe_majoritaire(example_db, lc3, 3) == 1);

    assert(classify(example_db, 3, input) == 1);

    /* delete_* */
    delete_database(example_db);
    delete_vector(input);
    delete_list(lc2);
    delete_list(lc3);

    return 0;
}

