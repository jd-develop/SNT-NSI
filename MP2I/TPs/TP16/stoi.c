#include "stoi.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct maillon{
 char* clef;
    int valeur;
    struct maillon* suiv;
} maillon_t;

typedef struct stoi {
    maillon_t* table[TAILLE_HASH];
} stoi_t;

unsigned int hash(char* s){
    unsigned int res = 0;
    for (int i = 0; s[i] != 0; ++i)
    {
        res = (256 * res + s[i])%TAILLE_HASH;
    }
    return res;
}


stoi_t* stoi_vide(){
    stoi_t* t = malloc(sizeof(stoi_t));
    for (int i = 0; i < TAILLE_HASH; ++i)
    {
        t->table[i] = NULL;
    }
    return t;
}

bool stoi_mem(stoi_t* t, char* clef){
    int h = hash(clef);
    maillon_t* m = t->table[h];
    // parcourir la liste chaînée jusqu'à trouver
    // la clef ou arriver à la fin
    while (m != NULL && strcmp(m->clef, clef) != 0){
        m = m->suiv;
    }
    return (m != NULL);
}


int stoi_get(stoi_t* t, char* clef){
    int h = hash(clef);
    maillon_t* m = t->table[h];
    while (m != NULL && strcmp(m->clef, clef) != 0){
        m = m->suiv;
    }
    if (m == NULL){
        printf("Clé invalide: [%s]\n", clef);
        exit(1);
    } else {
        return (m->valeur);
    }
}

void stoi_set(stoi_t* t, char* clef, int valeur){
    int h = hash(clef);
    maillon_t* m = t->table[h];
    // chercher la clé
    while (m != NULL && strcmp(m->clef, clef) != 0){
        m = m->suiv;
    }
    // si la recherche est infructueuse, créer un nouveau maillon pour l'association
    if (m == NULL){
        m = malloc(sizeof(maillon_t));
        m->suiv = t->table[h];
        t->table[h] = m;
        m->clef = clef;
    }
    m->valeur = valeur;
}

void stoi_free(stoi_t* t){
    for (int i = 0; i < TAILLE_HASH; ++i)
    {
        maillon_t* m = t->table[i];
        maillon_t* p = NULL;
        while (m != NULL){
            p = m;
            m = m->suiv;
            free(p);
        }
    }
    free(t);
}
