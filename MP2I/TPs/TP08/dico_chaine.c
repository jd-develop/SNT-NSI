#include "dico_chaine.h"
#include "keyval.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

chain_t* chain_create(){
    chain_t* d = malloc(sizeof(chain_t));
    d->head = NULL;
    d->n = 0;
    return d;
}

int taille(chain_t* d){
    return d->n;
}

bool chain_get(chain_t* d, KEY k, VAL* v){
    maillon_t* m = d->head;
    while (m != NULL){
        if (equal(m->key, k)) {
            strcpy(*v, m->val);
            return true;
        }
        m = m->next;
    }
    return false;
}

bool chain_set(chain_t* d, KEY k, VAL v){
    maillon_t* m = d->head;
    while(m != NULL && !equal(m->key, k)){
        m = m->next;
    }
    // en sortie de boucle: si m est NULL la clé k n'est
    // pas dans d, il faut créer un nouveau maillon. Sinon,
    // le maillon m contient la clé k, il suffit de modifier
    // sa valeur
    if (m == NULL){
        d->n++;
        // nouveau maillon_t
        m = malloc(sizeof(maillon_t));
        // si on exécute test.c sans les deux lignes suivantes, on a un double
        // free
        m->key = k;
        m->val = v;

        // ajout de m en tête de liste: deux liens à créer
        // entre m et la tête actuelle (qui peut être NULL)
        m->prev = NULL;
        m->next = d->head;
        if (d->head != NULL){
            d->head->prev = m;
        }
        d->head = m;
        return false;
    } else {
        val_free(m->val);
        m->val = v;
        key_free(k);
        return true;
    }
}

bool chain_delete(chain_t* d, KEY k){
    maillon_t* m = d->head;
    while(m != NULL && !equal(m->key, k)){
        m = m->next;
    }

    if (m == NULL){
        return false;
    }

    maillon_t* prev = m->prev;
    maillon_t* next = m->next;

    // Lier les deux maillons autour du maillon supprimé
    if (prev != NULL){
        prev->next = next;
    } else {
        d->head = next;
    }
    if (next != NULL){
        next->prev = prev;
    }
    key_free(m->key);
    val_free(m->val);
    free(m);
    d->n--;
    return true;
}


void chain_print(chain_t* d){
    maillon_t* m = d->head;
    if (m == NULL){
        printf("(liste vide)\n");
    }
    while (m != NULL){
        key_print(m->key);
        printf(" -> ");
        val_print(m->val);
        printf("\n");
        m = m->next;
    }
}


void free_maillon(maillon_t* m){
    if (m != NULL){
        free_maillon(m->next);
        key_free(m->key);
        val_free(m->val);
        free(m);
    }
}

void chain_free(chain_t* d){
    free_maillon(d->head);
    free(d);
}

KEY* chain_keys(chain_t* d) {
    int len = taille(d);
    KEY* keys = malloc(len*sizeof(KEY));
    maillon_t* m = d->head;
    for (int i = 0; i < len; i++) {
        keys[i] = strdup(m->key);
        m = m->next;
    }
    return keys;
}
