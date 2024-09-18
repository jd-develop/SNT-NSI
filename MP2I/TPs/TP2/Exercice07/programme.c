#include <stdio.h>

int main() {
    long nb = 0;
    unsigned long somme = 0;
    while (nb >= 0) {
        somme += nb;
        printf("Entrez un nombre : ");
        scanf("%ld", &nb);
    }
    printf("La somme des nombres positifs que vous avez entrés est %ld.\n", somme);

    return 0;
}

