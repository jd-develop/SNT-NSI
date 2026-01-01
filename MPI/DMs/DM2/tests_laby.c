#include "laby.h"

int main() {
    srand(time(NULL));
    printf("Implémenter des tests dans le fichier tests_laby.c afin de tester "
           "les fonctions de l'exercice 2.\n\n\n");

    laby_t laby;
    laby_t laby2;
    laby_t laby3;

    int w = 10;
    int h = 10;

    laby.width = w;
    laby.height = h;
    laby.cells = malloc(h * w * sizeof(char));
    laby2.width = w;
    laby2.height = h;
    laby2.cells = malloc(h * w * sizeof(char));
    laby3.width = w;
    laby3.height = h;
    laby3.cells = malloc(h * w * sizeof(char));

    for (int k = 0; k < w * h; k++) {
        laby.cells[k] = 3;
        laby2.cells[k] = 3;
        laby3.cells[k] = 3;
    }

    printf("\n==== version récursive ====\n");
    printf("Labyrinthe plein\n");
    draw_laby(laby);
    generate_laby(laby);
    printf("Labyrinthe généré\n");
    draw_laby(laby);

    printf("\n==== version impérative ====\n");
    printf("Labyrinthe plein\n");
    draw_laby(laby2);
    generate_laby_q2(laby2);
    printf("Labyrinthe généré\n");
    draw_laby(laby2);

    printf("\n==== version avec union-find ====\n");
    printf("Labyrinthe plein\n");
    draw_laby(laby3);
    generate_laby_q5(laby3);
    printf("Labyrinthe généré\n");
    draw_laby(laby3);

    free(laby.cells);
    free(laby2.cells);
    free(laby3.cells);
}
