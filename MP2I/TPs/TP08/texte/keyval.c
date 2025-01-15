#include "keyval.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned int hash(KEY k){
    int res = 0;
    int l = strlen(k);
    for (int i = 0; i < l; ++i){
        res = res + k[i];
    }
    return res;
}

bool equal(KEY k1, KEY k2){
    return strcmp(k1, k2) == 0;
}

void key_free(KEY k){
    free(k);
}

void val_free(VAL __attribute__ ((unused)) v) {  // je n’aime pas les warnings
}

void key_print(KEY k){
    printf("%s", k);
}

void val_print(VAL v){
    printf("%d", v);
}
