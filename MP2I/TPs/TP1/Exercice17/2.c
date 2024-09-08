#include <stdio.h>

int main() {
    int x;

    printf("Entrez un entier : ");
    scanf("%d", &x);

    if (x%15 == 0) {
        printf("gouba\n");
    } else if (x%3 == 0) {
        printf("gou\n");
    } else if (x%5 == 0) {
        printf("ba\n");
    } else {
        printf("%d\n", x);
    }
    return 0;
}

