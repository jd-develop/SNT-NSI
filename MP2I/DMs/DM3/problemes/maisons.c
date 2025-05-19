#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"


/* Pour modéliser ce problème, j’ai cinq fois cinq fois cinq variables : pour
 * chaque maison, 25 variables correspondant à chaque possibilité de chaque
 * caractéristique.
 * Les variables se nomment numéro_caractéristique.
 * Par exemple, 1_anglais, 5_poisson_rouge, 3_yop, 4_bleu, etc.
 */


char* NATIONALITES[5] = {
    "anglais",
    "suédois",
    "danois",
    "norvégien",
    "allemand"
};

char* COULEURS[5] = {
    "rouge",
    "vert",
    "blanc",
    "jaune",
    "bleu"
};

char* ANIMAUX[5] = {
    "chiens",
    "oiseaux",
    "chats",
    "cheval",
    "poisson_rouge"
};

char* BOISSONS[5] = {
    "thé",
    "café",
    "lait",
    "yop",
    "eau"
};

char* SPORTS[5] = {
    "vélo",
    "danse",
    "escalade",
    "basket",
    "karaté"
};


/*
 * À partir de deux caractéristiques car1 et car2 (par exemple, « anglais » et
 * « rouge »), construit la contrainte car1 dans la offset-ième maison à gauche
 * de car2, par exemple
 * "(1_anglais & 1_rouge) | (2_anglais & 2_rouge) | … | (5_anglais & 5_rouge)"
 * avec un offset de 0, ou encore
 * "(1_anglais & 2_rouge) | (2_anglais & 3_rouge) | … | (4_anglais & 5_rouge)"
 * avec un offset de 1.
 * Le offset ne peut être supérieur à 4
 */
String* contrainte_deux_caracteristiques(char* car1, char* car2, int offset)
{
    assert(0 <= offset && offset <= 4);

    String* res = new_string();
    char i_as_str[100];
    char i_plus_offset_as_str[100];

    for (int i = 1; i <= 5-offset; i++) {
        sprintf(i_as_str, "%d", i);
        sprintf(i_plus_offset_as_str, "%d", i+offset);

        string_append(res, "(");
        string_append(res, i_as_str);
        string_append(res, "_");
        string_append(res, car1);
        string_append(res, " & ");
        string_append(res, i_plus_offset_as_str);
        string_append(res, "_");
        string_append(res, car2);
        string_append(res, ") | ");
    }
    string_rm(res, 3);
    return res;
}


/*
 * À partir de deux caractéristiques car1 et car2 (par exemple, « anglais » et
 * « rouge »), construit la contrainte car1 dans la même maison que car2, par
 * exemple
 * "(1_anglais & 1_rouge) | (2_anglais & 2_rouge) | … | (5_anglais & 5_rouge)"
 */
String* meme_maison(char* car1, char* car2) {
    return contrainte_deux_caracteristiques(car1, car2, 0);
}


/*
 * À partir de deux caractéristiques car1 et car2 (par exemple, « anglais » et
 * « rouge »), construit la contrainte car1 à gauche de car2, par exemple
 * "(1_anglais & 2_rouge) | (2_anglais & 3_rouge) | … | (4_anglais & 5_rouge)"
 */
String* a_gauche(char* car1, char* car2) {
    return contrainte_deux_caracteristiques(car1, car2, 1);
}

/*
 * À partir de deux caractéristiques car1 et car2 (par exemple, « anglais » et
 * « rouge »), construit la contrainte car1 à droite de car2, par exemple
 * "(1_rouge & 2_anglais) | (2_rouge & 3_anglais) | … | (4_rouge & 5_anglais)"
 */
String* a_droite(char* car1, char* car2) {
    return a_gauche(car2, car1);
}


/*
 * À partir de deux caractéristiques car1 et car2 (par exemple, « anglais » et
 * « rouge »), construit la contrainte car1 et car2 voisins, par exemple
 * "(1_rouge & 2_anglais) | (2_rouge & 3_anglais) | … | (4_rouge & 5_anglais) |
 *  (1_anglais & 2_rouge) | (2_anglais & 3_rouge) | … | (4_anglais & 5_rouge)"
 */
String* voisins(char* car1, char* car2) {
    String* res = new_string();

    string_cat(res, a_droite(car1, car2));
    string_append(res, " | ");
    string_cat(res, a_gauche(car1, car2));

    return res;
}


/*
 * Construit et renvoie la contrainte « cette caractéristique se retrouve dans
 * exactement une maison ».
 */
String* contrainte_exactement_une_maison(char* caracteristique) {
    String* res = new_string();
    char i_as_str[100];

    for (int j = 1; j <= 5; j++) {
        string_append(res, "(");
        for (int i = 1; i <= 5; i++) {
            sprintf(i_as_str, "%d", i);

            if (i != j){
                string_append(res, "~");
            }
            string_append(res, i_as_str);
            string_append(res, "_");
            string_append(res, caracteristique);
            string_append(res, " & ");
        }
        string_rm(res, 3);
        string_append(res, ") | ");
    }
    string_rm(res, 3);
    return res;
}


/*
 * Construit et renvoie la contrainte « chaque caractéristique se retrouve dans
 * exactement une maison ».
 */
String* contrainte_unicite_toutes_caracteristiques() {
    String* res = new_string();
    string_append(res, "(");

    for (int i = 0; i < 5; i++) {
        string_cat(res, contrainte_exactement_une_maison(NATIONALITES[i]));
        string_append(res, ") & (");
        string_cat(res, contrainte_exactement_une_maison(COULEURS[i]));
        string_append(res, ") & (");
        string_cat(res, contrainte_exactement_une_maison(ANIMAUX[i]));
        string_append(res, ") & (");
        string_cat(res, contrainte_exactement_une_maison(BOISSONS[i]));
        string_append(res, ") & (");
        string_cat(res, contrainte_exactement_une_maison(SPORTS[i]));
        string_append(res, ") & (");
    }
    string_rm(res, 4);
    return res;
}

/*
 * Construit et renvoie la contrainte « cette maison a exactement une
 * caractéristique de cette catégorie ».
 */
String* contrainte_unicite_par_categorie(char** categorie, int maison) {
    String* res = new_string();
    char i_as_str[100];
    sprintf(i_as_str, "%d", maison);

    for (int j = 0; j < 5; j++) {
        string_append(res, "(");
        for (int i = 0; i < 5; i++) {
            if (i != j){
                string_append(res, "~");
            }
            string_append(res, i_as_str);
            string_append(res, "_");
            string_append(res, categorie[i]);
            string_append(res, " & ");
        }
        string_rm(res, 3);
        string_append(res, ") | ");
    }
    string_rm(res, 3);
    return res;
}

/*
 * Construit et renvoie la contrainte « chaque maison a exactement une
 * caractéristique de chaque type ».
 */
String* contrainte_unicite_par_categorie_toutes_maisons() {
    String* res = new_string();
    string_append(res, "(");

    for (int i = 1; i <= 5; i++) {
        string_cat(res, contrainte_unicite_par_categorie(NATIONALITES, i));
        string_append(res, ") & (");
        string_cat(res, contrainte_unicite_par_categorie(COULEURS, i));
        string_append(res, ") & (");
        string_cat(res, contrainte_unicite_par_categorie(ANIMAUX, i));
        string_append(res, ") & (");
        string_cat(res, contrainte_unicite_par_categorie(BOISSONS, i));
        string_append(res, ") & (");
        string_cat(res, contrainte_unicite_par_categorie(SPORTS, i));
        string_append(res, ") & (");
    }
    string_rm(res, 4);
    return res;
}


/* Construit et renvoie toutes les contraintes de l’énoncé */
String* contraintes_de_lenonce() {
    String* res = new_string();

    string_append(res, "(");
    string_cat(res, meme_maison("anglais", "rouge"));
    string_append(res, ") & (");
    string_cat(res, meme_maison("suédois", "chiens"));
    string_append(res, ") & (");
    string_cat(res, meme_maison("danois", "thé"));
    string_append(res, ") & (");
    string_cat(res, a_gauche("vert", "blanc"));
    string_append(res, ") & (");
    string_cat(res, meme_maison("vert", "café"));
    string_append(res, ") & (");
    string_cat(res, meme_maison("vélo", "oiseaux"));
    string_append(res, ") & (");
    string_cat(res, meme_maison("jaune", "danse"));
    string_append(res, ") & 3_lait & 1_norvégien & (");
    string_cat(res, voisins("escalade", "chats"));
    string_append(res, ") & (");
    string_cat(res, voisins("cheval", "danse"));
    string_append(res, ") & (");
    string_cat(res, meme_maison("basket", "yop"));
    string_append(res, ") & (");
    string_cat(res, meme_maison("allemand", "karaté"));
    string_append(res, ") & (");
    string_cat(res, voisins("norvégien", "bleu"));
    string_append(res, ") & (");
    string_cat(res, voisins("escalade", "eau"));
    string_append(res, ")");

    return res;
}


int main() {
    char outfile[] = "5maisons.txt";
    FILE* file = fopen(outfile, "w");
    assert(file != NULL);

    String* res = new_string();
    string_cat(res, contraintes_de_lenonce());
    string_append(res, " & ");
    string_cat(res, contrainte_unicite_toutes_caracteristiques());
    string_append(res, " & ");
    string_cat(res, contrainte_unicite_par_categorie_toutes_maisons());

    int size = res->len;
    fprintf(file, "%s\n", res->string);
    string_free(res);

    fclose(file);
    printf("Fichier '%s' généré.\n", outfile);
    printf("Taille du fichier : %d octets.\n", size);
    return 0;
}
