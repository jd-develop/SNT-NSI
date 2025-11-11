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
/* fusionne_homogene_modif_classe est bien de complexité linéaire en le nombre
 * de nœuds. En effet, elle est en O(1) sur les feuilles, et elle est au mieux
 * en O(nb nœuds vrai)+O(nb nœuds faux) et au pire en O(nb nœuds vrai) +
 * O(nb nœuds faux) + O(nb nœuds vrai) + O(nb nœuds faux) = O(nb nœuds vrai) +
 * O(nb nœuds faux) sur les nœuds */


/* Écourte *p_da (en modifiant sa valeur) */
void fusionne_homogene_modif(darbre* p_da) {
    fusionne_homogene_modif_classe(p_da);
}

/* Modifie *p_da en supprimant les disjonctions inutiles (i.e. les disjonctions
 * qui ont pour sous-arbres vrai et faux deux arbres équivalents). L’arbre en
 * entrée est supposé écourté. */
void supprime_disjonctions_inutiles_aux(darbre* p_da) {
    if (est_feuille(*p_da)) {
        return;
    }
    supprime_disjonctions_inutiles_aux(&((*p_da)->vrai));
    supprime_disjonctions_inutiles_aux(&((*p_da)->faux));
    if (sont_egaux((*p_da)->vrai, (*p_da)->faux)) {
        libere_darbre((*p_da)->vrai);
        darbre nouveau = (*p_da)->faux;
        free(*p_da);
        *p_da = nouveau;
    }
}


/* Modifie *p_da en supprimant les disjonctions inutiles (i.e. les disjonctions
 * qui ont pour sous-arbres vrai et faux deux arbres équivalents). Écourte
 * d’abord l’arbre. */
void supprime_disjonctions_inutiles(darbre* p_da) {
    fusionne_homogene_modif(p_da);
    supprime_disjonctions_inutiles_aux(p_da);
}


/* Remplit le tableau profil avec le profil de jdc */
void complete_profil(jeu_donnees_c jdc, int profil[K]) {
    for (int i = 0; i < K; i++) {
        profil[i] = 0;
    }
    for (int j = 0; j < jdc.taille; j++) {
        profil[jdc.contenu[j]->classe] ++;
    }
}


/* Renvoie c si jdc est homogène de classe c, -1 sinon */
int jdc_est_homogene(jeu_donnees_c jdc) {
    int* profil = malloc(K * sizeof(int));
    complete_profil(jdc, profil);

    for (int i = 0; i < K; i++) {
        if (profil[i] == jdc.taille) {
            int classe = i;
            free(profil);
            return classe;
        }
    }

    free(profil);
    return -1;
}


/* Renvoie l’entropie du jeu de données classifiées jdc */
/* Note : j’ai fait la somme des -|f⁻¹({c})|*ln(|f⁻¹({c})), puis divisé par
 * par 1/|S|, et j’ai ajouté ln(|S|) */
float entropie(jeu_donnees_c jdc) {
    int* profil = malloc(K * sizeof(int));
    complete_profil(jdc, profil);

    float res = 0.;
    for (int i = 0; i < K; i++) {
        if (profil[i] != 0) {
            res -= ((float) profil[i]) * logf((float) profil[i]);
        }
    }
    res /= (float) (jdc.taille);
    res += logf((float) (jdc.taille));

    free(profil);
    return res;
}


/* Partitionne le jeu de données classifiées jdc en 2 : un jeu de données
 * « vrai » (pour lequel toutes les composantes sur i sont vraies), qui est
 * mis dans la case pointée par jdc_i_vrai, et un jeu de données « faux » (pour
 * lequel toutes les composantes sur i sont fausses), qui est mis dans la case
 * pointée par jdc_i_faux. Les données sont copiées par référence, donc il
 * ne faudra les libérer qu’une seule fois ! */
void partitionne_jdc(
    jeu_donnees_c jdc, int i, jeu_donnees_c* jdc_i_faux,
    jeu_donnees_c* jdc_i_vrai
) {
    int nb_vrais = 0;
    for (int j = 0; j < jdc.taille; j++) {
        if (jdc.contenu[j]->donnee.contenu[i])
            nb_vrais++;
    }
    (*jdc_i_vrai).taille = nb_vrais;
    (*jdc_i_vrai).contenu = malloc(nb_vrais * sizeof(donnee_c));
    (*jdc_i_faux).taille = jdc.taille-nb_vrais;
    (*jdc_i_faux).contenu = malloc((*jdc_i_faux).taille * sizeof(donnee_c));

    int idx_vrai = 0;
    int idx_faux = 0;
    for (int j = 0; j < jdc.taille; j++) {
        if (jdc.contenu[j]->donnee.contenu[i]) {
            (*jdc_i_vrai).contenu[idx_vrai] = jdc.contenu[j];
            idx_vrai++;
        } else {
            (*jdc_i_faux).contenu[idx_faux] = jdc.contenu[j];
            idx_faux++;
        }
    }
}


/* Renvoie l’entropie de la partition du jeu de données classifiées i selon la
 * i-ième coordonée */
float entropie_disjonction_i(jeu_donnees_c jdc, int i) {
    jeu_donnees_c jdc_i_vrai;
    jeu_donnees_c jdc_i_faux;

    partitionne_jdc(jdc, i, &jdc_i_faux, &jdc_i_vrai);

    float entropie_partition = 0.;
    entropie_partition += (float) jdc_i_faux.taille * entropie(jdc_i_faux);
    entropie_partition += (float) jdc_i_vrai.taille * entropie(jdc_i_vrai);
    entropie_partition /= (float) jdc.taille,

    free(jdc_i_vrai.contenu);
    free(jdc_i_faux.contenu);

    return entropie_partition;
}


/* Renvoie l’indice de coordonnée i minimisant l’entropie de la partition
 * selon la coordonnée i du jeu de données jdc, tel que i ne soit pas déjà
 * utilisé (i.e. utilisees.contenu[i] est faux). Renvoie -1 si tous les indices
 * sont utilisés. */
int minimiseur_entropie(jeu_donnees_c jdc, bool_vec utilisees) {
    int i_min = -1;
    float entropie_min = INFINITY;  // macro C99
    float entropie_calculee;
    if (jdc.taille == 0)
        return -1;
    for (int i = 0; i < jdc.contenu[0]->donnee.dim; i++) {
        if (utilisees.contenu[i])
            continue;
        entropie_calculee = entropie_disjonction_i(jdc, i);
        if (entropie_calculee < entropie_min) {
            entropie_min = entropie_calculee;
            i_min = i;
        }
    }

    return i_min;
}


/* Comme id3 (cf. plus loin) mais n’utilise pas les indices de utilisees */
darbre id3_aux(jeu_donnees_c jdc, bool_vec utilisees) {
    if (jdc.taille == 1) {
        return cree_feuille(jdc.contenu[0]->classe);
    }
    int i_min = minimiseur_entropie(jdc, utilisees);
    utilisees.contenu[i_min] = true;

    jeu_donnees_c jdc_i_faux;
    jeu_donnees_c jdc_i_vrai;
    partitionne_jdc(jdc, i_min, &jdc_i_faux, &jdc_i_vrai);

    darbre arbre_faux = id3_aux(jdc_i_faux, utilisees);
    darbre arbre_vrai = id3_aux(jdc_i_vrai, utilisees);
    free(jdc_i_faux.contenu);
    free(jdc_i_vrai.contenu);

    utilisees.contenu[i_min] = false;
    return cree_noeud(i_min, arbre_faux, arbre_vrai);
}


/* Renvoie un arbre de décision pour le jeu de données jdc. Renvoie un arbre
 * écourté puis dont les disjonctions inutiles ont été supprimées. Plante
 * si le jeu de données est vide. */
darbre id3(jeu_donnees_c jdc) {
    assert(jdc.taille != 0);
    int dim = jdc.contenu[0]->donnee.dim;

    bool_vec utilisees;
    utilisees.contenu = malloc(dim*sizeof(bool));
    for (int i = 0; i < dim; i++)
        utilisees.contenu[i] = false;

    darbre res = id3_aux(jdc, utilisees);
    supprime_disjonctions_inutiles(&res); // écourte aussi l’arbre

    free(utilisees.contenu);
    return res;
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

    /* test de lit_darbre */
    assert(lit_darbre(ex, d) == 3);

    /* test de sont_egaux */
    darbre ex_autre_part_sur_la_memoire = exemple_1();
    assert(sont_egaux(ex, ex_autre_part_sur_la_memoire));

    ex_autre_part_sur_la_memoire->i = 0;
    assert(!sont_egaux(ex, ex_autre_part_sur_la_memoire));

    ex_autre_part_sur_la_memoire->i = 1;
    ex_autre_part_sur_la_memoire->vrai->vrai->i = 1;
    assert(!sont_egaux(ex, ex_autre_part_sur_la_memoire));

    /* test de est_homogene */
    assert(est_homogene(ex) == -1);
    assert(est_homogene(ex->faux) == 0);

    /* test de fusionne_homogene et fusionne_homogene_modif */
    darbre ex1h = fusionne_homogene(ex);
    printf("fusionne_homogene(exemple_1())\n");
    affiche_arbre(ex1h);
    fusionne_homogene_modif(&ex);
    affiche_arbre(ex);
    assert(sont_egaux(ex, ex1h));

    printf("fusionne_homogene(example_3(3))\n");
    darbre ex3 = exemple_3(3);
    darbre ex3h = cree_noeud(
        0,
        cree_feuille(0),
        cree_feuille(1)
    );

    fusionne_homogene_modif(&ex3);
    affiche_arbre(ex3);
    affiche_arbre(ex3h);
    assert(sont_egaux(ex3, ex3h));

    /* test de supprime_disjonctions_inutiles */
    printf("supprime_disjonctions_inutiles(example_2(3))\n");
    darbre ex2 = exemple_2(3);
    affiche_arbre(ex2);
    supprime_disjonctions_inutiles(&ex2);
    darbre ex2bis = cree_noeud(
        2,
        cree_feuille(0),
        cree_feuille(1)
    );
    affiche_arbre(ex2);
    affiche_arbre(ex2bis);
    assert(sont_egaux(ex2, ex2bis));

    /* test de complete_profil */
    jeu_donnees_c jdc = cree_jeu_donnees_exemple();
    int profil[K];
    complete_profil(jdc, profil);
    assert(profil[0] == 8);
    assert(profil[1] == 4);
    assert(profil[2] == 4);
    assert(profil[3] == 0);

    /* test de jdc_est_homogene */
    assert(jdc_est_homogene(jdc) == -1);

    jeu_donnees_c jdc_test;
    jdc_test.taille = 3;
    jdc_test.contenu = malloc(3*sizeof(donnee_c));
    bool arr0[2] = {false, false};
    bool arr1[2] = {true, false};
    bool arr2[2] = {true, true};
    jdc_test.contenu[0] = cree_donnee_classifiee(arr0, 2, 1);
    jdc_test.contenu[1] = cree_donnee_classifiee(arr1, 2, 1);
    jdc_test.contenu[2] = cree_donnee_classifiee(arr2, 2, 1);
    assert(jdc_est_homogene(jdc_test) == 1);

    /* test de entropie (calcul à la main au préalable) */
    float epsilon = 0.0001;

    float entropie_jdc = 1.039720771;
    float entropie_jdc_calculee = entropie(jdc);
    assert(entropie_jdc-epsilon <= entropie_jdc_calculee);
    assert(entropie_jdc_calculee <= entropie_jdc+epsilon);

    float entropie_jdc_test_calculee = entropie(jdc_test);
    assert(-epsilon <= entropie_jdc_test_calculee);
    assert(entropie_jdc_test_calculee <= epsilon);

    /* test de partitionne_jdc */
    jeu_donnees_c jdc_2_faux;
    jeu_donnees_c jdc_2_vrai;
    partitionne_jdc(jdc, 2, &jdc_2_faux, &jdc_2_vrai);
    assert(jdc_2_faux.taille == 8);
    assert(jdc_2_vrai.taille == 8);
    for (int j = 0; j < jdc.taille; j++) {
        // décommenter les printf pour constater que la formule moche fonctionne
        if ((j&2) == 0) {
            // printf("%.2d %d f\n", j, 2*(j/4)+((j%4)%2));
            assert(jdc_2_faux.contenu[2*(j/4)+((j%4)%2)] == jdc.contenu[j]);
        } else {
            // printf("%.2d %d v\n", j, 2*(j/4)+((j%4)%2));
            assert(jdc_2_vrai.contenu[2*(j/4)+((j%4)%2)] == jdc.contenu[j]);
        }
    }

    /* test de entropie_disjonction_i */
    float entropie_disjonction_2_calculee = entropie_disjonction_i(jdc, 2);
    // note : entropie_disjonction_2 = ½ln(8) = entropie_jdc
    assert(entropie_jdc-epsilon <= entropie_disjonction_2_calculee);
    assert(entropie_disjonction_2_calculee <= entropie_jdc+epsilon);

    float entropie_disjonction_3 = 0.3465735903;
    float entropie_disjonction_3_calculee = entropie_disjonction_i(jdc, 3);
    assert(entropie_disjonction_3-epsilon <= entropie_disjonction_3_calculee);
    assert(entropie_disjonction_3_calculee <= entropie_disjonction_3+epsilon);

    /* test de minimiseur_entropie */
    bool_vec utilisees;
    utilisees.contenu = malloc(4*sizeof(bool));
    for (int i = 0; i < 4; i++)
        utilisees.contenu[i] = false;
    assert(minimiseur_entropie(jdc, utilisees) == 3);

    utilisees.contenu[3] = true;
    // entropie selon 0 : 0.6931
    // entropie selon 1 : 1.0397
    // entropie selon 2 : 1.0397
    assert(minimiseur_entropie(jdc, utilisees) == 0);

    /* test id3 */
    printf("ID3\n");
    darbre id3_jdc = id3(jdc);
    affiche_arbre(id3_jdc);
    darbre arbre_attendu = cree_noeud(
        3,
        cree_feuille(0),
        cree_noeud(
            0,
            cree_feuille(2),
            cree_feuille(1)
        )
    );
    assert(sont_egaux(id3_jdc, arbre_attendu));

    darbre id3_jdc_test = id3(jdc_test);
    darbre arbre_attendu_jdc_test = cree_feuille(1);
    assert(sont_egaux(id3_jdc_test, arbre_attendu_jdc_test));

    /* libération de la mémoire */
    free(d.contenu);
    libere_darbre(ex);
    libere_darbre(ex_autre_part_sur_la_memoire);
    libere_darbre(ex1h);
    libere_darbre(ex3);
    libere_darbre(ex3h);
    libere_darbre(ex2);
    libere_darbre(ex2bis);
    libere_darbre(id3_jdc);
    libere_darbre(arbre_attendu);
    libere_darbre(id3_jdc_test);
    libere_darbre(arbre_attendu_jdc_test);

    /* jeu de données */
    for (int i = 0; i < jdc.taille; i++) {
        free(jdc.contenu[i]->donnee.contenu);
        free(jdc.contenu[i]);
    }
    free(jdc.contenu);
    free(jdc_2_faux.contenu);
    free(jdc_2_vrai.contenu);

    for (int i = 0; i < jdc_test.taille; i++) {
        free(jdc_test.contenu[i]->donnee.contenu);
        free(jdc_test.contenu[i]);
    }
    free(jdc_test.contenu);

    free(utilisees.contenu);

    return 0;
}
