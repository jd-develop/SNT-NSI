/**** Triangle de Rousseau ****
 *
 * Ce programme sert à afficher les triangles de Rousseau.
 * Le triangle d'ordre n aura n lignes. La i-ème ligne fait (i-1) unités
 * de large et pour j entre 1 et i-1, la ligne i contient un X à la j-ème
 * place si et seulement si i%(j+1)%3 ne vaut pas 1.
 * Par exemple pour n = 10:

X
  X
X   X
  X   X
X X X   X
    X X   X
X X X X X   X
  X     X X   X
X   X X   X X   X
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

// Renvoie un booléen indiquant si n est pair.
bool est_pair(int n){
    if (n%2 == 0)
        return true;
    else
        return false;
}


// affiche la i-ème ligne du triangle de Rousseau
void ligne(int i){
    assert(i >= 0);

    // afficher chaque caractère de la ligne.
    // j varie de 1 à i-1
    for (int j=1; j < i; ++j)
    {
        if ((i%(j+1))%3 != 1){
            printf("X ");
        } else {
            printf("  ");
        }
    }
    printf("\n");
}


int main(){
    srand(time(NULL));
    // nombre de lignes à afficher (n doit être positive)
    int n;
    assert(n >= 0);
    printf("Rentrez le nombre de lignes à afficher: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
    {
        ligne(i);
    }

    int a = rand()%2000;
    printf("Au fait, le saviez vous ?");
    printf(" %d ", a);
    if (est_pair(a)){
        printf("est pair !\n");
    } else {
        printf("n'est pas pair...\n");
    }
}
