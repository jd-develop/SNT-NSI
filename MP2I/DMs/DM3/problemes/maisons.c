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


const char* NATIONALITES[5] = {
    "anglais",
    "suédois",
    "danois",
    "norvégien",
    "allemand"
};

const char* COULEURS[5] = {
    "rouge",
    "vert",
    "blanc",
    "jaune",
    "bleu"
};

const char* ANIMAUX[5] = {
    "chiens",
    "oiseaux",
    "chats",
    "cheval",
    "poisson_rouge"
};

const char* BOISSONS[5] = {
    "thé",
    "café",
    "lait",
    "yop",
    "eau"
};

const char* SPORTS[5] = {
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
String* contrainte_deux_caracteristiques(String* car1, String* car2, int offset)
{
    assert(0 <= offset && offset <= 4);

    String* res = new_string();
    char* i_as_str = malloc(2*sizeof(char));
    char* i_plus_offset_as_str = malloc(2*sizeof(char));

    for (int i = 1; i <= 5-offset; i++) {
        sprintf(i_as_str, "%d", i);
        sprintf(i_plus_offset_as_str, "%d", i+offset);

        string_append(res, "(");
        string_append(res, i_as_str);
        string_append(res, "_");
        string_append(res, car1->string);
        string_append(res, " & ");
        string_append(res, i_plus_offset_as_str);
        string_append(res, "_");
        string_append(res, car2->string);
        string_append(res, ")");
        if (i != 5-offset) {
            string_append(res, " | ");
        }
    }

    free(i_as_str);
    return res;
}


/*
 * À partir de deux caractéristiques car1 et car2 (par exemple, « anglais » et
 * « rouge »), construit la contrainte car1 dans la même maison que car2, par
 * exemple
 * "(1_anglais & 1_rouge) | (2_anglais & 2_rouge) | … | (5_anglais & 5_rouge)"
 */
String* meme_maison(char* car1, char* car2) {
    String* c1 = new_string();
    String* c2 = new_string();

    string_append(c1, car1);
    string_append(c2, car2);

    String* res = contrainte_deux_caracteristiques(c1, c2, 0);

    string_free(c1);
    string_free(c2);

    return res;
}


/*
 * À partir de deux caractéristiques car1 et car2 (par exemple, « anglais » et
 * « rouge »), construit la contrainte car1 à gauche de car2, par exemple
 * "(1_anglais & 2_rouge) | (2_anglais & 3_rouge) | … | (4_anglais & 5_rouge)"
 */
String* a_gauche(char* car1, char* car2) {
    String* c1 = new_string();
    String* c2 = new_string();

    string_append(c1, car1);
    string_append(c2, car2);

    String* res = contrainte_deux_caracteristiques(c1, c2, 1);

    string_free(c1);
    string_free(c2);

    return res;
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
    String* droite = a_droite(car1, car2);
    String* gauche = a_gauche(car1, car2);

    String* res = new_string();
    string_append(res, droite->string);
    string_append(res, " | ");
    string_append(res, gauche->string);

    string_free(droite);
    string_free(gauche);

    return res;
}


/*
 * Construit et renvoie la contrainte « cette caractéristique se retrouve dans
 * exactement une maison ».
 */
String* contrainte_exactement_une_maison(String* caracteristique) {
    String* res = new_string();
    char* i_as_str = malloc(2*sizeof(char));

    for (int j = 1; j <= 5; j++) {
        string_append(res, "(");
        for (int i = 1; i <= 5; i++) {
            sprintf(i_as_str, "%d", i);

            if (i != j)
                string_append(res, "~");
            string_append(res, i_as_str);
            string_append(res, "_");
            string_append(res, caracteristique->string);
            if (i != 5)
                string_append(res, " & ");
        }
        string_append(res, ")");
        if (j != 5)
            string_append(res, " | ");
    }

    return res;
}


/*
 * Construit et renvoie la contrainte « chaque caractéristique se retrouve dans
 * exactement une maison ».
 */
String* contrainte_unicite_toutes_caracteristiques() {
    String* caracteristique = new_string();
    String* res = new_string();

    string_append(res, "(");
    for (int i = 0; i < 5; i++) {
        if (i != 0)
            string_rm(caracteristique, caracteristique->len);

        string_append(caracteristique, NATIONALITES[i]);
        string_cat(res, contrainte_exactement_une_maison(caracteristique));
        string_append(res, ") & (");

        string_rm(caracteristique, caracteristique->len);
        string_append(caracteristique, COULEURS[i]);
        string_cat(res, contrainte_exactement_une_maison(caracteristique));
        string_append(res, ") & (");

        string_rm(caracteristique, caracteristique->len);
        string_append(caracteristique, ANIMAUX[i]);
        string_cat(res, contrainte_exactement_une_maison(caracteristique));
        string_append(res, ") & (");

        string_rm(caracteristique, caracteristique->len);
        string_append(caracteristique, BOISSONS[i]);
        string_cat(res, contrainte_exactement_une_maison(caracteristique));
        string_append(res, ") & (");

        string_rm(caracteristique, caracteristique->len);
        string_append(caracteristique, SPORTS[i]);
        string_cat(res, contrainte_exactement_une_maison(caracteristique));

        if (i != 4)
            string_append(res, ") & (");
    }
    string_append(res, ")");
    return res;
}

/*
 * Construit et renvoie la contrainte « cette maison a exactement une
 * caractéristique de cette catégorie ».
 */
String* contrainte_unicite_par_categorie(const char** categorie, int maison) {
    String* res = new_string();
    char* i_as_str = malloc(2*sizeof(char));
    sprintf(i_as_str, "%d", maison);

    for (int j = 0; j < 5; j++) {
        string_append(res, "(");
        for (int i = 0; i < 5; i++) {
            if (i != j)
                string_append(res, "~");
            string_append(res, i_as_str);
            string_append(res, "_");
            string_append(res, categorie[i]);
            if (i != 4)
                string_append(res, " & ");
        }
        string_append(res, ")");
        if (j != 4)
            string_append(res, " | ");
    }

    return res;
}

/*
 * Construit et renvoie la contrainte « chaque maison a exactement une
 * caractéristique de chaque type ».
 */
String* contrainte_unicite_par_categorie_toutes_maisons() {
    String* res = new_string();
    for (int i = 1; i <= 5; i++) {
        string_append(res, "(");
        string_cat(res, contrainte_unicite_par_categorie(NATIONALITES, i));
        string_append(res, ") & (");
        string_cat(res, contrainte_unicite_par_categorie(COULEURS, i));
        string_append(res, ") & (");
        string_cat(res, contrainte_unicite_par_categorie(ANIMAUX, i));
        string_append(res, ") & (");
        string_cat(res, contrainte_unicite_par_categorie(BOISSONS, i));
        string_append(res, ") & (");
        string_cat(res, contrainte_unicite_par_categorie(SPORTS, i));
        string_append(res, ")");

        if (i != 5)
            string_append(res, " & ");
    }
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
    String* res = new_string();

    string_cat(res, contraintes_de_lenonce());
    string_append(res, " & ");
    string_cat(res, contrainte_unicite_toutes_caracteristiques());
    string_append(res, " & ");
    string_cat(res, contrainte_unicite_par_categorie_toutes_maisons());

    printf("%s\n", res->string);
    string_free(res);

    return 0;
}
