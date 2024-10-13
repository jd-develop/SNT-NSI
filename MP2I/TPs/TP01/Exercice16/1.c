#include <stdio.h>

int main() {
    int x;

    printf("Entrez un entier : ");
    scanf("%d", &x);

    if (x==0) {
        printf("%d est égal à 0\n", x);
    } else {
        printf("%d est différent de 0\n", x);
    }
    return 0;
}

