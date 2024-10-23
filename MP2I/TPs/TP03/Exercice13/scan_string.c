#include <stdio.h>

/*
 * Répète ce que l'utilisateur écrit tant que le programme n'est pas interrompu
 */
int main() {
    char buf[20]; // sert à stocker la chaîne lue

    while (1) {
        scanf("%s", buf);
        printf("Vous avez écrit: %s\n", buf);
    }
    return 0;
}
