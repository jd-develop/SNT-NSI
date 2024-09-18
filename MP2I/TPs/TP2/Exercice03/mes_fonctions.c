#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
 * Renvoie true si a divise b, false sinon. Plante si a = 0
 */
bool divise(int a, int b) {
    assert(a!=0);
    return (b%a == 0);
}

/*
 * Si x est non nul, affiche x puis affiche 1/x
 * Plante si x est nul
 */
void affiche_inverse(float x) {
    assert(x != 0);
    printf("%f, %f\n", x, 1/x);
}

/*
 * Affiche 3x + 5y - 6.25z + t et renvoie son carré
 */
float f(int x, int y, int z, int t) {
    float resultat = 3*x + 5*y - 6.25*z + t;
    printf("%f", resultat);
    return resultat*resultat;
}

int main() {
    printf("Tests de la fonction divise.\n");
    printf("2 divise 4 : %d\n", divise(2, 4));
    printf("4 divise 2 : %d\n", divise(4, 2));
    // printf("0 divise -24 : %d\n", divise(0, -24)); // plante

    printf("\nTests de la fonction affiche_inverse.\n");
    printf("Nombres testés : 0.0, 10.0, 1/π, -2.0.\n");
    // affiche_inverse(0.0); // plante
    affiche_inverse(10.0);
    affiche_inverse(1/3.14159265358979323846264338327950288419);
    affiche_inverse(-2.0);

    printf("\nTests de la fonction f.\n");
    printf("x=1, y=1, z=1, t=1 : ");
    printf(", %f\n", f(1, 1, 1, 1));
    printf("x=-3, y=-4, z=0, t=29 : ");
    printf(", %f\n", f(-3, -4, 0, 29));

    return 0;
}

