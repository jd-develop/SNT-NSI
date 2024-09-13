#include <stdio.h>

/* Affiche le double de x */
void afficher_double(int x) {
    printf("%d\n", 2*x);
}

int ajoute_un(int x) {
    printf("%d\n", 1+x);
    /* Erreur du compilateur */
}

int main() {
    int x = 5;
    /*void y =*/
    afficher_double(x);
    int y = ajoute_un(4);
    printf("%d\n", y);
    return 0;
}

