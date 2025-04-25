#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"


char* join(char** l, int n, char* s, int j) {
    char* res = strdup("(");
    bool not = (0 <= j) && (j <= n);
    for (int i = 0; i < n; i++) {
        if (not && i != j) {
            res = realloc(res, strlen(res)+2);
            strcat(res, "~");
        }
        res = realloc(res, strlen(res)+strlen(l[i])+1);
        strcat(res, l[i]);

        if (i+1 != n) {
            res = realloc(res, strlen(res)+strlen(s)+1);
            strcat(res, s);
        }
    }
    res = realloc(res, strlen(res)+2);
    strcat(res, ")");
    return res;
}


char* au_moins_une(char** l, int n) {
    return join(l, n, " | ", -1);
}


char* toutes(char** l, int n, int j) {
    return join(l, n, " & ", j);
}


char* au_plus_une(char** l, int n) {
    char** l2 = malloc((n+1)*sizeof(char*));
    for (int i = 0; i <= n; i++) {
        l2[i] = toutes(l, n, i);
    }
    char* res = au_moins_une(l2, n+1);
    for (int i = 0; i <= n; i++) {
        free(l2[i]);
    }
    free(l2);
    return res;
}


char* exactement_une(char** l, int n) {
    char** l2 = malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++) {
        l2[i] = toutes(l, n, i);
    }
    char* res = au_moins_une(l2, n);
    for (int i = 0; i < n; i++) {
        free(l2[i]);
    }
    free(l2);
    return res;
}

void printfree(char* s) {
    printf("%s\n", s);
    free(s);
}

