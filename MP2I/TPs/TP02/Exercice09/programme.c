#include <stdio.h>
#include <assert.h>

/* Affiche les n premiers entiers dans l’ordre décroissant, avec n ⩾ 0 */
void n_entiers_decroissants(int n) {
    assert(n >= 0);
    printf("%d\n", n);
    if (n == 0)
        return;
    n_entiers_decroissants(n-1);
}

/* Affiche les n premiers entiers dans l’ordre croissant, avec n ⩾ 0 */
void n_entiers_croissants(int n) {
    assert(n >= 0);
    if (n == 0) {
        printf("0\n");
        return;
    }
    n_entiers_croissants(n-1);
    printf("%d\n", n);
}

/* Affiche chaque chiffre de l’entier relatif n sur une ligne différente
 * (s’il y a un moins, il est affiché sur la première ligne)
 */
void nombre_multiligne(int n) {
    if (n < 0) {
        printf("-\n");
        nombre_multiligne(-n);
    } else if (0 <= n && n < 10) {
        printf("%d\n", n);
    } else {
        nombre_multiligne(n/10);
        printf("%d\n", n%10);
    }
}

/* Affiche n fois la lettre O sur la même ligne, avec n ⩾ 0 */
void n_fois_o(int n) {
    assert(n >= 0);
    if (n == 0)
        return;
    if (n == 1) {
        printf("O\n");
        return;
    }
    printf("O");
    n_fois_o(n-1);
}

/* Affiche, pour chaque chiffre de l’entier relatif n, autant de fois la lettre
 * 0 sur une ligne, puis revient à la ligne pour le chiffre suivant.
 * S’il y a un moins, il est affiché sur la première ligne.
 */
void nombre_multiligne_o(int n) {
    if (n < 0) {
        printf("-\n");
        nombre_multiligne_o(-n);
    } else if (0 <= n && n < 10) {
        n_fois_o(n);
    } else {
        nombre_multiligne_o(n/10);
        n_fois_o(n%10);
    }
}

int main() {
    // Tests question 1
    printf("Question 1 :\n");
    n_entiers_decroissants(0);
    n_entiers_decroissants(10);
    printf("\n");

    // Tests question 2
    printf("Question 2 :\n");
    n_entiers_croissants(0);
    n_entiers_croissants(10);
    printf("\n");

    // Tests question 3
    printf("Question 3 :\n");
    nombre_multiligne(5);
    printf("\n");
    nombre_multiligne(0);
    printf("\n");
    nombre_multiligne(-5);
    printf("\n");
    nombre_multiligne(8941);
    printf("\n");
    nombre_multiligne(-8941);
    printf("\n");

    // Tests question 4
    printf("Question 4 :\n");
    n_fois_o(1);
    n_fois_o(10);
    printf("\n");

    // Tests question 5
    printf("Question 5 :\n");

    nombre_multiligne_o(5);
    printf("\n");
    nombre_multiligne_o(0);
    printf("\n");
    nombre_multiligne_o(-5);
    printf("\n");
    nombre_multiligne_o(8941);
    printf("\n");
    nombre_multiligne_o(-8941);
    printf("\n");
    return 0;
}

