#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <pthread.h> // penser à compiler avec -pthread

#include <sys/resource.h>

struct matrice_s {
    int nbl;  //nombre de lignes
    int nbc;  //nombre de colonnes
    int** tab;//tableau de nbl tableaux de nbc coeffs
};

typedef struct matrice_s* matrice;


matrice create(int n,int m){
  //cree une matrice à n lignes et m colonnes, "vide"
  matrice res = malloc(sizeof(struct matrice_s));
  res->nbl = n;
  res->nbc = m;
  res->tab = malloc(sizeof(int*)*n);
  for(int i=0; i<n ; i++){
    res->tab[i] = malloc(sizeof(int)*m);
  }
  return res;
}


void libere_matrice(matrice m){
    for(int i=0; i < m->nbl; i++){
        free(m->tab[i]);
    }
    free(m->tab);
    free(m);
}


void affiche_matrice (matrice m){
    for(int j=0; j < m->nbc; j++){printf("------");};
    printf("-\n");
    for(int i=0; i < m->nbl; i++){
        for(int j=0; j < m->nbc; j++){
            printf("%d\t", m->tab[i][j]);
        }
        printf("\n");
    }
    for(int j=0; j < m->nbc; j++){printf("------");};
    printf("-\n");
}


/* Calcule et renvoie le produit de la matrice m1 et de la matrice m2 */
matrice produit (matrice m1, matrice m2) {
    assert(m1->nbc == m2->nbl);
    matrice res = create(m1->nbl, m2->nbc);
    for (int i = 0; i < m1->nbl; i++) {
        for (int j = 0; j < m2->nbc; j++) {
            int sum = 0;
            for (int k = 0; k < m1->nbc; k++) {
                sum += m1->tab[i][k] * m2->tab[k][j];
            }
            res->tab[i][j] = sum;
        }
    }
    return res;
}

/* Q2: on peut paralléliser chaque case (i, j) de la matrice résultat. Il n'y
 * a pas de section critique, on peut donc se passer de verrous */

struct aggregation_s {
    matrice m1;
    matrice m2;
    matrice res;
    int i;
    int j;
};

typedef struct aggregation_s* aggregation;


/* Effectue le calcul de la case d'indices (args_voidp->i, args_voidp->j), où
 * args_voidp est en réalité de type aggregation */
void* produit_1_case (void* args_voidp) {
   aggregation args = (aggregation) args_voidp;
   int sum = 0;
   for (int k = 0; k < args->m1->nbc; k++) {
       sum += args->m1->tab[args->i][k] * args->m2->tab[k][args->j];
   }
   args->res->tab[args->i][args->j] = sum;
   //printf("fini ! i=%d, j=%d, résultat : %d\n", args->i, args->j, sum);
   return NULL; 
}

matrice produit_parallele(matrice m1, matrice m2) {
    assert(m1->nbc == m2->nbl);
    matrice res = create(m1->nbl, m2->nbc);

    aggregation** cases = malloc(m1->nbl*sizeof(aggregation*));
    pthread_t** threads = malloc(m1->nbl*sizeof(pthread_t*));

    for (int i = 0; i < m1->nbl; i++) {
        cases[i] = malloc(m2->nbc * sizeof(aggregation));
        threads[i] = malloc(m2->nbc * sizeof(pthread_t));
        for (int j = 0; j < m2->nbc; j++) {
            cases[i][j] = malloc(sizeof(struct aggregation_s));
            cases[i][j]->m1 = m1;
            cases[i][j]->m2 = m2;
            cases[i][j]->res = res;
            cases[i][j]->i = i;
            cases[i][j]->j = j;
            pthread_create(&(threads[i][j]), NULL, produit_1_case, cases[i][j]);
        }
    }

    for (int i = 0; i < m1->nbl; i++) {
        for (int j = 0; j < m2->nbc; j++) {
            pthread_join(threads[i][j], NULL);
            free(cases[i][j]);
        }
        free(cases[i]);
        free(threads[i]);
    }

    free(cases);
    free(threads);
    return res;
}

bool mat_egales (matrice m1, matrice m2) {
    if (m1->nbc != m2->nbc || m1->nbl != m2->nbl)
        return false;
    bool res = true;
    for (int i = 0; i < m1->nbl && res; i++) {
        for (int j = 0; j < m1->nbc && res; j++) {
            res = (m1->tab[i][j] == m2->tab[i][j]);
        }
    }
    return res;
}

void test_lots_of_matrices() {
    int nbc = 100;
    int nbl = 100;
    matrice m1 = create(nbl, nbc);
    matrice m2 = create(nbl, nbc);
    matrice prod_seq;
    matrice prod_par;

    for (int k = 0; k < 100; k++) {
        for (int i = 0; i < nbl; i++) {
            for (int j = 0; j < nbc; j++) {
                m1->tab[i][j] = rand()%200 - 100;
                m2->tab[i][j] = rand()%200 - 100;
            }
        }
        prod_seq = produit(m1, m2);
        prod_par = produit_parallele(m1, m2);
        assert(mat_egales(prod_seq, prod_par));
        libere_matrice(prod_seq);
        libere_matrice(prod_par);
    }
    libere_matrice(m1);
    libere_matrice(m2);
}

int main() {
    struct rlimit res;
    getrlimit(RLIMIT_NPROC, &res);
    printf("%d %d\n", res.rlim_cur, res.rlim_max);

    srand(time(NULL));

    matrice m1 = create(2,3);
    m1->tab[0][0] = 1 ;
    m1->tab[0][1] = 8 ;
    m1->tab[0][2] = 3 ;
    m1->tab[1][0] = 1 ;
    m1->tab[1][1] = 2 ;
    m1->tab[1][2] = 1 ;
    affiche_matrice(m1);

    matrice m2 = create(3,4);
    m2->tab[0][0] = 1 ;
    m2->tab[0][1] = 8 ;
    m2->tab[0][2] = 3 ;
    m2->tab[0][3] = 0 ;
    m2->tab[1][0] = 1 ;
    m2->tab[1][1] = 2 ;
    m2->tab[1][2] = 1 ;
    m2->tab[1][3] = 0 ;
    m2->tab[2][0] = 1 ;
    m2->tab[2][1] = 2 ;
    m2->tab[2][2] = 1 ;
    m2->tab[2][3] = 0 ;
    affiche_matrice(m2);

    matrice prod = produit(m1,m2);
    affiche_matrice(prod);
    matrice prod1 = produit_parallele(m1,m2);
    affiche_matrice(prod1);

    libere_matrice(m1);
    libere_matrice(m2);
    libere_matrice(prod);
    libere_matrice(prod1);

    test_lots_of_matrices();
    printf("Eh ! Ça marche !\n");

    return 0;
}
