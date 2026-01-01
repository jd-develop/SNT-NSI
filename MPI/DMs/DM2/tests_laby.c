#include "laby.h"

int main() {
    srand(time(NULL));
    printf("Implémenter des tests dans le fichier tests_laby.c afin de tester "
           "les fonctions de l'exercice 2.\n\n\n");

    laby_t laby;
    int w = 10;
    int h = 10;
    laby.width = w;
    laby.height = h;
    laby.cells = malloc(h*w*sizeof(char));
    for (int k = 0; k < w*h; k++) {
        laby.cells[k] = 3;
    }

    printf("Labyrinthe plein\n");
    draw_laby(laby);
    generate_laby(laby);
    printf("Labyrinthe généré\n");
    draw_laby(laby);
}
