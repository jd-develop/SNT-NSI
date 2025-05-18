#ifndef UTILS_H
#define UTILS_H

/* structure pour stocker une chaîne de caractère
 * .len : taille de .string
 * .len_max : taille allouée pour .string
 * .string : chaîne de caractère
 */
/* Note : cette struct était utilisée dans la première version que nous avions
 * écrit de n_dames.c, mais on a finalement préféré utiliser des char* de taille
 * fixe déterminée en fonction des tailles des variables. Cette struct est
 * tout de même toujours utilisée dans maisons.c */
typedef struct {
    int len;
    int len_max;
    char* string;
} String;


/* Crée un nouveau string */
String* new_string();

/* Ajoute src dans dest */
void string_append(String* dest, const char* src);

/* Ajoute src dans dest puis libère src */
void string_cat(String* dest, String* src);

/* Supprime les n derniers caractères de dest*/
void string_rm(String* dest, int n);

/* Libère dest */
void string_free(String* dest);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « au moins une des formules de l est vraie ».
 */
String* au_moins_une(String** l, int n);
char* au_moins_une_charetoile(char** l, int n);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « au plus une des formules de l est vraie ».
 */
String* au_plus_une(String** l, int n);
char* au_plus_une_charetoile(char** l, int n);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « exactement une des formules de l est
 * vraie ».
 */
String* exactement_une(String** l, int n);

// Copie s dans f à partir de la case k et incrémente k.
void write_f(char* f, char* s, int* k);

/* Renvoie le nombre de chiffres dans n */
int digits_number(int n);

/* Renvoie le minimum de a et b*/
int min(int a, int b);

#endif

