#include <stdio.h>


int main() {
    int x = 6;
    int* px = &x;
    int y = *px;

    printf("y vaut %d\n", y);

    x = 12;
    printf("y vaut %d\n", y);

    return 0;
}
