#include <stdlib.h>


int main(){
    float* a = malloc(sizeof(float));
    *a = 5;
    free(a);
    a = malloc(2*sizeof(float));
    a[0] = 5;
    a[1] = 7;
    free(a);
}
