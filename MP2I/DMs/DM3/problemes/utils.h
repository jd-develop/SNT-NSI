#ifndef UTILS_H
#define UTILS_H

/*
 * Si l est une liste de n formules supposées atomiques (i.e. sans opérateurs
 * binaires en-dehors de parenthèses), renvoie une chaîne (dans le tas)
 * contenant une formule exprimant « au moins une des formules de l est vraie ».
 * Par exemple, au_moins_une(["(x & ~y)", "y", "z"], 3) pointe vers la chaîne
 * "((x & ~y) | y | z)"
 */
char* au_moins_une(char** l, int n);

#endif
