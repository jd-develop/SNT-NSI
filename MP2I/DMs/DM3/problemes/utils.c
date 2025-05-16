#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

String* exactement_une(String** l, int n){
    String* f = new_string();
    string_append(f, "(");
    string_cat(f, au_plus_une(l, n));
    string_append(f, " & ");
    string_cat(f, au_moins_une(l, n));
    string_append(f, ")");
    return f;
}
