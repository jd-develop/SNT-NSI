#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************
 *  Définition des constantes   *
 ********************************/
#define K 4       /* Le nombre de classes      */
#define H 1049    /* Paramètre pour le hachage */
#define B 991     /* Paramètre pour le hachage */


/********************************
 *     Définition des types     *
 ********************************/
/* Type des arbres de décision */
struct darbre_noeud_s {
  int classe;                   /* la classe ou -1 si nœud interne */
  int i;                        /* la coordonnée de disjonction */
  struct darbre_noeud_s *faux;  /* l'enfant gauche */
  struct darbre_noeud_s *vrai;  /* l'enfant droit */
};
typedef struct darbre_noeud_s *darbre;

/* Type des vecteurs de booléens */
struct bool_vec_s {
  bool* contenu;                /* un tableau de booléens */
  int   dim;                    /* la taille du tableau contenu */
};
typedef struct bool_vec_s bool_vec;

/* Type des données classifiées */
struct donnee_c_s {
  bool_vec donnee;              /* la donnée */
  int      classe;              /* sa classe */
};
typedef struct donnee_c_s* donnee_c;

/* Type des jeux de données classifiées */
struct jeu_donnees_c_s {
  donnee_c*   contenu;          /* un tableau de données classifiées */
  int         taille;           /* sa taille */
};
typedef struct jeu_donnees_c_s jeu_donnees_c;
/* Hyp : les données sont toutes de même dimension. */

/* Type des listes d'arbres de décision */
struct darbre_list_s {
  darbre                elem ;  /* L'élément dans la cellule */
  struct darbre_list_s* next ;  /* Le suivant */
};
typedef struct darbre_list_s* darbre_list;

/* Type des ensembles d'arbres de décision */
typedef darbre_list ensemble_darbres[H];

/********************************
 *     Quelques prototypes      *
 ********************************/

darbre cree_feuille(int classe);
darbre cree_noeud(int i, darbre faux, darbre vrai);

/********************************
 *    Fonctions d'affichage     *
 ********************************/

void affiche_arbre_aux(darbre da, char *prefixe, int l, int lrn) {
  /* Fonction auxiliaire récursive pour l'affichage d'un arbre.
     Affiche le sous-arbre da, qui est :
     + la racine si lrn == 2
     + un fils gauche si lrn == 0
     + un fils droit si lrn == 1.
     Chaque ligne d'affichage est précédée du préfixe prefixe de longueur
     l.
  */
  if (da->classe >= 0) {
    if (lrn == 0) { /* fils gauche */
      printf("%s├─ : %d\n", prefixe, da->classe);
    } else if (lrn == 1) { /* fils droit */
      printf("%s└─ : %d\n", prefixe, da->classe);
    } else { /* racine */
      printf("%s%d\n", prefixe, da->classe);
    }
  } else {
    if (lrn == 0) { /* enfant gauche */
      printf("%s├─%d\n", prefixe, da->i);
    } else if (lrn == 1) { /* enfant droit */
      printf("%s└─%d\n", prefixe, da->i);
    } else { /* racine */
      printf("%s%d\n", prefixe, da->i);
    }
    int new_l = l;  /* racine */
    if (lrn == 0) { /* enfant gauche */
      strcat(prefixe, "│ ");
      new_l = l + 4;
    } else if (lrn == 1) { /* enfant droit */
      strcat(prefixe, "  ");
      new_l = l + 2;
    }
    affiche_arbre_aux(da->faux, prefixe, new_l, 0);
    affiche_arbre_aux(da->vrai, prefixe, new_l, 1);
    prefixe[l] = '\0';
  }
}

void affiche_arbre(darbre da) {
  /* Affiche l'arbre da */
  char prefixe[101];
  prefixe[0] = '\0';
  affiche_arbre_aux(da, prefixe, 0, 2);
}

void affiche_bool(bool b) {
  /* Affiche le booléen b*/
  if (b) {printf("vrai"); }
  else {printf("faux"); }
}

void affiche_bool_vec(bool_vec bv) {
  /* Affiche le vecteur de booléens bv */
  if (bv.dim == 0) {
    printf("{}");
  } else {
    printf("{");
    for (int i = 0 ; i < bv.dim - 1; i ++) {
      affiche_bool(bv.contenu[i]);
      printf(", ");
    }
    affiche_bool(bv.contenu[bv.dim-1]);
    printf("}");
  }
}

void affiche_donnee_c(donnee_c d) {
  /* Affiche une donnée classifiée */
  affiche_bool_vec(d->donnee);
  printf(" ~> %d", d->classe);
}

void affiche_jeu_donnees_c(jeu_donnees_c jdc) {
  /* Affiche un jeu de données classifiées */
  printf("Je commence l'affichage : %d\n", jdc.taille);
  fflush(stdout);
  if (jdc.taille == 0) {
    printf("{}");
  } else {
    printf("{\n");
    for (int i = 0 ; i < jdc.taille-1; i ++) {
      printf("  ");
      affiche_donnee_c(jdc.contenu[i]);
      printf(",\n");
    }
    printf("  ");
    affiche_donnee_c(jdc.contenu[jdc.taille-1]);
    printf("\n}");
  }
}

void affiche_darbre_list(darbre_list dal) {
  /* Affiche une liste d'arbres */
  if (dal == NULL) {printf("[]");}
  else {
    printf("[\n");
    darbre_list cursor = dal;
    while (cursor->next != NULL) {
      affiche_arbre(cursor->elem);
      printf(",\n");
      cursor = cursor->next;
    }
    affiche_arbre(cursor->elem);
    printf("]\n");
  }

}

void affiche_ensemble_darbres(ensemble_darbres eda) {
  /* Affiche une table de hachage d'arbres */
  printf("====================\n");
  for (int i = 0 ; i < H ; i ++) {
    if (eda[i] != NULL) {
      printf("+++\nDe signature %d : \n", i);
      affiche_darbre_list(eda[i]);
    }
  }
  printf("====================\n");
}

/* NE PAS LIRE */
/* Un tableau dynamique d'arbres de décision */
struct tableau_dyn_s {
  int     taille;              /* La taille allouée du tableau contenu */
  int     remplissage;         /* Le nombre de cases de contenu utilisée */
  darbre* contenu;             /* Le tableau des arbres de décision */
};
typedef struct tableau_dyn_s* tableau_dyn;

tableau_dyn init() {
  /* Retourne un nouveau tableau dynamique vide. */
  tableau_dyn res = (tableau_dyn) malloc(sizeof(struct tableau_dyn_s));
  res->taille = 1;
  res->contenu = (darbre *)malloc(sizeof(darbre) * res->taille);
  res->contenu[0] = NULL;
  res->remplissage = 0;
  return res;
}

int trouve_arbre_meme_pointeur(tableau_dyn vus, darbre da) {
  /* Retourne -1 si da n'est pas dans le tableau dynamique vus ne contient
     pas le pointeur da. Retourne i si vus[i] = da. */
  for (int i = 0; i < vus->remplissage; i++) {
    if (vus->contenu[i] == da) {
      return i;
    }
  }
  return (-1);
}

void ajout(tableau_dyn vus, darbre da) {
  /* Ajoute l'arbre da au tableau dynamique vus. */
  if (vus->remplissage == vus->taille) {
    int n_taille = 2 * vus->taille;
    darbre *n_content = malloc(sizeof(darbre) * n_taille);
    for (int i = 0; i < vus->taille; i++) {
      n_content[i] = vus->contenu[i];
    }
    free(vus->contenu);
    vus->contenu = n_content;
    vus->taille = n_taille;
  }
  vus->contenu[vus->remplissage] = da;
  vus->remplissage++;
  return;
}

/* NE LIRE QUE POUR LA SECTION ... */
void affiche_arbre_d_aux(darbre da, tableau_dyn vu, char *prefixe, int l, int lrn) {
  /* Fonction auxiliaire récursive pour l'affichage d'un arbre, version debug.
     Affiche le sous-arbre da, qui est :
     + la racine si lrn == 2
     + un fils gauche si lrn == 0
     + un fils droit si lrn == 1.
     Chaque ligne d'affichage est précédée du préfixe prefixe de longueur l.
  */
  int i = trouve_arbre_meme_pointeur(vu, da) ;
  if (i >= 0) {
    if (lrn == 0) { /* fils gauche */
      printf("  \t%s├─ : (%d) ...\n", prefixe, i);
    } else if (lrn == 1) { /* fils droit */
      printf("  \t%s└─ : (%d) ...\n", prefixe, i);
    } else { /* racine */
      printf("  \t%s(%d) ...\n", prefixe, i);
    }
  } else {
    int i = vu->remplissage;
    ajout(vu, da);
    if (da->classe >= 0) {
      if (lrn == 0) { /* fils gauche */
        printf("(%d)\t%s├─ : %d\n", i, prefixe, da->classe);
      } else if (lrn == 1) { /* fils droit */
        printf("(%d)\t%s└─ : %d\n", i, prefixe, da->classe);
      } else { /* racine */
        printf("(%d)\t%s%d\n", i, prefixe, da->classe);
      }
    } else {
      if (lrn == 0) { /* fils gauche */
        printf("(%d)\t%s├─%d\n", i, prefixe, da->i);
      } else if (lrn == 1) { /* fils droit */
        printf("(%d)\t%s└─%d\n", i, prefixe, da->i);
      } else { /* racine */
        printf("(%d)\t%s%d\n", i, prefixe, da->i);
      }
      int new_l = l;  /* racine */
      if (lrn == 0) { /* fils gauche */
        strcat(prefixe, "│ ");
        new_l = l + 4;
      } else if (lrn == 1) { /* fils droit */
        strcat(prefixe, "  ");
        new_l = l + 2;
      }
      affiche_arbre_d_aux(da->faux, vu, prefixe, new_l, 0);
      affiche_arbre_d_aux(da->vrai, vu, prefixe, new_l, 1);
      prefixe[l] = '\0';
    }
  }

}

void affiche_arbre_d(darbre da) {
  /* Affiche l'arbre pointée par p_da pour le debug : les adresses de
     chaque zone mémoire sont affichées. */
  char prefixe[101];
  prefixe[0] = '\0';
  tableau_dyn vus = init();
  affiche_arbre_d_aux(da, vus, prefixe, 0, 2);
}


/********************************
 *       Arbres exemples        *
 ********************************/

darbre exemple_1() {
  /* Retourne l'arbre exemple de l'énoncé */
  return cree_noeud(1,
                    cree_noeud(0,
                               cree_feuille(0),
                               cree_feuille(0)),
                    cree_noeud(2,
                               cree_noeud(0,
                                          cree_feuille(1),
                                          cree_feuille(3)),
                               cree_noeud(0,
                                          cree_feuille(1),
                                          cree_feuille(3))));
}

darbre exemple_2_aux(int n, int p) {
  if (p == n - 1) {
    return cree_noeud(p, cree_feuille(0), cree_feuille(1));
  } else {
    return cree_noeud(p, exemple_2_aux(n, p + 1),
                      exemple_2_aux(n, p + 1));
  }
}
darbre exemple_2(int n) {
  /* Crée un arbre de décision dont chaque branche branche sur les
     variables x_0, x_1, ... x_(n-1), et tels que la classe est la valeur
     de x_(n-1) */
  return exemple_2_aux(n, 0);
}

darbre exemple_3_aux(int n, int p, bool b) {
  if (p == n) {
    return cree_feuille((int) b);
  } else {
    return cree_noeud(p, exemple_3_aux(n, p + 1, b),
                      exemple_3_aux(n, p + 1, b));
  }
}
darbre exemple_3(int n) {
  /* Crée un arbre de décision dont chaque branche branche sur les
     variables x_0, x_1, ... x_(n-1), et tels que la classe est la valeur
     de x_0 */
  return cree_noeud(0, exemple_3_aux(n, 1, false), exemple_3_aux(n, 1, true));
}

int evaluate(int n, int *path) {
  bool encore_possible = false;
  for (int i = 0; i < n; i++) {
    if (path[2 * i] == 1 && path[2 * i + 1] == 1) {
      return 1;
    } else if (path[2 * i] >= 1 && path[2 * i + 1] >= 1) {
      encore_possible = true;
    }
  }
  if (encore_possible) {
    return 2;
  } else {
    return 0;
  }
}

darbre exemple_4_aux(int p, int q, int *path) {
  int e = evaluate(p, path);
  if (e < 2) {
    return cree_feuille(e);
  } else {
    int nextq;
    if (q == 2 * (p - 1)) {
      nextq = 1;
    } else {
      nextq = q + 2;
    }
    path[q] = 0;
    darbre g = exemple_4_aux(p, nextq, path);
    path[q] = 1;
    darbre d = exemple_4_aux(p, nextq, path);
    path[q] = 2;
    return cree_noeud(q, g, d);
  }
}

darbre exemple_4(int p) {
  /* Crée un arbre de décision dont chaque branche branche sur les
     variables x_0, x_2, x_4, ..., x_(2p - 2), x_1, x_3, ..., x_(2p-1) et
     dont les feuilles sont étiquetées avec une classe booléenne qui est le
     résultat de l'évaluation de la fonction booléenne : x_0x_1 + x_2x_3 +
     ... + x_(2p-2)x_(2p-1). */
  int *path = malloc(sizeof(int) * 2 * p);
  for (int i = 0; i < 2 * p; i++) {
    path[i] = 2;
  }
  return exemple_4_aux(p, 0, path);
}

darbre exemple_5_aux(int n, int p, bool s) {
  if (p == n) {
    return cree_feuille((int) s);
  } else {
    darbre g = exemple_5_aux(n, p + 1,  s);
    darbre d = exemple_5_aux(n, p + 1, !s);
    return cree_noeud(p, g, d);
  }
}

darbre exemple_5(int n) {
  /* Crée un arbre de décision dont chaque branche branche sur les
     variables x_0, x_1, ..., x_(n-1) et dont les feuilles sont étiquetées
     avec une classe booléene qui est le résultat de l'évaluation de la
     fonction booléene x_0 + x_1 + ... + x_(n-1). */
  return exemple_5_aux(n, 0, false);
}

/********************************
 *      Jeu données exemple     *
 ********************************/

donnee_c cree_donnee_classifiee(bool* tab, int len, int c) {
  /* Crée une donnée classifiée de coordonées tab (de longueur len),
     classifiée avec la donnée c */
  donnee_c res = (donnee_c) malloc(sizeof(struct donnee_c_s));
  res->donnee.contenu = malloc(len * sizeof(bool));
  for (int i = 0 ; i < len ; i ++) {
    res->donnee.contenu[i] = tab[i];
  };
  res->donnee.dim = len;
  res->classe = c;
  return res;
}

jeu_donnees_c cree_jeu_donnees_exemple() {
  jeu_donnees_c res;
  res.taille = 16;
  res.contenu = malloc(res.taille * sizeof(donnee_c));
  bool arr0[4]  = {false, false, false, false};
  bool arr1[4]  = {false, false, false, true };
  bool arr2[4]  = {false, false, true , false};
  bool arr3[4]  = {false, false, true , true };
  bool arr4[4]  = {false, true , false, false};
  bool arr5[4]  = {false, true , false, true };
  bool arr6[4]  = {false, true , true , false};
  bool arr7[4]  = {false, true , true , true };
  bool arr8[4]  = {true , false, false, false};
  bool arr9[4]  = {true , false, false, true };
  bool arr10[4] = {true , false, true , false};
  bool arr11[4] = {true , false, true , true };
  bool arr12[4] = {true , true , false, false};
  bool arr13[4] = {true , true , false, true };
  bool arr14[4] = {true , true , true , false};
  bool arr15[4] = {true , true , true , true };
  res.contenu[0]  = cree_donnee_classifiee(arr0 , 4, 0);
  res.contenu[1]  = cree_donnee_classifiee(arr1 , 4, 2);
  res.contenu[2]  = cree_donnee_classifiee(arr2 , 4, 0);
  res.contenu[3]  = cree_donnee_classifiee(arr3 , 4, 2);
  res.contenu[4]  = cree_donnee_classifiee(arr4 , 4, 0);
  res.contenu[5]  = cree_donnee_classifiee(arr5 , 4, 2);
  res.contenu[6]  = cree_donnee_classifiee(arr6 , 4, 0);
  res.contenu[7]  = cree_donnee_classifiee(arr7 , 4, 2);
  res.contenu[8]  = cree_donnee_classifiee(arr8 , 4, 0);
  res.contenu[9]  = cree_donnee_classifiee(arr9 , 4, 1);
  res.contenu[10] = cree_donnee_classifiee(arr10, 4, 0);
  res.contenu[11] = cree_donnee_classifiee(arr11, 4, 1);
  res.contenu[12] = cree_donnee_classifiee(arr12, 4, 0);
  res.contenu[13] = cree_donnee_classifiee(arr13, 4, 1);
  res.contenu[14] = cree_donnee_classifiee(arr14, 4, 0);
  res.contenu[15] = cree_donnee_classifiee(arr15, 4, 1);
  return res;
}


/********************************
 *       Fin du compagnon       *
 ********************************/

/* Renvoie une feuille de classe classe */
darbre cree_feuille(int classe) {
    darbre res = malloc(sizeof(struct darbre_noeud_s));
    res->classe = classe;
    res->i = -1;
    res->vrai = NULL;
    res->faux = NULL;
    return res;
}


/* Renvoie un nœud dont le prédicat porte sur la composante i, dont le
 * sous-arbre faux est faux et dont le sous-arbre vrai est vrai */
darbre cree_noeud(int i, darbre faux, darbre vrai) {
    darbre res = malloc(sizeof(struct darbre_noeud_s));
    res->classe = -1;
    res->i = i;
    res->vrai = vrai;
    res->faux = faux;
    return res;
}


/* Renvoie true si da est une feuille */
bool est_feuille(darbre da) {
    return (da->classe != -1);
}


/* Libère la mémoire allouée à da */
void libere_darbre(darbre da) {
    if (!est_feuille(da)) {
        libere_darbre(da->faux);
        libere_darbre(da->vrai);
    }
    free(da);
}


/* Renvoie la classe assocée au vecteur d par l'arbre da */
int lit_darbre(darbre da, bool_vec d) {
    darbre courant = da;
    while (!est_feuille(courant)) {
        if (d.contenu[courant->i])
            courant = courant->vrai;
        else
            courant = courant->faux;
    }
    return courant->classe;
}


bool sont_egaux(darbre da1, darbre da2) {
    bool da1_feuille = est_feuille(da1);
    bool da2_feuille = est_feuille(da2);
    if (da1_feuille && da2_feuille) {
        return da1->classe == da2->classe;
    } else if ((da1_feuille && !da2_feuille) || (!da1_feuille && da2_feuille)) {
        return false;
    } else {
        return (
            (da1->i == da2->i) &&
            sont_egaux(da1->faux, da2->faux) &&
            sont_egaux(da1->vrai, da2->vrai)
        );
    }
}


/* Renvoie c si da est homogène de classe c, et -1 sinon */
int est_homogene(darbre da) {
    if (est_feuille(da))
        return da->classe;
    int vrai_homogene = est_homogene(da->vrai);
    if (vrai_homogene == -1)
        return -1;
    int faux_homogene = est_homogene(da->faux);
    if (vrai_homogene == faux_homogene)
        return vrai_homogene;
    return -1;
}


/* Renvoie l'arbre da écourté (crée un nouvel arbre et ne touche pas à da */
darbre fusionne_homogene(darbre da) {
    int classe = est_homogene(da);
    darbre res;
    if (classe == -1) {
        darbre fusion_vrai = fusionne_homogene(da->vrai);
        darbre fusion_faux = fusionne_homogene(da->faux);
        res = cree_noeud(da->i, fusion_faux, fusion_vrai);
    } else {
        res = cree_feuille(classe);
    }
    return res;
}


/* Écourte *p_da (en modifiant sa valeur), et renvoie est_homogene(*p_da) */
int fusionne_homogene_modif_classe(darbre* p_da) {
    if (est_feuille(*p_da)) {
        return (*p_da) -> classe;
    }
    int cv = fusionne_homogene_modif_classe(&((*p_da)->vrai));
    int cf = fusionne_homogene_modif_classe(&((*p_da)->faux));
    if (cv == cf && cv != -1) {
        (*p_da) -> classe = cv;
        (*p_da) -> i = -1;
        libere_darbre((*p_da)->vrai);
        libere_darbre((*p_da)->faux);
        (*p_da)->vrai = NULL;
        (*p_da)->faux = NULL;
        return cv;
    }
    return -1;
}


/* Écourte *p_da (en modifiant sa valeur) */
void fusionne_homogene_modif(darbre* p_da) {
    fusionne_homogene_modif_classe(p_da);
}


/* Remplit le tableau profil avec le profil de jdc */
void complete_profil(jeu_donnees_c jdc, int profil[K]) {
    for (int i = 0; i < K; i++) {
        profil[i] = 0;
    }
    for (int i = 0; i < jdc.taille; i++) {
        profil[jdc.contenu[i]] ++;
    }
}


/* Renvoie c si jdc est homogène de classe c, -1 sinon */
int jdc_est_homogene(jeu_donnes_c jdc) {
    // TODO
    return 0;
}


int main () {
    darbre ex = exemple_1();
    assert(est_feuille(ex->vrai->vrai->faux));

    bool_vec d;
    d.contenu = malloc(3*sizeof(bool));
    d.contenu[0] = true;
    d.contenu[1] = true;
    d.contenu[2] = false;
    d.dim = 3;

    assert(lit_darbre(ex, d) == 3);

    darbre ex_autre_part_sur_la_memoire = exemple_1();
    assert(sont_egaux(ex, ex_autre_part_sur_la_memoire));

    ex_autre_part_sur_la_memoire->i = 0;
    assert(!sont_egaux(ex, ex_autre_part_sur_la_memoire));

    ex_autre_part_sur_la_memoire->i = 1;
    ex_autre_part_sur_la_memoire->vrai->vrai->i = 1;
    assert(!sont_egaux(ex, ex_autre_part_sur_la_memoire));

    assert(est_homogene(ex) == -1);
    assert(est_homogene(ex->faux) == 0);

    darbre ex1h = fusionne_homogene(ex);
    affiche_arbre(ex1h);
    fusionne_homogene_modif(&ex);
    affiche_arbre(ex);
    assert(sont_egaux(ex, ex1h));

    free(d.contenu);
    libere_darbre(ex);
    libere_darbre(ex_autre_part_sur_la_memoire);
    libere_darbre(ex1h);
    return 0;
}
