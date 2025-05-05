#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Renvoie X_i_j avec i,j <= 99
char* variable(int i, int j){
	assert(i <= 99 && j <= 99);
	char* var = malloc(8*sizeof(char));
	sprintf(var, "X_%d_%d", i, j);
	return var;
}

// Renvoie la formule de contrainte sur la ligne i pour un échequier de n <= 100 lignes
char* contrainte_une_ligne(int i, int n){
	assert(i <= 99 && n <= 100);
	char** l = malloc(n * sizeof(char*));
	for (int j = 0; j < n; j++){
		l[j] = variable(i, j);
	}
	char* f = malloc(sizeof(char) * (n * (12*n - 2) + 5));
	char* f1 = au_moins_une(l, n);
	char* f2 = au_plus_une(l, n);
	sprintf(f, "(%s & %s)", f1, f2);
	free(f1);
	free(f2);
	for (int i = 0; i < n; i++){
		free(l[i]);
	}
	free(l);
	return f;
}

// Renvoie la formule de contrainte sur n <= 100 lignes
char* contrainte_toutes_lignes(int n){
	assert(n <= 100);
	char* f = calloc(n*n*(12*n-2) + 8*n, sizeof(char));
	f[0] = '(';
	char* s = contrainte_une_ligne(0, n);
	int k = 1;
	write_f(f, s, &k);
	free(s);
	for (int i = 1; i < n; i++){
		s = contrainte_une_ligne(i, n);
		write_f(f, " & ", &k);
		write_f(f, s, &k);
		free(s);
	}
	f[k++] = ')';
	f[k] = '\0';
	return f;
}

// Renvoie la formule de contrainte sur la colonne j pour un échequier de n <= 100 lignes
char* contrainte_une_colonne(int j, int n){
	assert(n <= 100 && j <= 99);
	char** l = malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++){
		l[i] = variable(i, j);
	}
	char* f = au_plus_une(l, n);
	for (int i = 0; i < n; i++){
		free(l[i]);
	}
	free(l);
	return f;
}

// Renvoie la formule de contrainte sur n <= 100 lignes
char* contrainte_toutes_colonnes(int n){
	assert(n <= 100);
	char* f = calloc(12*n*n*(n-1) + 3*n + 1, sizeof(char));
	f[0] = '(';
	int k = 1;
	char* s = contrainte_une_colonne(0, n);
	write_f(f, s, &k);
	free(s);
	for (int j = 1; j < n; j++){
		s = contrainte_une_colonne(j, n);
		write_f(f, " & ", &k);
		write_f(f, s, &k);
		free(s);
	}
	f[k++] = ')';
	f[k] = '\0';
	return f;
}

/* 
Renvoie la formule de contrainte sur la diagonale commencant à (i, j) avec s le
sens de la diagonale: 1 pour lignes montantes -1 pour descandantes.
pour un échequier de n <= 100 lignes
*/
char* contrainte_une_diag(int i, int j, int s, int n){
	assert(n <= 100);
	// nombre de variables
	int nv = min(n-1-j, (1 - s) * (n - 1) / 2 + s*i) + 1;
	if (nv <= 0) {
		return strdup("T");
	}
	char** l = malloc(nv * sizeof(char*));
	for (int k = 0; k < nv; k++){
		l[k] = variable(i - s * k, j + k);
	}
	char* f = au_plus_une(l, nv);
	for (int i = 0; i < nv; i++){
		free(l[i]);
	}
	free(l);
	return f;
}

// Renvoie la formule de contrainte sur n <= 100 lignes
char* contrainte_toutes_diag(int n){
	if (n == 1){
		return strdup("T");
	}
	char* f = calloc((12 * n * (n-1) + 3) * (4*n-6), sizeof(char));
	f[0] = '(';
	int k = 1;
	char* c = contrainte_une_diag(0, 0, -1, n);
	write_f(f, c, &k);
	free(c);
	for (int s = -1; s <= 1; s = s + 2){
		// 0 si s = -1, 1 si s = 1
		int d = (1 + s) / 2;
		for (int i = 1; i <= n - 2 + d; i++){
			c = contrainte_une_diag(i, 0, s, n);
			write_f(f, " & ", &k);
			write_f(f, c, &k);
			free(c);
		}
		for (int j = 1; j <= n - 2; j++){
			c = contrainte_une_diag((n - d) % n, j, s, n);
			write_f(f, " & ", &k);
			write_f(f, c, &k);
			free(c);
		}	
	}
	
	f[k++] = ')';
	f[k] = '\0';
	return f;
}

void gen_formule_n_dames(int n, char* filename){
	char* f_lignes = contrainte_toutes_lignes(n);
	char* f_colonnes = contrainte_toutes_colonnes(n);
	char* f_diag = contrainte_toutes_diag(n);

	FILE *file = fopen(filename, "w");
	fprintf(file, "(%s & %s & %s)", f_lignes, f_colonnes, f_diag);
	fclose(file);
	free(f_lignes);
	free(f_colonnes);
	free(f_diag);
}

int main (int argc, char** argv){
	if (argc != 3) {
		perror("Ce programme prend deux arguments: le nom du fichier et la taille de l'échéquier n");
	} else {
		gen_formule_n_dames(atoi(argv[2]), argv[1]);
	}
	return 0;
}