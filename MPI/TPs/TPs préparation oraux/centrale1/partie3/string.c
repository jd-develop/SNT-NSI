#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/* On suppose toujours que le pointeur `s` en paramètre correspond à
   une chaîne de caractère correctement allouée et initialisée. */

/* `length(s)` renvoie la longueur de la chaîne de caractères `s`. */
int length(char* s) {
  int i;
  for (i = 0; s[i] != '\0'; i++) {}
  return i;
}

void test_length () {
  assert (length("") == 0);
  assert (length("a") == 1);
  assert (length("abcd") == 4);
  printf("OK length\n");
}

/* `empty()` renvoie une nouvelle chaîne de caractères de longueur 0. */
char* empty(void) {
  char* res = malloc(1*sizeof(char));
  res[0] = '\0';
  return res;
}

void test_empty () {
  char* e = empty();
  assert(length(e) == 0);
  free(e);
  printf("OK empty\n");
}

/* `make(n, x)` renvoie une nouvelle chaîne de caractères constituée de
   `n` fois le caractère `x`. On suppose `n >= 0`. */
char* make(int n, char x) {
  assert(n >= 0);
  char* res = malloc((n+1)*sizeof(char));
  for (int i = 0; i < n; i++) {
    res[i] = x;
  }
  res[n] = 0;
  return res;
}

void test_make () {
  char* a = make(10, 'x');
  assert(length(a) == 10);
  for (int i = 0; i < 10; i++) {
    assert (a[i] == 'x');
  }
  free(a);
  char* b = make(0, 'b');
  assert(length(b) == 0);
  free(b);
  printf("OK make\n");
}

/* `get(s, i)` est le caractère en indice `i` de la chaîne de
   caractères `s`. On suppose que l'indice `i` est valable. */
char get(char* s, int i) {
  /* En O(1) (on regarde à l'emplacement mémoire s+i)
   * Pour vérifier que l'indice est valable, il faudrait connaître la longueur de s,
   * ce qui s'effectue en O(n) */
  return s[i];
}

void test_get() {
  char* a = "0123456789";
  for (int i = 0; i < 10; i++) {
    assert (get(a, i) == 0x30+i);
  }
  printf("OK get\n");
}

/* `cat(s1, s2)` est une nouvelle chaîne de caractères constituée de
   la concaténation des chaînes de caractères `s1` et `s2` */
char* cat(char* s1, char* s2) {
  /* Complexité temporelle : O(n+m)
   * Complexité spatiale : O(n+m) */
  int n = length(s1);
  int m = length(s2);
  char* res = malloc((n+m+1)*sizeof(char));
  for (int i = 0; i < n; i++) {
    res[i] = s1[i];
  }
  for (int j = 0; j < m; j++) {
    res[n+j] = s2[j];
  }
  res[n+m] = '\0';
  return res;
}

void test_cat() {
  char* a = "to";
  char* b = "ta";
  char* ab = cat(a, b);
  assert (ab[0] == 't');
  assert (ab[1] == 'o');
  assert (ab[2] == 't');
  assert (ab[3] == 'a');
  free(ab);
  printf("OK cat\n");
}

/* `sub(s, pos, len)` est une nouvelle chaîne de caractères consituée
   de la sous-chaîne de caractères commençant après la position `pos`
   de longueur `len`. On suppose que `pos` et `len` désignent une
   sous-chaîne valide. */
char* sub(char* s, int pos, int len) {
  char* res = malloc((len+1)*sizeof(char));
  for (int i = 0; i < len; i++) {
    res[i] = s[pos+i];
  }
  res[len] = '\0';
  return res;
}

void test_sub() {
  char* a = "toto";
  char* s = sub(a, 2, 2);
  assert (length(s) == 2);
  assert (s[0] == 't');
  assert (s[1] == 'o');
  free(s);
  printf("OK sub\n");
}


/* `read(file_name, nb_lines)` lit les `nb_lines` premières lignes
   d'un fichier (si elles existent) dans une chaîne de caractère. */
char* read(char* file_name, int nb_lines) {
  char* text = empty();
  FILE* fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "File %s not found.\n", file_name);
    exit(1);
  }
  char* line = NULL;
  size_t len = 0;
  while (nb_lines-- > 0 && (getline(&line, &len, fp)) > 0) {
    char* next = cat(text, line);
    free(text);
    text = next;
  }
  free(line);
  fclose(fp);
  return text;
}

int main(void) {
  // /*
  test_length();
  test_empty();
  test_make();
  test_get();
  test_cat();
  test_sub();
  // */

  /* Question 8 */
  char* dix_premieres_lignes = read("../europarl.txt", 10);
  printf("=== 10 premières lignes ===\n%s======\n", dix_premieres_lignes);
  char* sous_chaine = sub(dix_premieres_lignes, 475, 56);
  printf("=== sous-chaîne ===\n%s\n======\n", sous_chaine);

  free(sous_chaine);
  free(dix_premieres_lignes);

  // char* dix_mille_lignes = read("../europarl.txt", 10000);
  // free(dix_mille_lignes);

  return 0;
}
