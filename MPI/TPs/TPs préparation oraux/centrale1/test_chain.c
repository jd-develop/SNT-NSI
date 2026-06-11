#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "chain.h"

/* `read(file_name, nb_lines)` lit les `nb_lines` premières lignes
   d'un fichier (si elles existent) dans une chaîne. */
chain* read(char* file_name, int nb_lines) {
  chain* text = empty();
  FILE* fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "File %s not found.\n", file_name);
    exit(1);
  }
  char* line = NULL;
  size_t len = 0;
  while (nb_lines-- > 0 && (getline(&line, &len, fp)) > 0) {
    chain *ch_line = of_string(line);
    chain *new_text = cat(text, ch_line);
    free(text);
    free(ch_line);
    text = new_text;
  }
  free(line);
  fclose(fp);
  return text;
}

int main(void) {

}
