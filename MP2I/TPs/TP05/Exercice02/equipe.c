#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

struct etudiant {
    char* prenom;
    unsigned int age;
};
typedef struct etudiant etu_t;

typedef struct equipe{
    unsigned int nb_membres;
    etu_t** membres; // tableaux de pointeurs vers les membres de l'equipe
    unsigned int indice_cpt; // indice du capitaine dans le tableau des membres
} equipe_t;

/* Affiche les informations de l’étudiant représenté par la structure pointée
 * par `e`
 */
void print_etu(etu_t* e) {
    printf("%s, %d ans\n", e->prenom, e->age);
}

/* Affiche les informations de l’équipe représentée par la structure pointée
 * par `e`
 */
void print_equipe(equipe_t* e) {
    for (uint i = 0; i < e->nb_membres; i++) {
        if (e->indice_cpt == i)
            printf("Capitaine : ");
        print_etu(e->membres[i]);
    }
}

/* Libère la mémoire réservée à un étudiant */
void free_etu(etu_t* e) {
    free(e);
}

/* Libère la mémoire réservée à une équipe */
void free_equipe(equipe_t* e) {
    for (uint i = 0; i < e->nb_membres; i++) {
        free_etu(e->membres[i]);
    }
    free(e->membres);
    free(e);
}

int main() {
    equipe_t* equipe_1 = malloc(sizeof(equipe_t));
    equipe_1->membres = malloc(3*sizeof(etu_t*));
    equipe_1->nb_membres = 3;

    equipe_1->membres[0] = malloc(sizeof(etu_t));
    equipe_1->membres[0]->prenom = "Camille";
    equipe_1->membres[0]->age = 23;

    equipe_1->membres[1] = malloc(sizeof(etu_t));
    equipe_1->membres[1]->prenom = "Leila";
    equipe_1->membres[1]->age = 20;
    equipe_1->indice_cpt = 1;

    equipe_1->membres[2] = malloc(sizeof(etu_t));
    equipe_1->membres[2]->prenom = "Thibault";
    equipe_1->membres[2]->age = 22;

    print_equipe(equipe_1);
    free_equipe(equipe_1);

    return 0;
}
