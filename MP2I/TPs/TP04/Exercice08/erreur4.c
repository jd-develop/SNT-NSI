#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Renvoie un tableau de n entiers aléatoires entre 1 et 100 */
int* random_tab(int n){
    int* t = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i){
        t[i] = rand()%100 + 1;
    }
    return t;
}

int main(){
    int* t = random_tab(10);
    for (int i = 0; i < 10; ++i){
        printf("%d\n", t[i]);
    }
    free(t);
}
