#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "keyval.h"
#include "dico_chaine.h"


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

    chain_set(dico, chainevide, bonjour);
    assert(taille(dico) == 1);

    assert(chain_get(dico, "", &valeur));
    assert(strcmp(valeur, bonjour) == 0);
    assert(!chain_get(dico, bonjour, &valeur));

    chain_set(dico, bonjour, bonjour);
    chain_set(dico, texte1, texte2);
    assert(taille(dico) == 3);

    assert(chain_get(dico, bonjour, &valeur));
    assert(strcmp(valeur, bonjour) == 0);
    assert(chain_get(dico, texte1, &valeur));
    assert(strcmp(valeur, texte2) == 0);
    assert(!chain_get(dico, texte2, &valeur));

    chain_set(dico, texte1, bonjour);
    assert(chain_get(dico, texte1, &valeur));
    assert(strcmp(valeur, bonjour) == 0);
    assert(taille(dico) == 3);

    assert(!chain_delete(dico, texte2));
    assert(chain_delete(dico, "voici un texte a hacher"));
    assert(taille(dico) == 2);
    assert(!chain_get(dico, texte1, NULL));

    chain_free(dico);
    /* FIN TEST dico_chaine.c */

    free(bonjour);
    free(texte1);
    free(texte2);
    free(chainevide);
    free(valeur);

    return 0;
}
