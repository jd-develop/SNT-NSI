#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

/* Renvoie la variable de coordonnée i, j */
String* variable(int i, int j){
    String* f = new_string();
    char var[100];
    sprintf(var, "X_%i_%i", i, j);
    string_append(f, var);
    return f;
}

/* Renvoie une formule exprimant la contrainte sur la ligne i
   dans le problème des n dames */
String* contrainte_une_ligne(int i, int n){
    String** var_list = malloc(n*sizeof(String*));
    for (int j=0; j<n; j++){
        var_list[j] = variable(i, j);
    }
    String* f = exactement_une(var_list, n);
    for (int j=0; j<n; j++){
        string_free(var_list[j]);
    }
    free(var_list);
    return f;
}

/* Renvoie une formule exprimant la contrainte toutes les lignes
   dans le problème des n dames */
String* contrainte_toutes_lignes(int n){
    String* f = new_string();
    string_append(f, "(");
    for (int i=0; i<n; i++){
        string_cat(f, contrainte_une_ligne(i, n));
        string_append(f, " & ");
    }
    string_rm(f, 3);
    string_append(f, ")");
    return f;
}

/* Renvoie une formule exprimant la contrainte sur la colonne j
   dans le problème des n dames */
String* contrainte_une_colonne(int j, int n){
    String** var_list = malloc(n*sizeof(String*));
    for (int i=0; i<n; i++){
        var_list[i] = variable(i, j);
    }
    String* f = au_plus_une(var_list, n);
    for (int i=0; i<n; i++){
        string_free(var_list[i]);
    }
    free(var_list);
    return f;
}

/* Renvoie une formule exprimant la contrainte toutes les colonnes
   dans le problème des n dames */
String* contrainte_toutes_colonnes(int n){
    String* f = new_string();
    string_append(f, "(");
    for (int j=0; j<n; j++){
        string_cat(f, contrainte_une_colonne(j, n));
        string_append(f, " & ");
    }
    string_rm(f, 3);
    string_append(f, ")");
    return f;
}

/* Renvoie une formule exprimant la contrainte sur la diagonale 1 i
   dans le problème des n dames */
String* contrainte_une_diagonale_1(int i, int n){
    int len_var = n-abs(i);
    String** var_list = malloc(n*sizeof(String*));
    for (int j=0; j<len_var; j++){
        if (i > 0){
            var_list[j] = variable(j+i, j);
        } else {
            var_list[j] = variable(j, j-i);
        }
    }
    String* f = au_plus_une(var_list, len_var);
    for (int j=0; j<len_var; j++){
        string_free(var_list[j]);
    }
    free(var_list);
    return f;
}

/* Renvoie une formule exprimant la contrainte sur la diagonale 2 i
   dans le problème des n dames */
String* contrainte_une_diagonale_2(int i, int n){
    int len_var = n-abs(i);
    String** var_list = malloc(n*sizeof(String*));
    for (int j=0; j<len_var; j++){
        if (i > 0){
            var_list[j] = variable(j+i, n-1-j);
        } else {
            var_list[j] = variable(j, n-1-j+i);
        }
    }
    String* f = au_plus_une(var_list, len_var);
    for (int j=0; j<len_var; j++){
        string_free(var_list[j]);
    }
    free(var_list);
    return f;
}

/* Renvoie une formule exprimant la contrainte toutes les diagonales
   dans le problème des n dames */
String* contrainte_toutes_diagonales(int n){
    String* f = new_string();
    string_append(f, "(");
    for (int i=-n+2; i<n-1; i++){
        string_cat(f, contrainte_une_diagonale_1(i, n));
        string_append(f, " & ");
    }
    for (int i=-n+2; i<n-1; i++){
        string_cat(f, contrainte_une_diagonale_2(i, n));
        if (i < n-2){
            string_append(f, " & ");
        }
    }
    string_append(f, ")");
    return f;
}

/* Enregistre la formule des n dames dans filename et
   Renvoie la taille de filename */
int gen_formule_n_dames(int n, char* filename){
    FILE* file = fopen(filename, "w");
    assert(file != NULL);
    
    String* f = new_string();
    string_cat(f, contrainte_toutes_lignes(n));
    string_append(f, " & ");
    string_cat(f, contrainte_toutes_colonnes(n));
    string_append(f, " & ");
    string_cat(f, contrainte_toutes_diagonales(n));
    
    int size = f->len;
    fprintf(file, "%s", f->string);
    string_free(f);
    
    fclose(file);
    return size;
}

int main(int argc, char** argv){
    if (argc < 2){
        fprintf(stderr, "Erreur : Le nombre d'argument est insuffisant.\n");
        exit(EXIT_FAILURE);
    }
    int n;
    sscanf(argv[1], "%i", &n);
    
    char outfile[100];
    sprintf(outfile, "%i_dames.txt", n);
    
    int size = gen_formule_n_dames(n, outfile);
    printf("Fichier '%s' généré\n", outfile);
    printf("Taille du fichier: %d octets\n", size);
    return 0;
}
