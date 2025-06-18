#ifndef TEXTE_H
#define TEXTE_H

/* Renvoie l'indice de la première occurrence de m dans t.
 * n et p sont les longueurs respectives de t et m.
 * Renvoie -1 si m n'est pas un motif de t */
int recherche(char* t, char* m, int n, int p);

/* Renvoie le nombre d'occurrences de m dans t.
 * n et p sont les longueurs respectives de t et m. */
int recherche_compte(char* t, char* m, int n, int p);

#endif
