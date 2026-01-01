#include "laby.h"
// codes couleurs ANSI
#define GREEN "\033[92m"
#define RESET "\033[00m"

void draw_laby(laby_t laby) {
    // affiche le labyrinthe laby avec des caractères ASCII
    for (int j = 0; j < laby.width; j++) {
        printf("+-");
    }
    printf("+\n");
    for (int i = 0; i < laby.height - 1; i++) {
        printf("| ");
        for (int j = 0; j < laby.width - 1; j++) {
            int c = laby.cells[i * laby.width + j];
            if (c % 2 == 1) {
                printf("| ");
            } else {
                printf("  ");
            }
        }
        printf("|\n");
        printf("+");
        for (int j = 0; j < laby.width; j++) {
            int c = laby.cells[i * laby.width + j];
            if ((c / 2) % 2 == 1) {
                printf("-+");
            } else {
                printf(" +");
            }
        }
        printf("\n");
    }
    printf("| ");
    for (int j = 0; j < laby.width - 1; j++) {
        int c = laby.cells[(laby.height - 1) * laby.width + j];
        if (c % 2 == 1) {
            printf("| ");
        } else {
            printf("  ");
        }
    }
    printf("|\n");
    printf("+");
    for (int j = 0; j < laby.width; j++) {
        printf("-+");
    }
    printf("\n");
}

void draw_laby_with_visited(laby_t laby, bool *visited) {
    // affiche le labyrinthe laby et le chemin décrit par visited en ASCII
    /* note : j’ai pris l’initiative de remplacer les · par des # et de les
     * mettre en vert afin de mieux voir le chemin */
    for (int j = 0; j < laby.width; j++) {
        printf("+-");
    }
    printf("+\n");
    for (int i = 0; i < laby.height - 1; i++) {
        printf("|");
        for (int j = 0; j < laby.width - 1; j++) {
            if (visited[i * laby.width + j]) {
                printf("%s#%s", GREEN, RESET);
            } else {
                printf(" ");
            }
            int c = laby.cells[i * laby.width + j];
            if (c % 2 == 1) {
                printf("|");
            } else {
                if (visited[i * laby.width + j] &&
                    visited[i * laby.width + j + 1]) {
                    printf("%s#%s", GREEN, RESET);
                } else {
                    printf(" ");
                }
            }
        }
        if (visited[i * laby.width + laby.width - 1]) {
            printf("%s#%s", GREEN, RESET);
        } else {
            printf(" ");
        }
        printf("|\n");
        printf("+");
        for (int j = 0; j < laby.width; j++) {
            int c = laby.cells[i * laby.width + j];
            if ((c / 2) % 2 == 1) {
                printf("-+");
            } else {
                if (visited[i * laby.width + j] &&
                    visited[(i + 1) * laby.width + j]) {
                    printf("%s#%s+", GREEN, RESET);
                } else {
                    printf(" +");
                }
            }
        }
        printf("\n");
    }
    printf("|");
    for (int j = 0; j < laby.width - 1; j++) {
        if (visited[(laby.height - 1) * laby.width + j]) {
            printf("%s#%s", GREEN, RESET);
        } else {
            printf(" ");
        }
        int c = laby.cells[(laby.height - 1) * laby.width + j];
        if (c % 2 == 1) {
            printf("|");
        } else {
            if (visited[(laby.height - 1) * laby.width + j] &&
                visited[(laby.height - 1) * laby.width + j + 1]) {
                printf("%s#%s", GREEN, RESET);
            } else {
                printf(" ");
            }
        }
    }
    if (visited[(laby.height - 1) * laby.width + laby.width - 1]) {
        printf("%s#%s", GREEN, RESET);
    } else {
        printf(" ");
    }
    printf("|\n");
    printf("+");
    for (int j = 0; j < laby.width; j++) {
        printf("-+");
    }
    printf("\n");
}

bool is_laby_plein(laby_t laby) {
    // teste si le labyrinthe laby est plein
    for (int k = 0; k < laby.height; k++) {
        if (laby.cells[k] != 3)
            return false;
        // 3 est le type des cases ac mur sud et mur est
    }
    return true;
}

int linearise(laby_t laby, int i, int j) {
    // indice ds le tableau unidimensionnel de la case de coordonnées (i,j)
    // dans le tableau bidimensionnel aux dimensions de laby
    return i * laby.width + j;
}

void delinearise(laby_t laby, int x, int *pi, int *pj) {
    // modifie les valeurs de *pi et *pj pour qu'ils enregistrent les
    // coordoonées dans le tableau bidimensionnel aux dimensions de laby *
    // de la case d'indice x dans le tableau    unidimensionnel correspondant
    *pi = x / laby.width;
    *pj = x % laby.width;
}

bool is_in_laby(laby_t laby, int i, int j) {
    return i >= 0 && j >= 0 && i < laby.height && j < laby.width;
    // teste si la case de coordonnées (i,j) est dans laby
}

bool can_go_from(laby_t laby, int i1, int j1, int i2, int j2) {
    // hypothèse : is_in_laby(laby,i1,j1) && is_in_laby(laby,i2,j2)
    // teste l'abscence de mur entre les cases (i1,j1) et (i2,j2) ds laby
    if (i1 == i2 && j2 == j1 + 1) { // 1 à gauche, 2 à droite
        return laby.cells[linearise(laby, i1, j1)] % 2 == 0;
    } else if (i1 == i2 && j2 == j1 - 1) { // 2 à gauche, 1 à droite
        return laby.cells[linearise(laby, i2, j2)] % 2 == 0;
    } else if (i2 == i1 + 1 && j1 == j2) { // 1 au dessus, 2 en dessous
        return laby.cells[linearise(laby, i1, j1)] / 2 % 2 == 0;
    } else if (i1 == i2 + 1 && j1 == j2) { // 2 au dessus, 1 en dessous
        return laby.cells[linearise(laby, i2, j2)] / 2 % 2 == 0;
    } else {
        return false;
    }
}

void casse_mur(laby_t laby, int i1, int j1, int i2, int j2) {
    // hypothèse : is_in_laby(laby,i1,j1) && is_in_laby(laby,i2,j2)
    // casse le mur entre la case (i1,j1) et la case (i2,j2) dans laby
    if (i1 == i2 && j2 == j1 + 1) {
        laby.cells[linearise(laby, i1, j1)] =
            (laby.cells[linearise(laby, i1, j1)] / 2) * 2;
    } else if (i1 == i2 && j2 == j1 - 1) {
        laby.cells[linearise(laby, i2, j2)] =
            (laby.cells[linearise(laby, i2, j2)] / 2) * 2;
    } else if (i2 == i1 + 1 && j1 == j2) {
        laby.cells[linearise(laby, i1, j1)] =
            laby.cells[linearise(laby, i1, j1)] % 2;
    } else if (i1 == i2 + 1 && j1 == j2) {
        laby.cells[linearise(laby, i2, j2)] =
            laby.cells[linearise(laby, i2, j2)] % 2;
    }
}

/* Sachant un labyrinthe non encore parfait laby, casse des murs des cases dont
 * visited est à false à partir de la case d’indice (i, j) au moyen d’un
 * parcours en profondeur, jusqu’à ce que le labyrinthe soit parfait. Ne fait
 * rien si (i, j) est une case invalide dans le labyrinthe. */
void rec_generator(laby_t laby, bool *visited, int i, int j) {
    if (!visited[linearise(laby, i, j)]) {
        visited[linearise(laby, i, j)] = true;
        /* On initialise un tableau pour se souvenir quelles directions on a
         * visité. On choisit arbitrairement :
         * * 0 : nord
         * * 1 : est
         * * 2 : sud
         * * 3 : ouest
         */
        int directions[4] = {-1, -1, -1, -1};
        for (int k = 0; k < 4; k++) {
            bool ok = true;
            do {
                ok = true;
                // on choisit une direction
                directions[k] = rand() % 4;
                // on regarde si on l’a déjà choisie
                for (int j = 0; j < k; j++) {
                    if (directions[k] == directions[j]) {
                        // si oui, on recommence la boucle do-while
                        ok = false;
                        break;
                    }
                }
            } while (!ok);
            // on a une direction qu’on n’a pas encore faite
            if (directions[k] == 0) { // nord
                if (
                        is_in_laby(laby, i - 1, j) &&
                        !visited[linearise(laby, i - 1, j)]
                ) {
                    casse_mur(laby, i, j, i - 1, j);
                    rec_generator(laby, visited, i - 1, j);
                }
            } else if (directions[k] == 1) { // est
                if (
                        is_in_laby(laby, i, j + 1) &&
                        !visited[linearise(laby, i, j + 1)]
                ) {
                    casse_mur(laby, i, j, i, j + 1);
                    rec_generator(laby, visited, i, j + 1);
                }
            } else if (directions[k] == 2) { // sud
                if (
                        is_in_laby(laby, i + 1, j) &&
                        !visited[linearise(laby, i + 1, j)]
                ) {
                    casse_mur(laby, i, j, i + 1, j);
                    rec_generator(laby, visited, i + 1, j);
                }
            } else if (directions[k] == 3) {
                if (
                        is_in_laby(laby, i, j - 1) &&
                        !visited[linearise(laby, i, j - 1)]
                ) {
                    casse_mur(laby, i, j, i, j - 1);
                    rec_generator(laby, visited, i, j - 1);
                }
            }
        }
    }
}

/* Génère un labyrinthe parfait à partir du labyrinthe plein laby */
void generate_laby(laby_t laby) {
    int w = laby.width;
    int h = laby.height;
    bool* visited = malloc(w * h * sizeof(bool));
    for (int i = 0; i < w*h; i++) {
        visited[i] = false;
    }
    rec_generator(laby, visited, 0, 0);
    free(visited);
}


/* Idem, mais sans récursivité */
void generate_laby_q2(laby_t laby) {
    /* pour une cellule, stocke les directions essayées (même rôle que le
     * tableau directions dans la version récursive) */
    struct cell_directions {
        int cell;
        bool directions[4];
    };
    int w = laby.width;
    int h = laby.height;
    bool *visited = malloc(w * h * sizeof(bool));
    for (int i = 0; i < w*h; i++) {
        visited[i] = false;
    }

    struct cell_directions *pile =
        malloc(w * h * sizeof(struct cell_directions));
    pile[0].cell = 0;
    pile[0].directions[0] = false;
    pile[0].directions[1] = false;
    pile[0].directions[2] = false;
    pile[0].directions[3] = false;
    int tete_pile = 0;

    int i;
    int j;

    while (tete_pile != -1) {
        visited[pile[tete_pile].cell] = true;

        // si on a testé toutes les directions -> on dépile
        bool tout_teste = true;
        for (int k = 0; k < 4; k++) {
            if (!pile[tete_pile].directions[k]) {
                tout_teste = false;
                break;
            }
        }
        if (tout_teste) {
            tete_pile--;
        } else {
            int direction;
            bool ok = true;
            do {
                ok = true;
                // on choisit une direction
                direction = rand() % 4;
                // on regarde si on l’a déjà choisie
                if (pile[tete_pile].directions[direction])
                    ok = false;
            } while (!ok);

            pile[tete_pile].directions[direction] = true;
            delinearise(laby, pile[tete_pile].cell, &i, &j);

            // on a une direction qu’on n’a pas encore faite
            if (direction == 0) { // nord
                if (
                        is_in_laby(laby, i - 1, j) &&
                        !visited[linearise(laby, i - 1, j)]
                ) {
                    casse_mur(laby, i, j, i - 1, j);
                    tete_pile++;
                    pile[tete_pile].cell = linearise(laby, i - 1, j);
                    pile[tete_pile].directions[0] = false;
                    pile[tete_pile].directions[1] = false;
                    pile[tete_pile].directions[2] = true;
                    pile[tete_pile].directions[3] = false;
                }
            } else if (direction == 1) { // est
                if (
                        is_in_laby(laby, i, j + 1) &&
                        !visited[linearise(laby, i, j + 1)]
                ) {
                    casse_mur(laby, i, j, i, j + 1);
                    tete_pile++;
                    pile[tete_pile].cell = linearise(laby, i, j + 1);
                    pile[tete_pile].directions[0] = false;
                    pile[tete_pile].directions[1] = false;
                    pile[tete_pile].directions[2] = false;
                    pile[tete_pile].directions[3] = true;
                }
            } else if (direction == 2) { // sud
                if (
                        is_in_laby(laby, i + 1, j) &&
                        !visited[linearise(laby, i + 1, j)]
                ) {
                    casse_mur(laby, i, j, i + 1, j);
                    tete_pile++;
                    pile[tete_pile].cell = linearise(laby, i + 1, j);
                    pile[tete_pile].directions[0] = true;
                    pile[tete_pile].directions[1] = false;
                    pile[tete_pile].directions[2] = false;
                    pile[tete_pile].directions[3] = false;
                }
            } else if (direction == 3) {
                if (
                        is_in_laby(laby, i, j - 1) &&
                        !visited[linearise(laby, i, j - 1)]
                ) {
                    casse_mur(laby, i, j, i, j - 1);
                    tete_pile++;
                    pile[tete_pile].cell = linearise(laby, i, j - 1);
                    pile[tete_pile].directions[0] = false;
                    pile[tete_pile].directions[1] = true;
                    pile[tete_pile].directions[2] = false;
                    pile[tete_pile].directions[3] = false;
                }
            }
        }
    }

    free(pile);
    free(visited);
}


/*
bool rec_solver(laby_t laby, bool *chemin, int i, int j);
bool* solve_labyrinthe(laby_t laby);
*/

/* Renvoie le tableau contenant tous les murs du labyrinthe plein de même taille
 * que laby */
mur_t* tab_murs_laby_plein(laby_t laby) {
    int h = laby.height;
    int w = laby.width;

    mur_t* res = malloc((2*w*h-w-h)*sizeof(mur_t));

    int indice_courant = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i != h-1) {
                res[indice_courant].i1 = i;
                res[indice_courant].j1 = j;
                res[indice_courant].i2 = i+1;
                res[indice_courant].j2 = j;
                indice_courant++;
            }

            if (j != w-1) {
                res[indice_courant].i1 = i;
                res[indice_courant].j1 = j;
                res[indice_courant].i2 = i;
                res[indice_courant].j2 = j+1;
                indice_courant++;
            }
        }
    }
    assert(indice_courant == 2*w*h-w-h);

    return res;
}


/* Mélange la liste de murs `murs`, pour un labyrinthe de même taille que laby,
 * au moyen de l’algorithme de Fisher-Yates */
void melange_liste_murs(mur_t* murs, laby_t laby) {
    int h = laby.height;
    int w = laby.width;
    int j;
    mur_t temp;
    for (int i = 2*w*h-w-h-1; i > 0; i--) {
        j = rand()%(i+1);
        temp = murs[j];
        murs[j] = murs[i];
        murs[i] = temp;
    }
}

/* Idem que generate_laby, avec des union-find */
void generate_laby_q5(laby_t laby) {
    int h = laby.height;
    int w = laby.width;

    mur_t* murs = tab_murs_laby_plein(laby);
    melange_liste_murs(murs, laby);
    uf_partition_t p = uf_initialize(w*h);

    int mur_counter = 0;
    int mur_idx = 0;
    while (mur_counter < w*h-1) {
        /* on vérifie si le mur courant coupe deux cases de la même classe ou
         * non */
        uf_elem_t cell1 =
            p[linearise(laby, murs[mur_idx].i1, murs[mur_idx].j1)];
        uf_elem_t cell2 =
            p[linearise(laby, murs[mur_idx].i2, murs[mur_idx].j2)];
        if (uf_find_no(cell1)->elem != uf_find_no(cell2)->elem) {
            casse_mur(laby, murs[mur_idx].i1, murs[mur_idx].j1,
                            murs[mur_idx].i2, murs[mur_idx].j2);
            uf_union(cell1, cell2);
            mur_counter++;
        }
        mur_idx++;
    }
    uf_free(p, w*h);
    free(murs);
}


/* Résoud récursivement le labyrinthe laby à partir de la case (i, j) sachant
 * le tableau des cases déjà visitées chemin. Renvoie true si une solution
 * a été trouvée, false sinon. */
bool rec_solver(laby_t laby, bool* chemin, int i, int j) {
    int w = laby.width;
    int h = laby.height;

    if (!is_in_laby(laby, i, j)) {
        return false;
    } else if (i == h-1 && j == w-1) {
        chemin[linearise(laby, i, j)] = true;
        return true;
    } else if (chemin[linearise(laby, i, j)]) {
        return false;
    } else {
        chemin[linearise(laby, i, j)] = true;
        if (
            (is_in_laby(laby, i-1, j) &&
               can_go_from(laby, i, j, i-1, j) &&
               rec_solver(laby, chemin, i-1, j)) ||
            (is_in_laby(laby, i, j-1) &&
               can_go_from(laby, i, j, i, j-1) &&
               rec_solver(laby, chemin, i, j-1)) ||
            (is_in_laby(laby, i+1, j) &&
               can_go_from(laby, i, j, i+1, j) &&
               rec_solver(laby, chemin, i+1, j)) ||
            (is_in_laby(laby, i, j+1) &&
               can_go_from(laby, i, j, i, j+1) &&
               rec_solver(laby, chemin, i, j+1))
        ) {
            return true;
        } else {
            chemin[linearise(laby, i, j)] = false;
            return false;
        }
    }
}

/* Résoud le labyrinthe laby en renvoyant les cases visitées */
bool* solve_labyrinthe(laby_t laby) {
    bool* chemin = malloc(laby.width*laby.height*sizeof(bool));
    for (int i = 0; i < laby.width*laby.height; i++) {
        chemin[i] = false;
    }
    rec_solver(laby, chemin, 0, 0);
    return chemin;
}
