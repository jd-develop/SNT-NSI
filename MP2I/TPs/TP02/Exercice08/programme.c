#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


// ces variables globales servent à tricher
int borne_inf = 0;
int borne_sup = 4999;

/* Vérifie si guess est plus grand, égal ou moins grand que target.
 * Renvoie true si guess est égal à target, false sinon
 */
bool verifier(int target, int guess) {
    if (guess == target) {
        printf("Gagné !\n");
        return true;
    }
    if (guess >= target) {
        printf("Trop haut\n");
        borne_sup = guess;
    } else {
        printf("Trop bas\n");
        borne_inf = guess;
    }
    return false;
}

int main() {
    srand(time(NULL));
    int target = rand() % 5000;
    int guess;
    while (1) {
        // décommenter cette ligne pour tricher :
        // printf("Prochain nombre à tester : %d.\n", borne_inf + (borne_sup-borne_inf)/2);
        printf("Entrer un nombre : ");
        scanf("%d", &guess);
        if (verifier(target, guess)) {
            break;
        }
    }
    return 0;
}

