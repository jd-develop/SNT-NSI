#include <stdio.h>

/* Renvoie la factorielle de n supérieur ou égal à 0.
 * Renvoie 0 si n est stricement inférieur à 0
 */
unsigned long factorielle(int n) {
    if (n < 0)
        return 0;

    unsigned long i = 1;
    unsigned long r = 1;
    while (i <= (long unsigned int)n) {
        r *= i;
        i++;
    }
    return r;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%ld\n", factorielle(n));
    return 0;
}
