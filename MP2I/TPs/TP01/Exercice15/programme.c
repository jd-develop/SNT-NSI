#include <stdio.h>

int main() {
    int x;
    int y;

    printf("Entrez x : ");
    scanf("%d", &x);
    printf("Entrez y : ");
    scanf("%d", &y);

    if (x<y) {
        printf("oui\n");
    } else {
        printf("non\n");
    }

    return 0;
}

