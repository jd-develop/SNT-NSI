#include "laby.h"

int main() {
    srand(time(NULL));
    printf("Implémenter des tests dans le fichier tests_laby.c afin de tester "
           "les fonctions de l'exercice 2.\n\n\n");

    laby_t laby1;
    laby_t laby2;
    laby_t laby3;

    int w = 10;
    int h = 10;

    laby1.width = w;
    laby1.height = h;
    laby1.cells = malloc(h * w * sizeof(char));
    laby2.width = w;
    laby2.height = h;
    laby2.cells = malloc(h * w * sizeof(char));
    laby3.width = w;
    laby3.height = h;
    laby3.cells = malloc(h * w * sizeof(char));

    for (int k = 0; k < w * h; k++) {
        laby1.cells[k] = 3;
        laby2.cells[k] = 3;
        laby3.cells[k] = 3;
    }

    printf("\n==== version récursive ====\n");
    printf("Labyrinthe plein\n");
    draw_laby(laby1);
    generate_laby(laby1);
    printf("Labyrinthe généré\n");
    draw_laby(laby1);
    bool* solution1 = solve_labyrinthe(laby1);
    printf("Labyrinthe résolu\n");
    draw_laby_with_visited(laby1, solution1);

    printf("\n==== version impérative ====\n");
    printf("Labyrinthe plein\n");
    draw_laby(laby2);
    generate_laby_q2(laby2);
    printf("Labyrinthe généré\n");
    draw_laby(laby2);
    bool* solution2 = solve_labyrinthe(laby2);
    printf("Labyrinthe résolu\n");
    draw_laby_with_visited(laby2, solution2);

    printf("\n==== version avec union-find ====\n");
    printf("Labyrinthe plein\n");
    draw_laby(laby3);
    generate_laby_q5(laby3);
    printf("Labyrinthe généré\n");
    draw_laby(laby3);
    bool* solution3 = solve_labyrinthe(laby3);
    printf("Labyrinthe résolu\n");
    draw_laby_with_visited(laby3, solution3);

    free(laby1.cells);
    free(laby2.cells);
    free(laby3.cells);
    free(solution1);
    free(solution2);
    free(solution3);
}
