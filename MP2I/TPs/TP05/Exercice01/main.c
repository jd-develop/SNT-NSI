#include <stdio.h>
#include <assert.h>
#include "menu.h"

/* teste le programme */
void test() {
    /*menu_elem_t e_1 = {
        .nom = "Gloubi-boulga",
        .prix_unite = 19.99,
        .vegan = false,
    };
    menu_elem_t e_2 = {
        .nom = "Gloubi-boulga sans saucisse de Toulouse",
        .prix_unite = 15.99,
        .vegan = true,
    };
    menu_elem_t e_3 = {
        .nom = "Gloubi-boulga sans confiture de fraises",
        .prix_unite = 14.87,
        .vegan = false
    };
    menu_elem_t e_4 = {
        .nom = "Gloubi-boulga sans banane écrasée",
        .prix_unite = 16.32,
        .vegan = false
    };
    menu_elem_t e_5 = {
        .nom = "Gloubi-boulga sans chocolat",
        .prix_unite = 14.59,
        .vegan = false
    }; */
    /*printf("%f\n", e_1.prix_unite);*/
    /*
    affiche_elem(&e_1);
    affiche_elem(&e_2);
    */

    menu_t menu;
    menu.nb_elems = 0;
    ajouter_element(
        &menu,
        "Gloubi-boulga",
        19.99,
        false
    );
    ajouter_element(
        &menu,
        "Gloubi-boulga sans saucisse de Toulouse",
        15.99,
        true
    );
    ajouter_element(
        &menu,
        "Gloubi-boulga sans confiture de fraises",
        14.87,
        false
    );
    ajouter_element(
        &menu,
        "Gloubi-boulga sans banane écrasée",
        16.32,
        false
    );
    ajouter_element(
        &menu,
        "Gloubi-boulga sans chocolat",
        14.59,
        false
    );
    /* menu.nb_elems = 5,
    menu.elements[0] = e_1;
    menu.elements[1] = e_2;
    menu.elements[2] = e_3;
    menu.elements[3] = e_4;
    menu.elements[4] = e_5; */

    affiche_menu(&menu);

    int commande[5];
    init_commande(commande, 5);
    for (int i = 0; i < 5; i++) {
        assert(commande[i] == 0);
    }
    commande[0] = 1;
    commande[1] = 2;
    commande[4] = 4;
    float tot = total_commande(commande, &menu);
    float expected_tot = 19.99+15.99*2+14.59*4;
    assert(-0.01 <= tot-expected_tot && tot-expected_tot <= 0.01);

    /*init_commande(commande, 5);
    prendre_commande(commande, 5);*/
    resume_commande(commande, &menu);
    printf("Prix total : %.2f\n", total_commande(commande, &menu));

    menu_elem_t e_test;
    lire_element(stdin, &e_test);
    affiche_elem(&e_test);
} 

int main() {
    test();
}
