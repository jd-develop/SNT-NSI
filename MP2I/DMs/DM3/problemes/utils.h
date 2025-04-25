#ifndef UTILS_H
#define UTILS_H

/*
 * Renvoie la concaténation des chaînes de l (tableau de taille n) avec pour
 * séparateur la chaîne s, avec une parenthèse ouvrante et une parenthèse
 * fermante comme premier et dernier caractères.
 * Si j est compris entre 0 inclus et n exclus, toutes les chaînes sont
 * précédées de "~" sauf la chaîne d’indice j
 * Si j est égal à n, toutes les chaînes sont précédées de "~"
 */
char* join(char** l, int n, char* s, int j);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « au moins une des formules de l est vraie ».
 * Par exemple, au_moins_une(["(x & ~y)", "y", "z"], 3) pointe vers la chaîne
 * "((x & ~y) | y | z)"
 */
char* au_moins_une(char** l, int n);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « toutes les formules de l sont vraies ».
 * Par exemple, toutes(["(x & ~y)", "y", "z"], 3, -1) pointe vers la chaîne
 * "((x & ~y) & y & z)"
 *
 * Si j est compris entre 0 inclus et n exclus, la fomule représentée
 * par la chaîne de retour est « aucune formule n’est vraie sauf celle à
 * l’indice j ».
 * Par exemple, toutes(["(x & ~y)", "y", "z"], 3, 1) pointe vers la chaîne
 * "(~(x & ~y) & y & ~z)"
 *
 * Si j est égal à n, la formule représentée par la chaîne de retour est
 * « aucune formule n’est vraie ».
 * Par exemple, toutes(["(x & ~y)", "y", "z"], 3, 3) pointe vers la chaîne
 * "(~(x & ~y) & ~y & ~z)"
 */
char* toutes(char** l, int n, int j);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « au plus une des formules de l est vraie ».
 * Par exemple, au_plus_une(["(x & ~y)", "y", "z"], 3) pointe vers la chaîne
 * "(((x & ~y) & ~y & ~z) | (~(x & ~y) & y & ~z) | (~(x & ~y) & ~y & z)
 *  | (~(x & ~y) & ~y & ~z))"
 */
char* au_plus_une(char** l, int n);

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « exactement une des formules de l est
 * vraie ».
 * Par exemple, exactement_une(["(x & ~y)", "y", "z"], 3) pointe vers la chaîne
 * "(((x & ~y) & ~y & ~z) | (~(x & ~y) & y & ~z) | (~(x & ~y) & ~y & z))"
 */
char* exactement_une(char** l, int n);

/*
 * Affiche la chaîne de caractères s (dans le tas) puis libère la mémoire qui
 * lui est allouée
 */
void printfree(char* s);

#endif
