/* Recherche triée
 *
 * Entrée: un tableau T trié, x un entier
 * Sortie: Booléen indiquant si x est dans T
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

/* Génération et affichage */

// Renvoie un tableau aléatoire trié de n entiers
// entre 0 et 100
int* random_tab(int n) {
    int* res = malloc(n*sizeof(int));
    int x = rand()%10;
    for (int i = 0; i < n; ++i) {
        res[i] = x;
        x += rand()%10;
    }
    return res;
}

// Affiche le tableau t de n>0 cases
void print_tab(int* t, int n) {
    assert(n>0);
    printf("[%d", t[0]);
    for (int i = 1; i < n; ++i) {
        printf(", %d", t[i]);
    }
    printf("]\n");
}

/* SOLUTION */

// Détermine si x est dans le tableau t de n éléments
bool search_lin(int* t, int n, int x) {
    int i = 0;
    while (i < n) {
        if (t[i] == x) {
            return true;
        }
        i++;
    }
    return false;
}

// renvoie ∀i∈⟦0, A-1⟧∪⟦B+1, n-1⟧, T[i] ≠ x
bool invariant(int* T, int n, int x, int A, int B) {
    for (int i = 0; i < A; i++) {
        if (T[i] == x) {
            return false;
        }
    }
    for (int i = B+1; i < n; i++) {
        if (T[i] == x) {
            return false;
        }
    }
    return true;
}

// Détermine si x est dans le tableau t de n éléments
bool search(int* t, int n, int x) {
    int a = 0;
    int b = n-1;
    int m;
    while (b >= a) {
        m = (a+b)/2;
        if (t[m] == x) {
            return true;
        } else if (t[m] < x) {
            a = m+1;
        } else {
            b = m-1;
        }
        assert(invariant(t, n, x, a, b));
    }
    return false;
}

int main() {
    srand(time(NULL));
    int n = 15;
    int* t = random_tab(n);
    print_tab(t, n);
    printf("Entrez un élément à chercher: ");
    int x;
    scanf("%d", &x);
    if (search(t, n, x)) {
        printf("Oui\n");
    } else {
        printf("Non\n");
    }

    free(t);
    return 0;
}
