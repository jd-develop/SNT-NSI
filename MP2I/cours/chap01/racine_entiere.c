#include <stdio.h>

/* renvoie la partie entière de la racine carrée de n */
int racine_entiere(int n) {
    int k = 0;
    while (k*k <= n) {
        k++;
    }
    return k-1;
}

int main() {
    int x = 0;
    printf("Entrez un entier pour avoir sa racine entière "
           "(-1 pour quitter)\n");
    while (x>=0) {
        if (scanf("%d", &x) <= 0)
            return 1;
        printf("%d\n", racine_entiere(x));
    }
    return 0;
}

