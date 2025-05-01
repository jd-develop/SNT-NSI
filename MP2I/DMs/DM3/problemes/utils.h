/* Même fonction que strcat mais avec un realloc,
   strcat(dest, src); -> safe_strcat(&dest, src); */
void safe_strcat(char** dest, const char* src);

/* Renvoie la formule au moins une est vraie */
char* au_moins_une(char** l, int n);

/* Renvoie la formule au plus une est vraie */
char* au_plus_une(char** l, int n);

/* Renvoie la formule exactement une est vraie */
char* exactement_une(char** l, int n);
