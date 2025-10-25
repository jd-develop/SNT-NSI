#ifndef LECTURE_MNIST_H
#define LECTURE_MNIST_H

#include "database.h"


/* Code permettant l'import de la base de données MNIST */
int int_of_char(char c);
unsigned char next_char(FILE* f);
void mnist_input(int n, database *p_db_train, int m, database *p_db_test);

#endif
