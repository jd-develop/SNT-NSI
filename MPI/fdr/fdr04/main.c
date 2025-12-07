#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

/* Renvoie un tableau de n booléens rempli de false, avec n non nul */
bool* falses(int n) {
    bool* res = malloc(n*sizeof(bool));
    int i = 0;
    while (i < n) {
        res[i] = false;
        i++;
    }
    return res;
}


void test_falses() {
    bool* tab = falses(5);
    for (int i = 0; i < 5; i++) {
        assert(!(tab[i]));
    }
    free(tab);
}

/* Renvoie un tableau des n premiers entiers naturels non nuls, avec n non nul
 */
int* range(int n) {
    int* res = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        res[i] = i+1;
    }
    return res;
}

void test_range() {
    int* tab = range(3);
    assert(tab[0] == 1);
    assert(tab[1] == 2);
    assert(tab[2] == 3);
    free(tab);
}

void question_3() {
    int nombres[8] = {1, 2, 4, 8, 12, 56, -3, 19};
    for (int i = 0; i < 8; i++) {
        printf("%d\n", nombres[i]);
    }
}

/* Renvoie un tableau de n entiers relatifs compris entre a inclus et b exclus,
 * avec a < b */
int* randrange_n(int n, int a, int b) {
    assert(a < b);
    int* res = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        res[i] = rand()%(b-a) + a;
    }
    return res;
}

void test_randrange_n() {
    int* tab = randrange_n(10, -100, 100);
    for (int i = 0; i < 10; i++) {
        assert(tab[i] >= -100);
        assert(tab[i] < 100);
        // printf("%d ", tab[i]); // décommenter pour voir qu’en effet, ça
                                  // change d’une exécution à l’autre
    }
    // printf("\n");
    free(tab);
}


/* Renvoie true si t de taille n contient un 0, false sinon */
bool contient_0(int* t, int n) {
    bool res = false;
    int i = 0;
    while (!res && i < n) {
        if (t[i] == 0) {
            res = true;
        }
        i++;
    }
    return res;
}

void test_contient_0() {
    int* tab = range(5);
    assert(!contient_0(tab, 5));
    tab[3] = 0;
    assert(contient_0(tab, 5));
    assert(!contient_0(tab, 2));
    free(tab);
}

/* Renvoie l’indice du premier 0 dans t de taille n, ou -1 s’il n’y en a pas */
int premier_0(int* t, int n) {
    int res = -1;
    int i = 0;
    while (res == -1 && i < n) {
        if (t[i] == 0) {
            res = i;
        }
        i++;
    }
    return res;
}

void test_premier_0() {
    int tab[4] = {1, 4, 2, -3};
    assert(premier_0(tab, 4) == -1);
    tab[2] = 0;
    assert(premier_0(tab, 4) == 2);
    tab[1] = 0;
    assert(premier_0(tab, 4) == 1);
}


/* idem que premier_0 */
int premier_0_bis(int* t, int n) {
    int i = 0;
    while (i < n) {
        if (t[i] == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

void test_premier_0_bis() {
    int tab[4] = {1, 4, 2, -3};
    assert(premier_0_bis(tab, 4) == -1);
    tab[2] = 0;
    assert(premier_0_bis(tab, 4) == 2);
    tab[1] = 0;
    assert(premier_0_bis(tab, 4) == 1);
}

/* idem que premier_0 */
int premier_0_ter(int* t, int n) {
    int res = -1;
    for (int i = 0; res == -1 && i < n; i++) {
        if (t[i] == 0) {
            res = i;
        }
    }
    return res;
}

void test_premier_0_ter() {
    int tab[4] = {1, 4, 2, -3};
    assert(premier_0_ter(tab, 4) == -1);
    tab[2] = 0;
    assert(premier_0_ter(tab, 4) == 2);
    tab[1] = 0;
    assert(premier_0_ter(tab, 4) == 1);
}

/* Renvoie l’indice du dernier 0 dans t de taille n, et -1 si t ne contient
 * pas de 0. */
int dernier_0(int* t, int n) {
    int i = n-1;
    while (i >= 0) {
        if (t[i] == 0) {
            return i;
        }
        i--;
    }
    return -1;
}

void test_dernier_0() {
    int tab[4] = {1, 4, 2, -3};
    assert(dernier_0(tab, 4) == -1);
    tab[2] = 0;
    assert(dernier_0(tab, 4) == 2);
    tab[1] = 0;
    assert(dernier_0(tab, 4) == 2);
}


/* Renvoie la somme des éléments de t de taille n */
int somme(int* t, int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += t[i];
    }
    return res;
}

void test_somme() {
    int tab[4] = {1, 4, 2, -3};
    assert(somme(tab, 4) == 4);
    assert(somme(tab, 0) == 0);
}

/* Renovie l’indice de l’élément minimum de t de taille n>0 */
int min(int* t, int n) {
    int min_courant = t[0];
    int min_i = 0;
    for (int i = 1; i < n; i++) {
        if (t[i] < min_courant) {
            min_courant = t[i];
            min_i = i;
        }
    }
    return min_i;
}

void test_min() {
    int tab[4] = {1, 4, 2, -3};
    assert(min(tab, 4) == 3);
    assert(min(tab, 3) == 0);
}


/* Renvoie la conjonction des éléments de t de taille n */
bool all(bool* t, int n) {
    int i = 0;
    while (i < n) {
        if (!t[i]) {
            return false;
        }
        i++;
    }
    return true;
}


void test_all() {
    bool tab[4] = {true, true, true, true};
    assert(all(tab, 4));
    tab[2] = false;
    assert(!all(tab, 4));
    assert(all(tab, 2));
}


/* Renvoie l’élément de [[0, m-1]] ayant le plus d’occurences dans t de taille
 * n à valeurs dans [[0, m-1]], avec m>0. */
int max_occurences(int* t, int n, int m) {
    int* occurences = malloc(m*sizeof(int));
    for (int i = 0; i < m; i++) {
        occurences[i] = 0;
    }

    for (int j = 0; j < n; j++) {
        occurences[t[j]]++;
    }

    int max_i = 0;
    int max = occurences[0];
    for (int i = 1; i < m; i++) {
        if (occurences[i] > max) {
            max = occurences[i];
            max_i = i;
        }
    }

    free(occurences);
    return max_i;
}

void test_max_occurences() {
    int tab[10] = {9, 1, 2, 0, 6, 1, 9, 2, 9, 11};
    assert(max_occurences(tab, 10, 12) == 9);
    tab[3] = 1;
    tab[9] = 1;
    assert(max_occurences(tab, 10, 12) == 1);
}

int main() {
    srand(time(NULL));

    test_falses();
    test_range();
    question_3();
    test_randrange_n();
    test_contient_0();
    test_premier_0();
    test_premier_0_bis();
    test_premier_0_ter();
    test_dernier_0();
    test_somme();
    test_min();
    test_all();
    test_max_occurences();
    return 0;
}
