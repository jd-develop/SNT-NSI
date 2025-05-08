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
int** date(int jour, int mois, int j_semaine){
    if (jour<1 || jour>31 || mois<1 || mois>12 || j_semaine<1 || j_semaine>7){
        fprintf(stderr, "Erreur : La date est invalide.\n");
        exit(EXIT_FAILURE);
    }
    int** cal_date = malloc(n_calendrier*sizeof(int*));
    for (int l=0; l<n_calendrier; l++){
        cal_date[l] = malloc(n_calendrier*sizeof(int));
        for (int c=0; c<n_calendrier; c++){
            cal_date[l][c] = calendrier[l][c];
        }
    }
    cal_date[(mois-1)/6][(mois-1)%6] = 0;
    cal_date[2+(jour-1)/7][(jour-1)%7] = 0;
    switch (j_semaine) {
        case 1: cal_date[6][4] = 0; break;
        case 2: cal_date[6][5] = 0; break;
        case 3: cal_date[6][6] = 0; break;
        case 4: cal_date[7][4] = 0; break;
        case 5: cal_date[7][5] = 0; break;
        case 6: cal_date[7][6] = 0; break;
        case 7: cal_date[6][3] = 0; break;
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
        for (int s=0; s<p.n_sym; s++){
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
int gen_formule_calendrier(int jour, int mois, int j_semaine, char* filename){
    int** cal_date = date(jour, mois, j_semaine);
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
    if (argc < 4){
        fprintf(stderr, "Erreur : Le nombre d'argument est insuffisant.\n");
        exit(EXIT_FAILURE);
    }
    int jour;
    int mois;
    int j_semaine;
    sscanf(argv[1], "%i", &j_semaine);
    sscanf(argv[2], "%i", &jour);
    sscanf(argv[3], "%i", &mois);
    
    char outfile[] = "calendrier.txt";
    
    int size = gen_formule_calendrier(jour, mois, j_semaine, outfile);
    printf("Fichier '%s' généré.\n", outfile);
    printf("Taille du fichier : %d octets\n", size);
    return 0;
}
