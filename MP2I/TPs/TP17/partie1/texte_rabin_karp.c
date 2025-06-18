#include <stdio.h>
#include <stdbool.h>

#include "texte.h"

#define B 256
#define q 5003371

/* renvoie x^n modulo k */
int exponentiation(int x, int n, int k) {
    int res = 1;
    for (int i = 0; i < n; i++) {
        res *= x;
        res %= k;
    }
    return res;
}

/* calcule le hash de la chaîne formée des p premières lettres de s */
int hash(char* s, int p) {
    int ht = 0;

    for (int j = 0; j < p; j++) {
        ht = (B*ht + s[j]) % q;
    }
    return ht;
}

/* Calcule n modulo k */
int vrai_modulo(int n, int k) {
    return ((n%k) + k) % k;
}


/* si compte = true, c’est recherche_compte, sinon c’est recherche */
int _recherche(char* t, char* m, int n, int p, bool compte) {
    int ht = hash(t, p);
    int hm = hash(m, p);
    int r = exponentiation(B, p, q);
    int total = 0;

    int i = 0;
    int j;
    while (i < n-p) {
        if (ht == hm) {
            j = 0;
            while (j<p && t[i+j] == m[j])
                j++;
            if (j == p) {
                if (compte)
                    total++;
                else
                    return i;
            } else {
                printf("Collision !\n");
            }
        }
        ht = vrai_modulo(B*ht - r*t[i] + t[i+p], q);
        i++;
    }
    if (compte)
        return total;
    else
        return -1;
}


int recherche(char* t, char* m, int n, int p) {
    return _recherche(t, m, n, p, false);
}


int recherche_compte(char* t, char* m, int n, int p) {
    return _recherche(t, m, n, p, true);
}

