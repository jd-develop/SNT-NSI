#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

String* new_string(){
    String* dest = malloc(sizeof(String));
    dest->len_max = 16;
    dest->string = malloc(16*sizeof(char));
    dest->len = 0;
    dest->string[0] = '\0';
    return dest;
}

void string_append(String* dest, const char* src){
    int len_src = strlen(src);
    if (dest->len + len_src >= dest->len_max){
        while (dest->len + len_src >= dest->len_max){
            dest->len_max *= 2;
        }
        char* temp = realloc(dest->string, dest->len_max*sizeof(char));
        if (temp == NULL) {
            fprintf(stderr, "Erreur : impossible de réallouer la mémoire\n");
            exit(EXIT_FAILURE);
        }
        dest->string = temp;
    }
    dest->len += len_src;
    strcat(dest->string, src);
}

void string_cat(String* dest, String* src){
    if (dest->len + src->len >= dest->len_max){
        while (dest->len + src->len >= dest->len_max){
            dest->len_max *= 2;
        }
        char* temp = realloc(dest->string, dest->len_max*sizeof(char));
        if (temp == NULL) {
            fprintf(stderr, "Erreur : impossible de réallouer la mémoire\n");
            exit(EXIT_FAILURE);
        }
        dest->string = temp;
    }
    dest->len += src->len;
    strcat(dest->string, src->string);
    string_free(src);
}

void string_rm(String* dest, int n){
    if (n > dest->len) {
        fprintf(stderr, "Erreur : le string est trop court\n");
        exit(EXIT_FAILURE);
    }
    dest->len -= n;
    dest->string[dest->len] = '\0';
}

void string_free(String* dest){
    free(dest->string);
    free(dest);
}

String* au_moins_une(String** l, int n){
    String* f = new_string();
    string_append(f, "(");
    for (int i = 0; i < n; i++){
        string_append(f, l[i]->string);
        if (i < n-1){
            string_append(f, " | ");
        }
    }
    string_append(f, ")");
    return f;
}

char* au_moins_une_charetoile(char** l, int n){
    assert(n > 0);
    int lenght = 0;
    for (int i = 0; i < n; i++){
        lenght += strlen(l[i]);
    }
    char* result = malloc(sizeof(char) * (lenght + 3*n));
    result[0] = '(';
    int k = 1;
    write_f(result, l[0], &k);
    for (int i = 1; i < n; i++){
        result[k] = ' ';
        result[k+1] = '|';
        result[k+2] = ' ';
        k += 3;
        write_f(result, l[i], &k);
    }
    result[k++] = ')';
    result[k] = '\0';
    return result;
}

String* au_plus_une(String** l, int n){
    String* f = new_string();
    string_append(f, "(");
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            string_append(f, "(~");
            string_append(f, l[i]->string);
            string_append(f, " | ~");
            string_append(f, l[j]->string);
            string_append(f, ")");
            if (i < n-2){
                string_append(f, " & ");
            }
        }
    }
    string_append(f, ")");
    return f;
}

char* au_plus_une_charetoile(char** l, int n){
    assert(n > 0);
    if (n == 1) {
        return strdup("T");
    }
    int lenght = 0;
    for (int i = 0; i < n; i++){
        lenght += strlen(l[i]);
    }
    char* result = malloc(sizeof(char) * (5 * n * (n-1) + (n-1)*lenght));
    result[0] = '(';
    int k = 1;
    for (int i = 0; i < n - 2; i++){
        for (int j = i+1; j < n; j++){
            result[k++] = '(';
            result[k++] = '~';
            write_f(result, l[i], &k);
            result[k++] = ' ';
            result[k++] = '|';
            result[k++] = ' ';
            result[k++] = '~';
            write_f(result, l[j], &k);
            result[k++] = ')';
            result[k++] = ' ';
            result[k++] = '&';
            result[k++] = ' ';
        }
    }
    result[k++] = '(';
    result[k++] = '~';
    write_f(result, l[n-2], &k);
    result[k++] = ' ';
    result[k++] = '|';
    result[k++] = ' ';
    result[k++] = '~';
    write_f(result, l[n-1], &k);
    result[k++] = ')';
    result[k++] = ')';
    result[k] = '\0';
    return result;
}

String* exactement_une(String** l, int n){
    String* f = new_string();
    string_append(f, "(");
    string_cat(f, au_plus_une(l, n));
    string_append(f, " & ");
    string_cat(f, au_moins_une(l, n));
    string_append(f, ")");
    return f;
}

void write_f(char* f, char* s, int* k){
    int j = *k;
    for (int i = 0; s[i] != '\0'; i++){
        f[j + i] = s[i];
        (*k)++;
    }
}

int digits_number(int n){
    if (n == 0) return 1;
    int p = 0;
    while (n > 0){
        n /= 10;
        p++;
    }
    return p;
}

int min(int a, int b){
    if (a < b){
        return a;
    } else {
        return b;
    }
}

