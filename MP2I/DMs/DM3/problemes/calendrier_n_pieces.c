#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "utils.h"
#include "piece.h"

/* calendrier */
int n_calendrier = 8;
int calendrier[8][8] = {
    {1,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {0,0,0,0,1,1,1,0}
};

/* Renvoie la variable de nom n, de coordonnée l c */
String* variable(char n, int l, int c){
    String* f = new_string();
    char var[100];
    sprintf(var, "%c_%i_%i", n, l, c);
    string_append(f, var);
    return f;
}

/* Renvoie le calendrier avec la dates marquer */
int** date(){
    int** cal_date = malloc(n_calendrier*sizeof(int*));
    for (int l=0; l<n_calendrier; l++){
        cal_date[l] = malloc(n_calendrier*sizeof(int));
        for (int c=0; c<n_calendrier; c++){
            cal_date[l][c] = calendrier[l][c];
        }
    }
    cal_date[0][5] = 0;
    cal_date[2][6] = 0;
    cal_date[7][4] = 0;
    if (n_pieces < 10){ //l
        cal_date[2][0] = 0;
        cal_date[2][1] = 0;
        cal_date[2][2] = 0;
        cal_date[3][0] = 0;
    }
    if (n_pieces < 9){ //s
        cal_date[3][1] = 0;
        cal_date[3][2] = 0;
        cal_date[4][0] = 0;
        cal_date[4][1] = 0;
    }
    if (n_pieces < 8){ //Z
        cal_date[4][2] = 0;
        cal_date[5][0] = 0;
        cal_date[5][1] = 0;
        cal_date[5][2] = 0;
        cal_date[6][0] = 0;
    }
    if (n_pieces < 7){ //S
        cal_date[5][3] = 0;
        cal_date[5][4] = 0;
        cal_date[6][1] = 0;
        cal_date[6][2] = 0;
        cal_date[6][3] = 0;
    }
    if (n_pieces < 6){ //I
        cal_date[1][3] = 0;
        cal_date[2][3] = 0;
        cal_date[3][3] = 0;
        cal_date[4][3] = 0;
    }
    if (n_pieces < 5){ //C
        cal_date[4][4] = 0;
        cal_date[4][5] = 0;
        cal_date[5][5] = 0;
        cal_date[6][4] = 0;
        cal_date[6][5] = 0;
    }
    if (n_pieces < 4){ //L
        cal_date[4][6] = 0;
        cal_date[5][6] = 0;
        cal_date[6][6] = 0;
        cal_date[7][5] = 0;
        cal_date[7][6] = 0;
    }
    if (n_pieces < 3){ //b
        cal_date[0][0] = 0;
        cal_date[0][1] = 0;
        cal_date[1][0] = 0;
        cal_date[1][1] = 0;
        cal_date[1][2] = 0;
    }
    if (n_pieces < 2){ //V
        cal_date[0][2] = 0;
        cal_date[0][3] = 0;
        cal_date[0][4] = 0;
        cal_date[1][4] = 0;
        cal_date[2][4] = 0;
    }
    if (n_pieces < 1){ //T
        cal_date[1][5] = 0;
        cal_date[2][5] = 0;
        cal_date[3][4] = 0;
        cal_date[3][5] = 0;
        cal_date[3][6] = 0;
    }
    for (int l=0; l<n_calendrier; l++){
        for (int c=0; c<n_calendrier; c++){
            printf("%i", cal_date[l][c]);
        }
        printf("\n");
    }
    return cal_date;
}

/* Si la pièce p de position l, c est valide dans cal_date */
bool piece_valide(Piece p, int l, int c, int** cal_date){
    if (l<0 || l+p.n_ligne-1>=n_calendrier ||
        c<0 || c+p.n_col-1>=n_calendrier ){
        return false;
    }
    for (int i=0; i<p.n_ligne; i++){
        for (int j=0; j<p.n_col; j++){
            if (p.tab[i][j] == 1 && cal_date[l+i][c+j] == 0){
                return false;
            }
        }
    }
    return true;
}

/* Renvoie une formule exprimant la contrainte de la pièce p en l c,
   avec alias le nom d'une variable intermédiaire,
   dans le problème du calendrier */
String* contrainte_piece_pos(Piece p, int l, int c, char* alias, int** cal_date){
    String* f = new_string();
    String* var;
    for (int i=0; i<n_calendrier; i++){
        for (int j=0; j<n_calendrier; j++){
            if (cal_date[i][j] == 1){
                string_append(f, "(~");
                string_append(f, alias);
                string_append(f, " | ");
                var = variable(p.nom, i, j);
                if (l<=i && i<l+p.n_ligne && c<=j && j<c+p.n_col
                    && p.tab[i-l][j-c] == 1){
                    string_cat(f, var);
                } else {
                    string_append(f, "~");
                    string_cat(f, var);
                }
                string_append(f, ") & ");
            }
        }
    }
    string_rm(f, 3);
    return f;
}

/* Renvoie une formule exprimant la contrainte de la pièce p,
   dans le problème du calendrier */
String* contrainte_une_piece(Piece p, int** cal_date){
    String* f = new_string();
    char alias[100];
    int k = 0;
    for (int r=0; r<p.n_rot; r++){
        for (int s=0; s<2; s++){
            for (int l=0; l<n_calendrier; l++){
                for (int c=0; c<n_calendrier; c++){
                    if (piece_valide(p, l, c, cal_date)){
                        sprintf(alias, "alias_%c%i", p.nom, k++);
                        string_cat(f, contrainte_piece_pos(p, l, c, alias, cal_date));
                        string_append(f, " & ");
                    }
                }
            }
            p = symetrie(p);
        }
        p = rotation(p);
    }
    string_append(f, "(");
    for (int i=0; i<k; i++){
        sprintf(alias, "alias_%c%i", p.nom, i);
        string_append(f, alias);
        string_append(f, " | ");
    }
    string_rm(f, 3);
    string_append(f, ")");
    return f;
}

/* Renvoie une formule exprimant la contrainte de toutes les pieces,
   dans le problème du calendrier */
String* contrainte_toutes_pieces(int** cal_date){
    String* f = new_string();
    string_append(f, "(");
    String* var;
    for (int k_p=0; k_p<n_pieces; k_p++){
        var = contrainte_une_piece(pieces[k_p], cal_date);
        string_cat(f, var);
        string_append(f, " & ");
    }
    string_rm(f, 3);
    string_append(f, ")");
    return f;
}

/* Renvoie une formule exprimant la contrainte de la case l c,
   dans le problème du calendrier */
String* contrainte_une_case(int l, int c){
    String** var_list = malloc(n_pieces*sizeof(char*));
    for (int k_p=0; k_p<n_pieces; k_p++){
        var_list[k_p] = variable(pieces[k_p].nom, l, c);
    }
    String* f = exactement_une(var_list, n_pieces);
    for (int k_p=0; k_p<n_pieces; k_p++){
        string_free(var_list[k_p]);
    }
    free(var_list);
    return f;
}

/* Renvoie une formule exprimant la contrainte de toutes les cases,
   dans le problème du calendrier */
String* contrainte_toutes_cases(int** cal_date){
    String* f = new_string();
    string_append(f, "(");
    String* var;
    for (int l=0; l<n_calendrier; l++){
        for (int c=0; c<n_calendrier; c++){
            if (cal_date[l][c] == 1){
                var = contrainte_une_case(l, c);
                string_cat(f, var);
                string_append(f, " & ");
            }
        }
    }
    string_rm(f, 3);
    string_append(f, ")");
    return f;
}

/* Enregistre la formule du calendrier dans filename et
   Renvoie la taille de filename */
int gen_formule_calendrier(char* filename){
    int** cal_date = date();
    FILE* file = fopen(filename, "w");
    assert(file != NULL);
    
    String* f = new_string();
    string_cat(f,contrainte_toutes_pieces(cal_date));
    string_append(f, " & ");
    string_cat(f,contrainte_toutes_cases(cal_date));
    
    int size = f->len;
    fprintf(file, "%s", f->string);
    string_free(f);
    
    fclose(file);
    for (int i=0; i<n_calendrier; i++){
            free(cal_date[i]);
    }
    free(cal_date);
    return size;
}

int main(int argc, char** argv){
    if (argc < 2){
        fprintf(stderr, "Erreur : Le nombre d'argument est insuffisant.\n");
        exit(EXIT_FAILURE);
    }
    sscanf(argv[1], "%i", &n_pieces);
    if (n_pieces < 2 || n_pieces > 10){
        fprintf(stderr, "Erreur : L'argument doit être compris entre 2 et 10.\n");
        exit(EXIT_FAILURE);
    }
    
    char outfile[100];
    sprintf(outfile, "calendrier_%i_pieces.txt", n_pieces);
    
    int size = gen_formule_calendrier(outfile);
    printf("Fichier '%s' généré.\n", outfile);
    printf("Taille du fichier : %d octets.\n", size);
    return 0;
}
