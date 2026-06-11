#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <assert.h>
#include <string.h>

int BLOSUM[20][20] =
{{4, -1, -2, -2,  0, -1, -1,  0, -2, -1, -1, -1, -1, -2, -1,  1,  0, -3, -2,  0},
{-1,  5,  0, -2, -3,  1,  0, -2,  0, -3, -2,  2, -1, -3, -2, -1, -1, -3, -2, -3},
{-2,  0,  6,  1, -3,  0,  0,  0,  1, -3, -3,  0, -2, -3, -2,  1,  0, -4, -2, -3},
{-2, -2,  1,  6, -3,  0,  2, -1, -1, -3, -4, -1, -3, -3, -1,  0, -1, -4, -3, -3},
{ 0, -3, -3, -3,  9, -3, -4, -3, -3, -1, -1, -3, -1, -2, -3, -1, -1, -2, -2, -1},
{-1,  1,  0,  0, -3,  5,  2, -2,  0, -3, -2,  1,  0, -3, -1,  0, -1, -2, -1, -2},
{-1,  0,  0,  2, -4,  2,  5, -2,  0, -3, -3,  1, -2, -3, -1,  0, -1, -3, -2, -2},
{ 0, -2,  0, -1, -3, -2, -2,  6, -2, -4, -4, -2, -3, -3, -2,  0, -2, -2, -3, -3},
{-2,  0,  1, -1, -3,  0,  0, -2,  8, -3, -3, -1, -2, -1, -2, -1, -2, -2,  2, -3},
{-1, -3, -3, -3, -1, -3, -3, -4, -3,  4,  2, -3,  1,  0, -3, -2, -1, -3, -1,  3},
{-1, -2, -3, -4, -1, -2, -3, -4, -3,  2,  4, -2,  2,  0, -3, -2, -1, -2, -1,  1},
{-1,  2,  0, -1, -3,  1,  1, -2, -1, -3, -2,  5, -1, -3, -1,  0, -1, -3, -2, -2},
{-1, -1, -2, -3, -1,  0, -2, -3, -2,  1,  2, -1,  5,  0, -2, -1, -1, -1, -1,  1},
{-2, -3, -3, -3, -2, -3, -3, -3, -1,  0,  0, -3,  0,  6, -4, -2, -2,  1,  3, -1},
{-1, -2, -2, -1, -3, -1, -1, -2, -2, -3, -3, -1, -2, -4,  7, -1, -1, -4, -3, -2},
{ 1, -1,  1,  0, -1,  0,  0,  0, -1, -2, -2,  0, -1, -2, -1,  4,  1, -3, -2, -2},
{ 0, -1,  0, -1, -1, -1, -1, -2, -2, -1, -1, -1, -1, -2, -1,  1,  5, -2, -2,  0},
{-3, -3, -4, -4, -2, -2, -3, -2, -2, -3, -2, -3, -1,  1, -4, -3, -2, 11,  2, -3},
{-2, -2, -2, -3, -2, -1, -2, -3,  2, -1, -1, -2, -1,  3, -3, -2, -2,  2,  7, -1},
{ 0, -3, -3, -3, -1, -2, -2, -3, -3,  3,  1, -2,  1, -1, -2, -2,  0, -3, -1,  4}};

char A[20] = {'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L',
              'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V'};

int to_ind(char a) {
  for (int i=0; i<20; i++) {
    if (A[i] == a) {return i;}
  }
  return -1;
}

int blosum(char a, char b) {
  return BLOSUM[to_ind(a)][to_ind(b)];
}

int s(char* u, char* v) {
  assert(strlen(u) == strlen(v));
  int res = 0;
  int n = strlen(u);
  for (int i = 0; i < n; i++) {
    res += blosum(u[i], v[i]);
  }
  return res;
} 

int sf(char* u, char* v) {
  assert(strlen(u) == strlen(v));
  assert(strlen(u) != 0);

  int n = strlen(u);
  int max = s(u, v);
  int s;
  int s_max;
  for (int i = 0; i < n; i++) {
    s = blosum(u[i], v[i]);
    s_max = s;
    for (int j = i+1; j < n; j++) {
      s += blosum(u[j], v[j]);
      if (s > s_max) {
        s_max = s;
      }
    }
    if (s_max > max) {
      max = s_max;
    }
  }
  return max;
}

/* Renvoie le maximum entre a et b */
int max2(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

/* Renvoie le maximum entre a, b et c */
int max3(int a, int b, int c) {
  return max2(a, max2(b, c));
}

/* Comme sf2 mais sur les positions de l'intervalle [i, j] */
int sf2bis(char* u, char* v, int i, int j) {
  assert(i <= j);
  if (i == j) {
    return blosum(u[i], v[i]);
  } else if (i == j-1) {
    int sf_gauche = sf2bis(u, v, i, i);
    int sf_droite = sf2bis(u, v, j, j);
    int sf_tout = sf_gauche + sf_droite;
    return max3(sf_gauche, sf_droite, sf_tout);
  }

  int milieu = (i+j)/2;
  int sf_gauche = sf2bis(u, v, i, milieu-1);
  int sf_droite = sf2bis(u, v, milieu+1, j);

  int max_suffixes_gauche = 0;
  int s = 0;
  for (int k = milieu-1; k >= i; k--) {
    s += blosum(u[k], v[k]);
    if (s > max_suffixes_gauche) {
      max_suffixes_gauche = s;
    }
    // printf("  k=%d, s=%d, maxg=%d\n", k, s, max_suffixes_gauche);
  };

  int max_suffixes_droite = 0;
  s = 0;
  for (int k = milieu+1; k <= j; k++) {
    s += blosum(u[k], v[k]);
    if (s > max_suffixes_droite) {
      max_suffixes_droite = s;
    }
    // printf("  k=%d, s=%d, maxd=%d\n", k, s, max_suffixes_droite);
  };

  int b_milieu = blosum(u[milieu], v[milieu]);

  return max3(sf_gauche, sf_droite, max_suffixes_gauche + max_suffixes_droite + b_milieu);
}

int sf2(char* u, char* v) {
  assert(strlen(u) == strlen(v));
  assert(strlen(u) != 0);
  return sf2bis(u, v, 0, strlen(u)-1);
}

/* progdyn -> t[i] = meilleur suffixe connu entre [0, i]
   t[0] = b(u0, v0)
   t[i] = max(t[i-1]+b(ui, vi), b(ui, vi))
   puis on fait le max du tableau : c'est du O(n)
 */
int sf3(char* u, char* v) {
  assert(strlen(u) == strlen(v));
  assert(strlen(u) != 0);

  int n = strlen(u);

  int* t = malloc(n*sizeof(int));

  t[0] = blosum(u[0], v[0]);
  int max_courant = t[0];
  for (int i = 1; i < n; i++) {
    t[i] = max2(t[i-1], 0) + blosum(u[i], v[i]);
    if (t[i] > max_courant) {
      max_courant = t[i];
    }
  }

  free(t);
  return max_courant;
}


int main() {
  assert(s("ARN","ARD") == 10);

  assert(sf("ACATMLESACA", "KTKTMNESCSS") == 16);
  assert(sf("DESTRIER", "CENTRALE") == 16);
  assert(sf("AA", "DD") == -2);
  assert(sf("AAA", "DDD") == -2);

  assert(max3(1,2,3) == 3);
  assert(max3(3,2,1) == 3);
  assert(max3(1,3,2) == 3);

  assert(sf2("ACATMLESACA", "KTKTMNESCSS") == 16);
  assert(sf2("DESTRIER", "CENTRALE") == 16);
  assert(sf2("AA", "DD") == -2);
  assert(sf2("AAA", "DDD") == -2);

  assert(sf3("ACATMLESACA", "KTKTMNESCSS") == 16);
  assert(sf3("DESTRIER", "CENTRALE") == 16);
  assert(sf3("AA", "DD") == -2);
  assert(sf3("AAA", "DDD") == -2);

  return 0;
}
