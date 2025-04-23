#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


char* au_moins_une(char** l, int n) {
    char* res = strdup("(");
    for (int i = 0; i < n; i++) {
        res = realloc(res, strlen(res)+strlen(l[i])+1);
        strcat(res, l[i]);

        if (i+1 != n) {
            res = realloc(res, strlen(res)+4);
            strcat(res, " | ");
        }
    }
    res = realloc(res, strlen(res)+2);
    strcat(res, ")");
    return res;
}


int main () {
    char* forms[3] = {"(x & ~y)", "y", "z"};
    char* phi = au_moins_une(forms, 3);
    printf("%s\n", phi);
    return 0;
}
