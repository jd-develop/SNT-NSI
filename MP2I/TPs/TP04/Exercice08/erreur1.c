#include <stdlib.h>

int main(){
    int* t = malloc(4*sizeof(int));
    t[0] = 5;
    t[1] = 6;
    t[2] = 7;
    t[3] = 8;
    free(t);
}
