#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "chain.h"

/* Déjà implémentée. */
char* to_string(chain* c) {
  char* s = malloc(c->len + 1);
  link* curr = c->head;
  for (int i = 0; i < c->len; i++) {
    s[i] = curr->val;
    curr = curr->next;
  }
  s[c->len] = '\0';
  return s;
}

/* Déjà implémentée. */
char get(chain* c, int i) {
  link* curr = c->head;
  for (int k = 0; k < i; k++) {
    curr = curr->next;
  }
  return curr->val;
}

int main(void) {

}
