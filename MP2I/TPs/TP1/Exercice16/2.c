#include <stdio.h>

int main() {
    float x;

    printf("Entrez un flottant : ");
    scanf("%f", &x);

    if (x < -0.33) {
        printf("Cas A\n");
    } else if (-0.33 <= x && x <= 7.89) {
        printf("Cas B\n");
    } else {
        printf("Cas C\n");
    }

    return 0;
}

