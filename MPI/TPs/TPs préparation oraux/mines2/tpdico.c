#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct dict0 {
  char* mot;
  char* phonetique;
  struct dict0* suivant;
};

void free_dict(struct dict0 * dict) {
  struct dict0 * courant = dict;
  if (dict != NULL) {
    struct dict0 * suiv = dict->suivant;
    while (suiv != NULL) {
      free(courant->mot);
      free(courant->phonetique);
      free(courant);
      courant = suiv;
      suiv = suiv->suivant;
    }
    free(courant->mot);
    free(courant->phonetique);
    free(courant);
  }
}

/* Ouvre le fichier et l'écrit dans un dictionnaire qui est renvoyé */
struct dict0 * read_file(char* filename) {
  // ouverture du fichier
  FILE* fp = fopen(filename, "r+");
  if (fp == NULL) {
    return NULL;
  }

  // initialisation de la structure
  struct dict0 * res = malloc(sizeof(struct dict0));
  res->suivant = NULL;
  struct dict0 * courant = res;
  struct dict0 * prec = NULL;

  // tant qu'on peut lire
  while (true) {
    courant->mot = NULL;
    courant->phonetique = NULL;

    size_t zero = 0;

    // on lit la ligne
    ssize_t l1 = getdelim(&(courant->mot), &zero, ',', fp);
    if (l1 == -1) {  // EOF : on arrête le while
      free(courant->mot);
      free(courant);
      if (prec != NULL) {
        prec->suivant=NULL;
      }
      break;  // while (true)
    }
    ssize_t l2 = getline(&(courant->phonetique), &zero, fp);
    // suppression de ',' et '\n'
    courant->mot[l1-1] = '\0';
    courant->phonetique[l2-1] = '\0';

    prec = courant;
    courant->suivant = malloc(sizeof(struct dict0));

    courant = courant->suivant;
    courant->suivant = NULL;
  }

  fclose(fp);

  return res;
}


/**** partie 2 ****/

typedef struct {
  char* mot;
  char* phonetique;
} couple;

typedef struct {
  int taille;  // taille du tableau (y compris les cases vides)
  int indice_actuel;  // premier indice d'une case VIDE
  couple* tableau; 
} tas_min;

/* Créée et renvoie un tas vide */
tas_min* creer_tas() {
  tas_min* res = malloc(sizeof(tas_min));
  res->taille = 8;
  res->indice_actuel = 0;
  res->tableau = malloc(8*sizeof(couple));
  return res;
}

/* Renvoie l'indice de l'enfant gauche de la case d'indice `indice` */
int tas_enfant_gauche(int indice) { return 2*indice+1; }
/* Renvoie l'indice de l'enfant droit de la case d'indice `indice` */
int tas_enfant_droit(int indice) { return 2*indice+2; }

/* Renvoie l'indice du parent de la case d'indice `indice` */
int tas_parent(int indice) { return (indice-1)/2; }

/* Insère l'élément `elem` dans le tas `tas` au bon endroit (en le faisant remonter
 * si nécessaire */ 
void insere_tas(tas_min* tas, couple elem) {
  // tableau trop petit : on le realloc
  if (tas->indice_actuel == tas->taille) {
    tas->tableau = realloc(tas->tableau, 2 * tas->taille * sizeof(couple));
    tas->taille *= 2;
  }

  // on met l'élément dans la case actuelle
  tas->tableau[tas->indice_actuel] = elem;

  // on fait remonter s'il faut le faire remonter
  int i = tas->indice_actuel++;
  while(i != 0 && strcmp(tas->tableau[i].mot, tas->tableau[tas_parent(i)].mot) < 0) {
    tas->tableau[i] = tas->tableau[tas_parent(i)];
    tas->tableau[tas_parent(i)] = elem;
    i = tas_parent(i);
  }
}

/* Extrait le min du tas `tas` et le renvoie. Précondition : le tas est non vide */
couple extraire_min (tas_min* tas) {
  couple res = tas->tableau[0];

  tas->tableau[0] = tas->tableau[tas->indice_actuel--];
  
  int i = 0;
  // initialisation de quelques valeurs
  couple temp;
  int g; int d;
  bool gauche_min;

  while (i < tas->indice_actuel) {
    g = tas_enfant_gauche(i);
    d = tas_enfant_droit(i);

    // je suis plus grand que mon enfant gauche
    if (strcmp(tas->tableau[i].mot, tas->tableau[g].mot) > 0) {
      // je suis aussi plus grand que mon enfant droit
      if (strcmp(tas->tableau[i].mot, tas->tableau[d].mot) > 0) {
        // je choisis le min entre l'enfant gauche et l'enfant droit
        gauche_min = strcmp(tas->tableau[g].mot, tas->tableau[d].mot) < 0;
        if (gauche_min) {
          // je m'échange avec mon enfant gauche
          temp = tas->tableau[i];
          tas->tableau[i] = tas->tableau[g];
          tas->tableau[g] = temp;
          i = g;
        } else {
          // je m'échange avec mon enfant droit
          temp = tas->tableau[i];
          tas->tableau[i] = tas->tableau[d];
          tas->tableau[d] = temp;
          i = d;
        }
      } else {
        // je suis seulement plus grand que mon enfant gauche
        temp = tas->tableau[i];
        tas->tableau[i] = tas->tableau[g];
        tas->tableau[g] = temp;
        i = g;
      }
    } else if (strcmp(tas->tableau[i].mot, tas->tableau[d].mot) > 0) {
      // je suis plus grand que mon enfant droit, mais pas de mon enfant gauche
      temp = tas->tableau[i];
      tas->tableau[i] = tas->tableau[d];
      tas->tableau[d] = temp;
      i = d;
    } else {
      // je suis déjà le min de mes deux enfants
      break; // while (i < tas->indice_actuel)
    }
  } 

  return res;
}

//struct dict0* tri_par_tas(struct dict0* 

int main() {
  struct dict0 * dict = read_file("data/mini_lexique383.csv");

  for (struct dict0 * courant = dict; courant != NULL; courant = courant->suivant) {
    printf("%s : %s\n", courant->mot, courant->phonetique);
  }
  
  free_dict(dict); 

  return 0;
}
