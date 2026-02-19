#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int* solution;


/* Affiche la solution sol de taille n */
void affiche_solution(int n, solution sol) {
    for (int i = 0; i < n; i++) {
        printf("%d\t", i);
        for (int j = 0; j < n; j++) {
            if (sol[i] == j)
                printf("#");
            else
                printf(".");
        }
        printf("\n");
    }
}

/* Renvoie true s’il est possible de placer une dame en ligne nbl et en colonne
 * col sans être à la portée de la dame se situant à la ligne i de sol */
bool est_extension_valide_dame_i(solution sol, int i, int nbl, int col) {
    /* Il y a deux cas :
     * 1. On se situe sur la même colonne
     * 2. On se situe sur la diagonale */
    // Colonne
    if (col == sol[i]) {
        return false;
    }
    // Diagonale
    if (col == sol[i] + (nbl-i) || col == sol[i] - (nbl-i)) {
        return false;
    }
    return true;
}

/* Renvoie true s’il est possible de placer une dame en ligne nbl et en colonne
 * col sans invalider la solution partielle définie sur les nbl premières lignes
 * de sol */
bool est_extension_valide(solution sol, int nbl, int col) {
    bool res = true;
    for (int i = 0; i < nbl && res; i++) {
        res = est_extension_valide_dame_i(sol, i, nbl, col);
    }
    return res;
}

/* Cet algorithme, au pire, explore chaque possibilité, i.e. n appels à la
 * première ligne, qui entraîne n^2 appels à la seconde ligne, etc. jusqu’à
 * un total de n^n appels */

/* Sur un échiquier 2×2, on obtient l’arbre suivant :
 *                                 appel
 *                                /    \
 *  ligne 0 :            colonne 0      colonne 1
 *                     /      |          |     \
 *  ligne 1 : colonne 0   colonne 1  colonne 0  colonne 1 */


/* Renvoie true si on peut compléter la solution partielle sol (valide sur
 * les nbl premières lignes), en une solution valide sur les n lignes, auquel
 * cas sol est mis à jour pour contenir cette solution */
bool peut_etre_completee(solution sol, int nbl, int n) {
    if (nbl == n) {
        return true;
    }
    bool res = false;
    // On résoud récursivement sur les colonnes
    for (int j = 0; j < n && !res; j++) {
        if (est_extension_valide(sol, nbl, j)) {
            sol[nbl] = j;
            res = peut_etre_completee(sol, nbl+1, n);
        }
    }
    // if (!res) sol[nbl] = -1;  // à voir si c’est pertinent
    return res;
}

/* Teste s’il existe une solution au problème des n dames et affiche le
 * résultat */
void resolution_deterministe(int n) {
    solution sol = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        sol[i] = -1;
    }
    if (peut_etre_completee(sol, 0, n))
        affiche_solution(n, sol);
    else
        printf("Pas de solution trouvée pour une taille %d×%d !\n", n, n);
    free(sol);
}

/*      partie 2      */

/* Remplit dans tab_pos les indices des colonnes valides pour placer des
 * dames sur la ligne nbl au regard de la solution partielle décrite
 * par les nbl premières lignes de sol, et renvoie le nombre de telles
 * colonnes valides. */
int positions_valides(solution sol, int nbl, int n, int* tab_pos) {
    int nb_solutions = 0;
    for (int col = 0; col < n; col++) {
        if (est_extension_valide(sol, nbl, col))
            tab_pos[nb_solutions++] = col;
    }
    return nb_solutions;
}


/* Tente de construire une solution valide de taille n par l’algo probabliliste,
 * et renvoie si cette tentative a réussi, auquel cas le tableau tab_sol est
 * mis à jour pour stocker une telle solution */
/*bool generation_aleatoire(int n, solution tab_sol) {
    // TODO
}*/


int main() {
    int sol1[4] = {3, 0, -1, -1};
    int sol_ex[4] = {1, 3, 0, 3};

    /* Tests affiche_solution */
    affiche_solution(4, sol1);
    printf("\n");
    affiche_solution(4, sol_ex);

    /* Tests est_extension_valide */
    assert(!est_extension_valide(sol_ex, 3, 0));
    assert(!est_extension_valide(sol_ex, 3, 1));
    assert(est_extension_valide(sol_ex, 3, 2));

    /* Affiche la résolution pour n=20 */
    printf("\n");
    resolution_deterministe(20);

    return 0;
}

