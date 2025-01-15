#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dico_hash.h"
#include "keyval.h"

/* Renvoie la clé de d dont la valeur est maximale. On suppose que d n’est pas
 * vide et que toutes les valeurs sont des entiers positifs */
char* argmax(hashtable_t* d) {
    assert(hash_taille(d) != 0);
    KEY* keys = hash_keys(d);

    KEY current_max_k = keys[0];
    VAL current_max_v;
    hash_get(d, keys[0], &current_max_v);
    assert(current_max_v >= 0);
    VAL value;

    for (int i = 0; i < hash_taille(d); i++) {
        assert(hash_get(d, keys[i], &value));
        assert(value >= 0);
        if (value >= current_max_v) {
            current_max_k = keys[i];
            current_max_v = value;
        }
    }
    for (int i = 0; i < hash_taille(d); i++) {
        if (!equal(current_max_k, keys[i])) {
            free(keys[i]);
        }
    }
    free(keys);
    return current_max_k;
}

void occurences(char* filename, int K) {

}

void test() {
    hashtable_t* ht = hash_create();
    hash_set(ht, strdup("lorem"), 12);
    hash_set(ht, strdup("ipsum"), 8);
    hash_set(ht, strdup("dolor"), 15);
    hash_set(ht, strdup("sit"), 0);
    hash_set(ht, strdup("amet"), 14);

    KEY max = argmax(ht);
    assert(equal(max, "dolor"));
    key_free(max);
    hash_free(ht);
}

int main() {
    printf("hello world\n");
    test();
}
