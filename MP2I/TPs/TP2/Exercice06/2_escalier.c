#include <stdio.h>
#include <assert.h>

/* Génère la k-ième ligne de l’escalier (en partant de 0, donc k positif ou
 * nul)
 */
void ligne(int k) {
    assert(k >= 0);
    for (int i = 0; i < 2*k+1; i++) {
        printf("-");
    }
    printf("|\n");
}

/* Affiche un escalier de n lignes, où n est un entier positif ou nul. */
void escalier(int n) {
    assert(n >= 0);
    for (int i = 0; i < n; i++) {
        ligne(i);
    }
}

int main() {
    int n;
    printf("Entrez un entier positif ou nul : ");
    scanf("%d", &n);
    escalier(n);
    return 0;
}

