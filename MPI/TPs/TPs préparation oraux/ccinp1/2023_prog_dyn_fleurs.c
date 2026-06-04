/******************************************************/
/* Concours commun INP                                */
/* https://www.concours-commun-inp.fr                 */
/* CC BY-NC-SA, Novembre 2023                         */
/* https://creativecommons.org/licenses/by-nc-sa/4.0/ */
/******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
La directive #define est utilisée pour définir des valeurs pour
des constantes qui serviront à déclarer des fleursleaux de taille fixe.
*/
#define m 4
#define n 4

/* Macro de calcul du maximum entre i et j */
int max(int i,int j){
    if (i<j)
        return j;
    else
        return i;
}


int recolte(int champ[m][n], int i, int j){
    if (i == 0 && j == 0) {
        return champ[i][j];
    } else if (i == 0) {
        return champ[i][j] + recolte(champ, i, j-1);
    } else if (j == 0) {
        return champ[i][j] + recolte(champ, i-1, j);
    } else {
        return champ[i][j] + max(recolte(champ, i-1, j), recolte(champ, i, j-1));
    }
}

void deplacements(int fleurs[m][n], int i, int j){
    int i_courant = i;
    int j_courant = j;
    while (i_courant != 0 || j_courant != 0) {
        printf("%d, %d <- ", i_courant, j_courant);
        if (i_courant == 0) {
           j_courant--;
        } else if (j_courant == 0) {
           i_courant--;
        } else {
            if (fleurs[i_courant-1][j_courant] > fleurs[i_courant][j_courant-1]) {
                i_courant--;
            } else {
                j_courant--;
            }
        }
    }
    printf("0, 0\n");
}


int recolte_iterative(int champ[m][n], int i, int j, int fleurs[m][n]){
    for (int k = 0; k <= i; k++) {
        for (int l = 0; l <= j; l++) {
            if (k == 0 && l == 0) {
                fleurs[k][l] = champ[k][l];
            } else if (k == 0) {
                fleurs[k][l] = champ[k][l] + fleurs[k][l-1];
            } else if (l == 0) {
                fleurs[k][l] = champ[k][l] + fleurs[k-1][l];
            } else {
                fleurs[k][l] = champ[k][l] + max(fleurs[k][l-1], fleurs[k-1][l]);
            }
        }
    }
    deplacements(fleurs, i, j);
    return fleurs[i][j];
}




int main(){
    int champ_test[4][4];
    int fleurs0[4][4];
    for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
            champ_test[i][j] = (i+j) % 5;
        }
    }
    printf("%d\n", recolte_iterative(champ_test, 3, 3, fleurs0));

    int champ[m][n],fleurs[m][n];
    int i,j;

    /* Exemple du champ de fleurs : le nombre de fleurs par case est un entier
    aléatoire entre 0 et 10. On utilise la fonction int rand() de stdlib. Le générateur
    de nombre pseudo-aléatoires est tout d'abord initialisé.*/
    srand(time(NULL));
    for (i=0;i<m;i++) for(j=0;j<n;j++)
         champ[i][j] = rand() % 11;

    printf("\nNombre de fleurs maximum cueillies : %d\n",recolte_iterative(champ,3,3,fleurs));
    //printf("%d\n", recolte(champ, 3, 3));

    return 0;
}

