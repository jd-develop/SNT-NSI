
// Copie s dans f à partir de la case k et incrémente k.
char* write_f(char* f, char* s, int* k);

/* Renvoie la disjonction des n formules atomiques que contient l*/
char* au_moins_une(char** l, int n);

/* Renvoie une formule atomique qui est vrai ssi au plus une des n formule atomique de l est vrai*/
char* au_plus_une(char** l, int n);

// Renvoie le minimum de a et b
int min(int a, int b);
