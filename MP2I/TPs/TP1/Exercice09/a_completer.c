#include <stdio.h>

int main(){
    // créer une variable entière x, initialement nulle
    int x = 0;

    // créer une variable entière y, valant 5 initialement
    int y = 5;

    // modifier x en lui assignant x+y
    x += y;

    // modifier y en lui assignant y+x
    y += x;

    // répéter les deux dernières étapes une fois de plus
    x += y;
    y += x;

    // afficher x et y
    printf("x vaut %d, y vaut %d\n", x, y);
    return 0;
}
