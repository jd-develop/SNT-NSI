#include <stdio.h>

int main() {
    float x, y, z;

    printf("Entrez trois nombres : ");
    scanf("%f %f %f", &x, &y, &z);

    if (x <= y && x <= z) {
        printf("%f ⩽ ", x);
        if (y <= z) {
            printf("%f ⩽ %f\n", y, z);
        } else {
            printf("%f ⩽ %f\n", z, y);
        }
    } else if (y <= x && y <= z) {
        printf("%f ⩽ ", y);
        if (x <= z) {
            printf("%f ⩽ %f\n", x, z);
        } else {
            printf("%f ⩽ %f\n", z, x);
        }
    } else {
        printf("%f ⩽ ", z);
        if (x <= y) {
            printf("%f ⩽ %f\n", x, y);
        } else {
            printf("%f ⩽ %f\n", y, x);
        }
    }

    return 0;
}

