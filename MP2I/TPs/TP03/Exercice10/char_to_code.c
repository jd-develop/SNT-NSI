#include <stdio.h>

/*
 * Affiche le code ASCII du caractère entré par l’utilisateur
 */
int main() {
    char c;
    printf("Entrez un caractère ASCII : ");
    scanf("%c", &c);

    printf("Le code de '%c' est %d\n", c, c);

    return 0;
}

