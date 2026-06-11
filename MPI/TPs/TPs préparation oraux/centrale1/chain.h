#ifndef CHAIN_H
#define CHAIN_H

/* Maillons chaînés. */
struct link_s {
  char val;
  struct link_s* next;
};
typedef struct link_s link;

/* Type chaîne pour représenter une chaîne de caractères. */
struct chain_s {
  int len;
  link* head;
  link* last;
};
typedef struct chain_s chain;

/* `length(c)` renvoie la longueur de la chaîne de caractères
   représentée par la chaîne `c`. */
int length(chain* c);

/* `empty()` renvoie une nouvelle chaîne représentant une chaîne de
   caractères de longueur 0. */
chain* empty(void);

/* `free_chain(c)` libère la chaîne `c` ainsi que tous les maillons
   utilisés par cette chaîne et seulement ceux-là. */
 void free_chain(chain* c);

/* `to_string(c)` renvoie une chaîne de caractère correspondant à la
   chaîne de caractères représentée par la chaîne `c` */
char* to_string(chain* c);

/* `of_string s` renvoie une chaîne qui représente la chaîne de
   caractères `s` */
chain* of_string(char* s);

/* `cat(c1, c2)` est une nouvelle chaîne représentant la concaténation
   des chaînes de caractères représentées par `c1` et `c2` */
chain* cat(chain* c1, chain* c2);

/* `get(c, i)` est le caractère en indice `i` de la chaîne de
   caractères représentée par la chaîne `c`. On suppose que l'indice
   `i` est valable. */
char get(chain* c, int i);

/* `sub(c, pos, len)` est une nouvelle chaîne représentant la
   sous-chaîne de caractères commençant après la position `pos` de
   longueur `len` de la chaîne de caractères représentée par `c`. On
   suppose que `pos` et `len` désignent une sous-chaîne valide. */
chain* sub(chain* c, int pos, int len);

#endif
