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
    free(e->prenom);
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

/* Rajoute les membres de l’équipe pointée par `src` à l’équipe pointée par
 * `dst`. Garde le capitaine de l’équipe la plus grande. Les structures
 * etudiant manipulées sont dupliquées et l’équipe source n’est pas
 * invalidée. Il faut donc, après exécution de cette fonction, libérer
 * la mémoire allouée aux deux équipes
 */
void agrandir_equipe(equipe_t* dst, equipe_t* src) {
    uint nb_membres_tot = dst->nb_membres + src->nb_membres
    uint indice_cpt;
    if (dst->nb_membres > src->nb_membres) {
        indice_cpt = dst->indice_cpt;
    } else {
        indice_cpt = dst->nb_membres + src->indice_cpt;
    }

    etu_t** nouveaux_membres = malloc(nb_membres_tot*sizeof(etu_t*))

    // on copie les poiteurs des étudiants de l’équipe destination vers la
    // nouvelle équipe destination
    for (uint i = 0; i < dst->nb_membres; i++) {
        nouveaux_membres[i] = dst->membres[i];
    }
    free(dst->membres);
    dst->membres = nouveaux_membres;

    etu_t* nouveau_membre;
    int longueur_prenom;
    for (uint i = 0; i < src->nb_membres; i++) {
        nouveau_membre = malloc(sizeof(etu_t));

        longueur_prenom = strlen(src->membres[i]->prenom) + 1;
        nouveau_membre->prenom = malloc(longueur_prenom*sizeof(char));
        strcpy(nouveau_membre->prenom, src->membres[i]);

        nouveau_membre.age = src->membres[i]->age;

        dst->membres[dst->nb_membres + i] = nouveau_membre;
    }
}


int main() {
    equipe_t* equipe_1 = malloc(sizeof(equipe_t));
    equipe_1->membres = malloc(3*sizeof(etu_t*));
    equipe_1->nb_membres = 3;

    equipe_1->membres[0] = malloc(sizeof(etu_t));
    equipe_1->membres[0]->prenom = malloc(8*sizeof(char));
    strcpy(equipe_1->membres[0]->prenom, "Camille");

    equipe_1->membres[0]->age = 23;

    equipe_1->membres[1] = malloc(sizeof(etu_t));
    equipe_1->membres[1]->prenom = malloc(6*sizeof(char));
    strcpy(equipe_1->membres[1]->prenom, "Leila");
    equipe_1->membres[1]->age = 20;
    equipe_1->indice_cpt = 1;

    equipe_1->membres[2] = malloc(sizeof(etu_t));
    equipe_1->membres[2]->prenom = malloc(9*sizeof(char));
    strcpy(equipe_1->membres[2]->prenom, "Thibault");
    equipe_1->membres[2]->age = 22;

    print_equipe(equipe_1);
    free_equipe(equipe_1);

    return 0;
}
