#include <stdio.h>
#include <assert.h>

/*
 * Renvoie le nombre de 1 dans l’écriture binaire de n⩾0
 */
int f(int n) {
    assert(n >= 0);

    int r;
    int N = n;
    int accu = 0;
    while (N > 0) {
        r = N%2;
        N = N/2;
        if (r == 1) {
            accu ++;
        }
    }
    return accu;
}

/*
 * Calcule le maximum que peut prendre f entre k et n.
 * 0 ⩽ k ⩽ n
 */
int max_f(int k, int n) {
    assert(0 <= k);
    assert(k <= n);

    int max = 0;
    int f_i;
    for (int i = k; i <= n; i++) {
        f_i = f(i);
        if (f_i > max)
            max = f_i;
    }
    return max;
}

/*
 * Calcule la somme pour k allant de 1 à n des maximums de f entre k et n.
 * n ⩾ 0
 */
int somme_maximums(int n) {
    assert(n >= 0);

    int somme = 0;
    for (int k = 1; k <= n; k++) {
        somme += max_f(k, n)
    }
    return somme
}

int main() {
    // tests f
    assert(f(0) == 0);
    assert(f(1) == 1);
    assert(f(2) == 1);
    assert(f(3) == 2);
    assert(f(0x12) == 2);
    assert(f(0xF6) == 6);
    assert(f(0xFF) == 8);

    // tests max
    assert(max_f(4, 4) == 1);
    assert(max_f(4, 5) == 2);
    assert(max_f(4, 25) == 4);
    assert(max_f(16, 25) == 4);

    return 0;
}

