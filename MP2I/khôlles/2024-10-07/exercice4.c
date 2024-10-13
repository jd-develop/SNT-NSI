#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
 * Renvoie vrai si n⩾2 est premier, faux sinon
 */
bool est_premier(int n) {
    assert(n >= 2);
    for (int i = 2; i < n; i++)
        if (n%i == 0)
            return false;
    return true;
}

/*
 * Renvoie le plus petit nombre premier strictement supérieur à n⩾2
 */
int plus_petit_premier(int n) {
    assert(n >= 2);
    int N = n+1;
    while (!est_premier(N))
        N++;
    return N;
}

/*
 * Affiche la décomposition de n⩾2 en facteurs premiers
 */
void decomposition(int n) {
    assert(n >= 2);
    int premier_a_tester = 2;
    int nombre_a_decomposer = n;
    int accu = 1;
    while (accu != n) {
        if (nombre_a_decomposer % premier_a_tester == 0) {
            accu *= premier_a_tester;
            nombre_a_decomposer /= premier_a_tester;
            printf("%d", premier_a_tester);
            if (accu != n) printf("*");
        } else {
            premier_a_tester = plus_petit_premier(premier_a_tester);
        }
    }
    printf("\n");
}

/*
 * Affiche la décomposition de n⩾2 en facteurs premiers, mais n’affiche
 * qu’une seule fois chaque nombre
 */
void decomposition_2(int n) {
    assert(n >= 2);
    int premier_a_tester = 2;
    int nombre_a_decomposer = n;
    int accu = 1;
    int k = 0; // nombre de fois qu’on a vu chaque premier
    while (accu != n) {
        if (nombre_a_decomposer % premier_a_tester == 0) {
            accu *= premier_a_tester;
            nombre_a_decomposer /= premier_a_tester;
            k++;
        }
        if (!(nombre_a_decomposer % premier_a_tester == 0)) {
            if (k != 0) {
                if (k == 1)
                    printf("%d", premier_a_tester);
                else
                    printf("%d^%d", premier_a_tester, k);
                if (accu != n) printf("*");
            }
            k = 0;
            premier_a_tester = plus_petit_premier(premier_a_tester);
        }
    }
    printf("\n");
}

/*
 * Affiche la décomposition en nombres premiers sans utiliser les fonctions
 * précédentes
 */
void decomposition_3(int n) {
    assert(n >= 2);

    int premier_a_tester = 2;
    int nombre_a_decomposer = n;
    int accu = 1;

    while (accu != n) {
        if (nombre_a_decomposer % premier_a_tester == 0) {
            accu *= premier_a_tester;
            nombre_a_decomposer /= premier_a_tester;
            printf("%d", premier_a_tester);
            if (accu != n) printf("*");
        } else {
            premier_a_tester++;
        }
    }

    printf("\n");
}

int main() {
    // tests est_premier
    assert(est_premier(2));
    assert(est_premier(3));
    assert(!est_premier(4));
    assert(est_premier(5));
    assert(!est_premier(6));
    assert(est_premier(7));
    assert(!est_premier(8));
    assert(!est_premier(9));
    assert(!est_premier(10));
    assert(est_premier(11));

    // tests plus_petit_premier
    assert(plus_petit_premier(2) == 3);
    assert(plus_petit_premier(3) == 5);
    assert(plus_petit_premier(17) == 19);
    assert(plus_petit_premier(19) == 23);

    // tests decomposition
    decomposition(2); // 2
    decomposition(8); // 2*2*2
    decomposition(10); // 2*5
    decomposition(210); // 2*3*5*7

    // tests decomposition_2
    printf("\n");
    decomposition_2(2); // 2
    decomposition_2(8); // 2^3
    decomposition_2(10); // 2*5
    decomposition_2(3780); // 2^2*3^3*5*7

    // tests decomposition_3
    printf("\n");
    decomposition_3(2); // 2
    decomposition_3(8); // 2*2*2
    decomposition_3(10); // 2*5
    decomposition_3(210); // 2*3*5*7
    decomposition_3(3780); // 2*2*3*3*3*5*7
    decomposition_3(17*19*23*97); // 17*19*23*97
}
