#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "keyval.h"
#include "dico_chaine.h"
#include "dico_hash.h"


int main() {
    /* DÉBUT TEST hash */
    char* bonjour = strdup("bonjour");
    char* texte1 = strdup("voici un texte a hacher");
    char* texte2 = strdup("voici un texte a macher");
    assert(hash(bonjour)%101 == 60);
    assert(hash(texte1)%503 == 151);
    assert(hash(texte2)%503 == 156);
    /* FIN TEST hash */

    /* DÉBUT TEST equal */
    char* chainevide = strdup("");
    assert(!equal(bonjour, texte1));
    assert(!equal(texte1, texte2));
    assert(equal(bonjour, "bonjour"));
    assert(equal("voici un texte a hacher", texte1));
    assert(equal("", ""));
    assert(equal("", chainevide));
    /* FIN TEST equal */

    /* DÉBUT TEST dico_chaine.c */
    char* valeur = malloc(100*sizeof(char));
    chain_t* dico = chain_create();

    assert(taille(dico) == 0);
    assert(!chain_get(dico, "", &valeur));
    assert(!chain_get(dico, bonjour, &valeur));

    chain_set(dico, strdup(chainevide), strdup(bonjour));
    assert(taille(dico) == 1);

    assert(chain_get(dico, "", &valeur));
    assert(strcmp(valeur, bonjour) == 0);
    assert(!chain_get(dico, bonjour, &valeur));

    chain_set(dico, strdup(bonjour), strdup(bonjour));
    chain_set(dico, strdup(texte1), strdup(texte2));
    assert(taille(dico) == 3);

    printf("----\nClés :\n");
    KEY* cles = chain_keys(dico);
    for (int i = 0; i < taille(dico); i++) {
        printf("%s\n", cles[i]);
        key_free(cles[i]);
    }
    free(cles);
    printf("----\n");

    assert(chain_get(dico, bonjour, &valeur));
    assert(strcmp(valeur, bonjour) == 0);
    assert(chain_get(dico, texte1, &valeur));
    assert(strcmp(valeur, texte2) == 0);
    assert(!chain_get(dico, texte2, &valeur));

    chain_set(dico, strdup(texte1), strdup(bonjour));
    assert(chain_get(dico, texte1, &valeur));
    assert(strcmp(valeur, bonjour) == 0);
    assert(taille(dico) == 3);

    assert(!chain_delete(dico, texte2));
    assert(chain_delete(dico, "voici un texte a hacher"));
    assert(taille(dico) == 2);
    assert(!chain_get(dico, texte1, NULL));

    chain_free(dico);
    /* FIN TEST dico_chaine.c */

    /* DÉBUT TEST dico_hash.c */
    hashtable_t* dicohash = hash_create();

    assert(!hash_get(dicohash, "", &valeur));
    assert(!hash_get(dicohash, bonjour, &valeur));

    hash_set(dicohash, strdup(chainevide), strdup(bonjour));
    assert(hash_get(dicohash, "", &valeur));
    assert(strcmp(valeur, bonjour) == 0);
    assert(!hash_get(dicohash, bonjour, &valeur));

    hash_set(dicohash, strdup(bonjour), strdup(bonjour));
    hash_set(dicohash, strdup(texte1), strdup(texte2));

    printf("----\nClés :\n");
    KEY* cles1 = hash_keys(dicohash);
    for (int i = 0; i < hash_taille(dicohash); i++) {
        printf("%s\n", cles1[i]);
        key_free(cles1[i]);
    }
    free(cles1);
    printf("----\n");

    hash_set(dicohash, strdup("clé 1"), strdup("valeur 1"));
    hash_set(dicohash, strdup("clé 2"), strdup("valeur 2"));
    hash_set(dicohash, strdup("clé 3"), strdup("valeur 3"));
    hash_set(dicohash, strdup("clé 4"), strdup("valeur 4"));
    hash_set(dicohash, strdup("clé 5"), strdup("valeur 5"));
    hash_set(dicohash, strdup("clé 6"), strdup("valeur 6"));
    hash_set(dicohash, strdup("clé 7"), strdup("valeur 7"));
    hash_set(dicohash, strdup("clé 8"), strdup("valeur 8"));
    hash_set(dicohash, strdup("clé 9"), strdup("valeur 9"));
    hash_set(dicohash, strdup("clé 10"), strdup("valeur 10"));

    hash_print(dicohash);
    printf("----\nClés :\n");
    KEY* cles2 = hash_keys(dicohash);
    for (int i = 0; i < hash_taille(dicohash); i++) {
        printf("%s\n", cles2[i]);
        key_free(cles2[i]);
    }
    free(cles2);
    printf("----\n");

    hash_delete(dicohash, "clé 1");
    hash_delete(dicohash, "clé 2");
    hash_delete(dicohash, "clé 3");
    hash_delete(dicohash, "clé 4");
    hash_delete(dicohash, "clé 5");
    hash_delete(dicohash, "clé 6");
    hash_delete(dicohash, "clé 7");
    hash_delete(dicohash, "clé 8");
    hash_delete(dicohash, "clé 9");
    hash_delete(dicohash, "clé 10");

    printf("\n");
    // hash_print(dicohash);

    assert(hash_get(dicohash, bonjour, &valeur));
    assert(strcmp(valeur, bonjour) == 0);
    assert(hash_get(dicohash, texte1, &valeur));
    assert(strcmp(valeur, texte2) == 0);
    assert(!hash_get(dicohash, texte2, &valeur));

    hash_set(dicohash, strdup(texte1), strdup(bonjour));
    assert(hash_get(dicohash, texte1, &valeur));
    assert(strcmp(valeur, bonjour) == 0);

    assert(!hash_delete(dicohash, texte2));
    assert(hash_delete(dicohash, "voici un texte a hacher"));
    assert(!hash_get(dicohash, texte1, NULL));

    printf("----\nClés :\n");
    KEY* cles3 = hash_keys(dicohash);
    for (int i = 0; i < hash_taille(dicohash); i++) {
        printf("%s\n", cles3[i]);
        key_free(cles3[i]);
    }
    free(cles3);
    printf("----\n");
    hash_free(dicohash);
    /* FIN TEXT dico_hash.c */

    free(bonjour);
    free(texte1);
    free(texte2);
    free(chainevide);
    free(valeur);

    return 0;
}
