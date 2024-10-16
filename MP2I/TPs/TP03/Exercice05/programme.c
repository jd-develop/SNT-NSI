#include <stdio.h>
#include <assert.h>
#include <math.h>

/* incrémente l’entier pointé par p */
void incrementer(int* p) {
    assert(p != NULL);
    *p = *p + 1;
}

/* échange les flottants pointés par pa et pb */
void echange(float* pa, float* pb) {
    assert(pa != NULL);
    assert(pb != NULL);
    float c = *pa;
    *pa = *pb;
    *pb = c;
}

/*
 * Résout l’équation quadratique aX² + bX + c = 0
 * et renvoie le nombre de solutions réelles (0, 1, 2 ou -1 s’il y a une
 * infinité de solutions (si a=b=c=0))
 * Stocke également la ou les racines réelles dans les zones pointées par
 * x1 et x2.
 */
int quad_solve(float a, float b, float c, float* x1, float* x2) {
    assert(x1 != NULL);
    assert(x2 != NULL);
    if (a == 0) {
        // équation de degré 1
        if (b == 0) {
            // équation de degré 0
            if (c == 0)
                // 0=0 admet une infinité de solutions
                return -1;
            else
                // c=0 avec c≠0 n’admet pas de solutions
                return 0;
        }
        *x1 = -c/b;
        *x2 = -c/b;
        return 1;
    }
    // calcule le discriminant
    float delta = b*b - 4*a*c;
    if (-1e-3 <= delta && delta <= 1e-3) {
        // racine unique : -b/2a
        float racine = (-b)/(2*a);
        *x1 = racine;
        *x2 = racine;
        return 1;
    } else if (delta > 0) {
        // racine double : (-b±sqrt(Δ))/2a
        *x1 = (-b-sqrt(delta))/(2*a);
        *x2 = (-b+sqrt(delta))/(2*a);
        return 2;
    } else {
        // racines complexes
        return 0;
    }
}

int main() {
    int x = 3;
    printf("Avant : %d\n", x);
    incrementer(&x);
    printf("Après : %d\n", x);

    float a = 3.4;
    float b = 14.0;
    echange(&a, &b);
    // printf("%f, %f\n", a, b);
    assert(a == 14.0);
    assert(3.4 - 1e-3 <= b && b <= 3.4 + 1e-3);  // aaah, les flottants

    float x1;
    float x2;
    assert(quad_solve(2, 3, 4, &x1, &x2) == 0);

    assert(quad_solve(1, 0, 0, &x1, &x2) == 1);
    assert(x1 == x2 && x1 == 0);

    assert(quad_solve(0, 5, 4, &x1, &x2) == 1);
    printf("%f %f\n", x1, x2);
    assert(x1 == x2 && -0.8 - 1e-3 <= x1 && x1 <= -0.8 + 1e-3);

    assert(quad_solve(0, 0, 4, &x1, &x2) == 0);

    assert(quad_solve(0, 0, 0, &x1, &x2) == -1);

    assert(quad_solve(1, 0, -1, &x1, &x2) == 2);
    assert(x1 == -1 && x2 == 1);

    return 0;
}
