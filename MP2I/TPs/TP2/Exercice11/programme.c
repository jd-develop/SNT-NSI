#include <stdio.h>
#include <assert.h>
#include <time.h>

/* Calcule le terme suivant x dans la suite de Syracuse, avec x > 0 */
long int suivant(long int x) {
    assert(x > 0);
    if (x%2 == 0) {
        return x/2;
    } else {
        return 3*x + 1;
    }
}

/* Calcule le n-ième terme de la suite de Syracuse commençant par u₀ = x
 * x ⩾ 1 et n ⩾ 0
 */
long int syracuse(long int x, int n) {
    assert(x > 0);
    assert(n >= 0);
    long int terme_courant = x;
    for (int i = 0; i < n; i++) {
        terme_courant = suivant(terme_courant);
    }
    return terme_courant;
}

/* Calcule le temps de vol de x ⩾ 1 (le plus petit k∈N tel que u_k = 1) */
int temps_de_vol(long int x) {
    assert(x > 0);
    long int terme_courant = x;
    int temps_vol = 0;
    for (; terme_courant != 1; temps_vol++) {
        if (terme_courant%2 == 0) {
            terme_courant /= 2;
        } else {
            terme_courant = (3*terme_courant + 1)/2;
            temps_vol++;
        }
    }
    return temps_vol;
}

/* Calcule l’entier dans l’intervalle [[1, N]] ayant le plus long temps de
 * vol. N ⩾ 1
 */
int plus_long_vol(int n) {
    assert(n > 0);
    int plus_long = 0;
    int entier_plus_long = 1;
    int tps_vol;
    for (int i = 2; i <= n; i++) {
        tps_vol = temps_de_vol(i);
        if (tps_vol > plus_long) {
            plus_long = tps_vol;
            entier_plus_long = i;
        }
    }
    return entier_plus_long;
}

int main() {
    // printf("x = 5, n = 1 : %ld\n", syracuse(5, 1)); // normalement égal à 16
    printf("x = 9, n = 6 : %ld\n", syracuse(9, 6));
    printf("x = 77, n = 128 : %ld\n", syracuse(77, 128));
    printf("x = 1023, n = 729 : %ld\n", syracuse(1023, 729));
    printf("x = 12345567, n = 52397 : %ld\n", syracuse(1234567, 52397));
    printf("\n");

    printf("Temps de vol :\n");
    printf("x = 1 : %d\n", temps_de_vol(1));
    printf("x = 26 : %d\n", temps_de_vol(26));
    printf("x = 27 : %d\n", temps_de_vol(27));
    printf("x = 28 : %d\n", temps_de_vol(28));
    printf("x = 77030 : %d\n", temps_de_vol(77030));
    printf("x = 77031 : %d\n", temps_de_vol(77031));
    printf("\n");

    printf("Plus long temps de vol entre 1 et ... :\n");
    int time_start;
    for (int i = 1; i <= 10000000; i *= 10) {
        time_start = time(NULL);
        int plus_long_entier = plus_long_vol(i);
        int temps_vol_pour_cet_entier = temps_de_vol(plus_long_entier);
        printf(
            "%d : %d (temps de vol : %d, temps de calcul : %ds)\n",
            i,
            plus_long_entier,
            temps_vol_pour_cet_entier,
            time(NULL) - time_start
        );
    }
    return 0;
}

