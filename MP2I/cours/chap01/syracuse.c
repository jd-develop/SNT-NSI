#include <stdio.h>

/* Renvoie le n-ième terme de la suite de Syracuse */
unsigned long long int syracuse(unsigned long long int x, int n) {
    if (n == 0) {
        return x;
    }
    /*if (syracuse(x, n-1) % 2 == 0) {
        return syracuse(x, n-1) / 2;
    } else {
        return 3 * syracuse(x, n-1) + 1;
    }*/
    unsigned long long int precedent = syracuse(x, n-1);

    if (precedent%2 == 0) {
        return precedent/2;
    } else {
        return 3*precedent + 1;
    }
}

int main() {
    unsigned long long int a;
    for (int i = 0; ; i++) {
        unsigned long long int a = syracuse(i, 1000);
        if (a != 1 && a != 2 && a != 4)
            printf("%d: %d\n", i, a);
    }
}

