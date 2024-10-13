#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    // choix de la seed pour l’aléatoire
    srand(time(NULL));

    int x = rand() % 100;
    int y = rand() % 11 + 10;

    printf("x: %d, y: %d\n", x, y);

    return 0;
}

