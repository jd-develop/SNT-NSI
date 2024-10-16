#include <stdio.h>

int main() {
    //int *p = NULL;
    int *p = (int *) 25;
    printf("La valeur pointée par le pointeur NULL est %d\n", *p);
    return 0;
}
