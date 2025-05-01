#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Écrit dans tab les valeurs des entrées de scanf */
void input_tab(char** tab, int n_ligne, int n_col){
	char input[99];
	char nom;
	int ligne;
	int col;
	while (scanf("%99[^\n]\n", input) != EOF){
		if(sscanf(input, "%c_%i_%i\n", &nom, &ligne, &col) == 3){
			if (ligne<n_ligne && col<n_col){
				tab[ligne][col] = nom;
			} else {
				fprintf(stderr, "Erreur : La taille du tableau est incorrect.\n");
				exit(EXIT_FAILURE);
			}
		}
		printf("%s\n", input);
	}
	return;
}

/* Affiche tab */
void print_tab(char** tab, int n_ligne, int n_col){
	printf("+");
	for (int j=0; j<n_col; j++){
		printf("--+");
	}
	printf("\n");
	for (int i=0; i<n_ligne; i++){
		printf("|");
		for (int j=0; j<n_col; j++){
			printf("  ");
			if (j<n_col-1 && tab[i][j]==tab[i][j+1]){
				printf(" ");
			} else {
				printf("|");
			}
		}
		printf("\n");
		printf("+");
		for (int j=0; j<n_col; j++){
			if (i<n_ligne-1 && tab[i][j]==tab[i+1][j]){
				printf("  ");
			} else {
				printf("--");
			}
			if (i<n_ligne-1 && j<n_col-1 && tab[i][j]==tab[i+1][j] &&
				tab[i][j]==tab[i][j+1] && tab[i][j]==tab[i+1][j+1]){
				printf(" ");
			} else {
				printf("+");
			}
		}
		printf("\n");
	}
}

int main(int argc, char** argv){
	if (argc < 3){
		fprintf(stderr, "Erreur : Le nombre d'argument est insuffisant.\n");
		exit(EXIT_FAILURE);
	}
	int n_ligne;
	int n_col;
	sscanf(argv[1], "%i", &n_ligne);
	sscanf(argv[2], "%i", &n_col);
	
	char** tab = malloc(n_ligne*sizeof(char*));
	for (int i=0; i<n_ligne; i++){
		tab[i] = malloc(n_col*sizeof(char*));
		for (int j=0; j<n_col; j++){
			tab[i][j] = ' ';
		}
	}
	
	input_tab(tab, n_ligne, n_col);
	print_tab(tab, n_ligne, n_col);
	
	for (int i=0; i<n_ligne; i++){
		free(tab[i]);
	}
	free(tab);
	return 0;
}
