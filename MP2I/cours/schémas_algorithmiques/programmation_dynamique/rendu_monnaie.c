#include <stdio.h>
#include <stdlib.h>


unsigned int min(unsigned int a, unsigned int b) {
    if (a < b)
        return a;
    return b;
}


unsigned int rendu_monnaie(unsigned int* pieces, int n_pieces, unsigned int montant) {
    unsigned int** t = malloc((montant+1)*sizeof(unsigned int*));
    for (unsigned int x = 0; x <= montant; x++) {
        t[x] = malloc((n_pieces+1)*sizeof(unsigned int));
    }

    for (unsigned int x = 1; x <= montant; x++) {
        t[x][0] = -1;  // it will underflow, so it basically is +infty
    }
    for (int i = 0; i <= n_pieces; i++) {
        t[0][i] = 0;
    }

    for (int i = 1; i <= n_pieces; i++) {
        for (unsigned int x = 1; x <= montant; x++) {
            if (x >= pieces[i])
                t[x][i] = min(t[x][i-1], 1+t[x-pieces[i]][i]);
            else
                t[x][i] = t[x][i-1];
        }
    }

    unsigned int res = t[montant][n_pieces];

    for (unsigned int x = 1; x <= montant; x++) {
        free(t[x]);
    }
    free(t);

    return res;
}


int main() {
    unsigned int pieces[3] = {2, 3, 7};
    printf("%d\n", rendu_monnaie(pieces, 3, 13));
    return 0;
}
