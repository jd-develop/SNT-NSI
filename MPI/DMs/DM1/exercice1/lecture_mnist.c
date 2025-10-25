#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lecture_mnist.h"

#define NBCOL 784


/* Code permettant l'import de la base de donnée MNIST */
int int_of_char(char c) {
  switch (c) {
  case '0': return 0;
  case '1': return 1;
  case '2': return 2;
  case '3': return 3;
  case '4': return 4;
  case '5': return 5;
  case '6': return 6;
  case '7': return 7;
  case '8': return 8;
  default:  return 9;
  }
}

unsigned char next_char(FILE* f) {
  unsigned char partial = 0;
  char c = fgetc(f);
  while (true) {
    if (c == ',' || c == '\n') {
      return partial;
    } else {
      partial = partial * 10 + int_of_char(c);
      c = fgetc(f);
    }
  }
}

void mnist_input(int n, database *p_db_train, int m, database *p_db_test) {
  // hyp : le fichier ./MNIST-txt/MNIST_train.txt est présent
  // crée une bd d'entrainement avec les n premières données du fichier
  // remplit * p_db_train avec cette base
  // crée une bd de test avec les m données suivantes du fichier
  // remplit * p_db_test avec cette base

  FILE *f = fopen("./MNIST-txt/MNIST_train.txt", "r");
  if (f == NULL) {
    printf("le fichier ./MNIST-txt/MNIST_train.txt n'a pas pu être ouvert\n");
  }
  database db_train = create_empty_database(n);
  database db_test = create_empty_database(m);
  int class;
  for (int j = 0; j < n; j++) {
    class = next_char(f);
    vector v = create_zero_vector(NBCOL);
    for (int i = 0; i < NBCOL; i++) {
      unsigned char c = next_char(f);
      v->content[i] = c;
    }
    (db_train->data)[j].vector = v;
    (db_train->data)[j].class = class;
  }
  for (int j = 0; j < m; j++) {
    class = next_char(f);
    vector v = create_zero_vector(NBCOL);
    for (int i = 0; i < NBCOL; i++) {
      unsigned char c = next_char(f);
      v->content[i] = c;
    }
    (db_test->data)[j].vector = v;
    (db_test->data)[j].class = class;
  }
  fclose(f);
  *p_db_test = db_test;
  *p_db_train = db_train;
  return;
}
