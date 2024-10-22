#include <stdio.h>

/* Affiche le caractère correspondant à l’entier entré */
int main() {
    int c;
    printf("Entrez un nombre entre 0 et 127 : ");
    scanf("%d", &c);

    char code_8bits = c;  // transforme un int en char
    printf("Le caractère correspondant au code %d est '%c'\n", code_8bits, code_8bits);

    return 0;
}
