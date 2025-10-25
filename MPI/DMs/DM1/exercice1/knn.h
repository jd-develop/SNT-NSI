#ifndef KNN_H
#define KNN_H

#include "database.h"
#include "candidats.h"

extern int nb_class_max;

candidats pproche_list(database db, int k, vector input);

int classe_majoritaire(database db, candidats lc, int r);
int classify(database db, int k, vector input);

#endif
