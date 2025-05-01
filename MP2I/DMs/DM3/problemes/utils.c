#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

void safe_strcat(char** dest, const char* src){
	size_t size = strlen(src) + strlen(*dest) + 1;
	*dest = realloc(*dest, size*sizeof(char));
	if (*dest == NULL) {
		fprintf(stderr, "Erreur : impossible de réallouer la mémoire\n");
		exit(EXIT_FAILURE);
	}
	strcat(*dest, src);
}

char* au_moins_une(char** l, int n){
	char* f = strdup("(");
	for (int i = 0; i < n; i++){
		safe_strcat(&f, l[i]);
		if (i < n-1){
			safe_strcat(&f, " | ");
		}
	}
	safe_strcat(&f, ")");
	return f;
}

char* au_plus_une(char** l, int n){
	char* f = strdup("(");
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			safe_strcat(&f, "(~");
			safe_strcat(&f, l[i]);
			safe_strcat(&f, " | ~");
			safe_strcat(&f, l[j]);
			safe_strcat(&f, ")");
			if (i < n-2){
				safe_strcat(&f, " & ");
			}
		}
	}
	safe_strcat(&f, ")");
	return f;
}

char* exactement_une(char** l, int n){
	char* f = strdup("(");
	char* plus = au_plus_une(l, n);
	safe_strcat(&f, plus);
	free(plus);
	safe_strcat(&f, " & ");
	char* moins = au_moins_une(l, n);
	safe_strcat(&f, moins);
	free(moins);
	safe_strcat(&f, ")");
	return f;
}
