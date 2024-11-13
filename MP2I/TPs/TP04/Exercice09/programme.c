#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Lit autant d’entiers que la valeur pointée par n dans le fichier filename, et
 * les renvoie dans un tableau.
 * Si moins d’entiers ont été lus, met à jour la valeur pointée par n pour y
 * stocker le nombre d’entiers lus.
 * Précondition : `filename` doit être le nom d’un fichier existant.
 */
int* lire_entiers(char* filename, int* n) {
    assert(n != NULL);
    int* t = malloc(*n * sizeof(int));

    FILE* fp = fopen(filename, "r");
    assert(fp != NULL);

    int x;
    int nb_lus_tot = 0;
    int nb_lus = fscanf(fp, "%d", &x);
    while (nb_lus != EOF && nb_lus_tot < *n) {
        t[nb_lus_tot] = x;
        nb_lus_tot++;
        nb_lus = fscanf(fp, "%d", &x);
    }
    fclose(fp);

    *n = nb_lus_tot;

    return t;
}

/* teste la fonction lire_entiers en lisant n_a_lire entiers dans le fichier
 * filename ; confronte le tableau résultat avec le tableau stocké dans
 * tab_attendu et confronte n avec n_attendu
 */
void teste_lire_entiers(char* filename, int n_a_lire, int n_attendu,
                        int* tab_attendu) {
    int n = n_a_lire;
    int* tab = lire_entiers(filename, &n);
    assert(n == n_attendu);
    for (int i = 0; i < n; i++) {
        assert(tab_attendu[i] == tab[i]);
    }
    free(tab);
}

int main() {
    int TAB_M1[10] = {1, 2, 3, 4, 5, 6, 7, 8, -9, 10};
    int TAB_0[1] = {0};
    int TAB_1[10] = {-5, 6, -98, 0, 56, -97465, 0, 36, 984, -95191951};
    int TAB_2[10] = {89, -456, 32, -56, -45, 0, 0, 654, 951, -9881};
    int TAB_3[7] = {654, -987, -987, 654, 123, 0, 98};
    int TAB_4[9] = {-9881, -987, -621, -23, 651, 3, 984, 148, 0};

    teste_lire_entiers("../Exercice05/-1", 10, 10, TAB_M1);
    teste_lire_entiers("../Exercice05/0", 10, 1, TAB_0);
    teste_lire_entiers("../Exercice05/1", 10, 10, TAB_1);
    teste_lire_entiers("../Exercice05/2", 10, 10, TAB_2);
    teste_lire_entiers("../Exercice05/3", 10, 7, TAB_3);
    teste_lire_entiers("../Exercice05/4", 10, 9, TAB_4);
}
