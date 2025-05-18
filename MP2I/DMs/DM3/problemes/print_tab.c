#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Écrit dans tab les valeurs des entrées de scanf */
void input_tab(char** tab, int n){
    char input[99];
    char nom;
    int ligne;
    int col;
    while (scanf("%99[^\n]\n", input) != EOF){
        if(sscanf(input, "%c_%i_%i\n", &nom, &ligne, &col) == 3){
            if (ligne<n && col<n){
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
void print_tab(char** tab, int n){
    printf("+");
    for (int j=0; j<n; j++){
        printf("--+");
    }
    printf("\n");
    for (int i=0; i<n; i++){
        printf("|");
        for (int j=0; j<n; j++){
            printf("  ");
            if (j<n-1 && tab[i][j]==tab[i][j+1]){
                printf(" ");
            } else {
                printf("|");
            }
        }
        printf("\n");
        printf("+");
        for (int j=0; j<n; j++){
            if (i<n-1 && tab[i][j]==tab[i+1][j]){
                printf("  ");
            } else {
                printf("--");
            }
            if (i<n-1 && j<n-1 && tab[i][j]==tab[i+1][j] &&
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
    if (argc < 2){
        fprintf(stderr, "Erreur : Le nombre d'argument est insuffisant.\n");
        exit(EXIT_FAILURE);
    }
    int n;
    sscanf(argv[1], "%i", &n);
    
    char** tab = malloc(n*sizeof(char*));
    for (int i=0; i<n; i++){
        tab[i] = malloc(n*sizeof(char*));
        for (int j=0; j<n; j++){
            tab[i][j] = ' ';
        }
    }
    
    input_tab(tab, n);
    print_tab(tab, n);
    
    for (int i=0; i<n; i++){
        free(tab[i]);
    }
    free(tab);
    return 0;
}
