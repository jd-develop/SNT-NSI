#ifndef UTILS_H
#define UTILS_H

/* structure pour stocker une chaîne de caractère
 * .len : taille de .string
 * .len_max : taille allouer pour .string
 * .string : chaîne de caractère
 */
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

/* Supprime les n derniers caractère de dest*/
void string_rm(String* dest, int n);

/* Libère dest */
void string_free(String* dest);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « au moins une des formules de l est vraie ».
 */
String* au_moins_une(String** l, int n);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « au plus une des formules de l est vraie ».
 */
String* au_plus_une(String** l, int n);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « exactement une des formules de l est
 * vraie ».
 */
String* exactement_une(String** l, int n);
#endif

