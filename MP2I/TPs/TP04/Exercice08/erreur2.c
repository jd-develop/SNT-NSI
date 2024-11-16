#include <stdlib.h>

int main(){
    int** p = malloc(sizeof(int*));
    *p = malloc(sizeof(int));
    **p = 75;
    free(*p);
    free(p);
}
