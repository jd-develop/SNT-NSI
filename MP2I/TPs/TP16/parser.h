#ifndef PARSER_H
#define PARSER_H

#include "graphe.h"
#include <string.h>

/* Lit un graphe stocké dans le fichier filename, au format spécifié dans le TP */
graphe_t* lire_graphe(char* filename);

#endif
