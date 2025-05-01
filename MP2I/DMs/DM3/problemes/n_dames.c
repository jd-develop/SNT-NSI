#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

/* Renvoie la variable de coordonnée i, j */
char* variable(int i, int j){
	char* var = malloc(100*sizeof(char));
	sprintf(var, "X_%i_%i", i, j);
	return var;
}

/* Renvoie une formule exprimant la contrainte sur la ligne i
   dans le problème des n dames */
char* contrainte_une_ligne(int i, int n){
	char** var_list = malloc(n*sizeof(char*));
	for (int j=0; j<n; j++){
		var_list[j] = variable(i, j);
	}
	char* f = exactement_une(var_list, n);
	for (int j=0; j<n; j++){
		free(var_list[j]);
	}
	free(var_list);
	return f;
}

/* Renvoie une formule exprimant la contrainte toutes les lignes
   dans le problème des n dames */
char* contrainte_toutes_lignes(int n){
	char* f = strdup("(");
	for (int i=0; i<n; i++){
		char* ligne = contrainte_une_ligne(i, n);
		safe_strcat(&f, ligne);
		free(ligne);
		if (i < n-1){
			safe_strcat(&f, " & ");
		}
	}
	safe_strcat(&f, ")");
	return f;
}

/* Renvoie une formule exprimant la contrainte sur la colonne j
   dans le problème des n dames */
char* contrainte_une_colonne(int j, int n){
	char** var_list = malloc(n*sizeof(char*));
	for (int i=0; i<n; i++){
		var_list[i] = variable(i, j);
	}
	char* f = au_plus_une(var_list, n);
	for (int i=0; i<n; i++){
		free(var_list[i]);
	}
	free(var_list);
	return f;
}

/* Renvoie une formule exprimant la contrainte toutes les colonnes
   dans le problème des n dames */
char* contrainte_toutes_colonnes(int n){
	char* f = strdup("(");
	for (int j=0; j<n; j++){
		char* col = contrainte_une_colonne(j, n);
		safe_strcat(&f, col);
		free(col);
		if (j < n-1){
			safe_strcat(&f, " & ");
		}
	}
	safe_strcat(&f, ")");
	return f;
}

/* Renvoie une formule exprimant la contrainte sur la diagonale 1 i
   dans le problème des n dames */
char* contrainte_une_diagonale_1(int i, int n){
	int len_var = n-abs(i);
	char** var_list = malloc(n*sizeof(char*));
	for (int j=0; j<len_var; j++){
		if (i > 0){
			var_list[j] = variable(j+i, j);
		} else {
			var_list[j] = variable(j, j-i);
		}
	}
	char* f = au_plus_une(var_list, len_var);
	for (int j=0; j<len_var; j++){
		free(var_list[j]);
	}
	free(var_list);
	return f;
}

/* Renvoie une formule exprimant la contrainte sur la diagonale 2 i
   dans le problème des n dames */
char* contrainte_une_diagonale_2(int i, int n){
	int len_var = n-abs(i);
	char** var_list = malloc(n*sizeof(char*));
	for (int j=0; j<len_var; j++){
		if (i > 0){
			var_list[j] = variable(j+i, n-1-j);
		} else {
			var_list[j] = variable(j, n-1-j+i);
		}
	}
	char* f = au_plus_une(var_list, len_var);
	for (int j=0; j<len_var; j++){
		free(var_list[j]);
	}
	free(var_list);
	return f;
}

/* Renvoie une formule exprimant la contrainte toutes les diagonales
   dans le problème des n dames */
char* contrainte_toutes_diagonales(int n){
	char* f = strdup("(");
	for (int i=-n+2; i<n-1; i++){
		char* diag = contrainte_une_diagonale_1(i, n);
		safe_strcat(&f, diag);
		free(diag);
		safe_strcat(&f, " & ");
	}
	for (int i=-n+2; i<n-1; i++){
		char* diag = contrainte_une_diagonale_2(i, n);
		safe_strcat(&f, diag);
		free(diag);
		if (i < n-2){
			safe_strcat(&f, " & ");
		}
	}
	safe_strcat(&f, ")");
	return f;
}

/* Enregistre la formule des n dames dans filename et
   Renvoie la taille de filename */
int gen_formule_n_dames(int n, char* filename){
	int size = 0;
	FILE* file = fopen(filename, "w");
	assert(file != NULL);
	
	char* ligne = contrainte_toutes_lignes(n);
	size += strlen(ligne);
	fprintf(file, "%s", ligne);
	free(ligne);
	
	size += 3;
	fprintf(file, " & ");
	
	char* col = contrainte_toutes_colonnes(n);
	size += strlen(col);
	fprintf(file, "%s", col);
	free(col);
	
	size += 3;
	fprintf(file, " & ");
	
	char* diag = contrainte_toutes_diagonales(n);
	size += strlen(diag);
	fprintf(file, "%s", diag);
	free(diag);
	
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
