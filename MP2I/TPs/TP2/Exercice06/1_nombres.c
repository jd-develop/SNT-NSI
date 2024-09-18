#include <stdio.h>
#include <assert.h>

/* Affiche tous les nombres de 1 à n (entier positif non nul) */
void un_a_n(int n) {
    assert(n >= 1);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", i);
    }
}

int main() {
    int n;
    printf("Entrez un entier positif : ");
    scanf("%d", &n);
    un_a_n(n);
    return 0;
}

