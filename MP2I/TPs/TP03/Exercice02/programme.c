#include <stdio.h>


int main() {
    int x = 6;
    int y = 98;
    int* px = &x;
    int* py = &y;

    printf("L'adresse de x est %p, celle de y est %p\n", px, py);

    return 0;
}
