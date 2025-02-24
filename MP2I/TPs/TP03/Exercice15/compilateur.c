/*
 * Note : je n’ai pas eu le temps d’implémenter toutes les fonctionnalités
 * que je voulais (mais toutes celles qui sont indiquées ci-dessous sont
 * implémentées).
 *
 * Il manque également quelques tests.
 *
 * Je vais sûrement continuer à ajouter les tests manquants mais aussi
 * l’étoffer après le 30 : j’ai plusieurs idées de sucre syntaxique à ajouter.
 * Je vais peut-être aussi réécrire l’exo 9 pour pouvoir mettre des boucles, ou
 * des go to.
 */

/*
 * Ce programme est un compilateur pour créer des programmes machines
 * exécutables par l’exercice 9
 *
 * Lit un fichier, écrit le code machine dans stdout, écrit les erreurs dans
 * stderr
 *
 * Renvoie 0 si tout s’est bien passé, ou bien :
 * * -2 en cas d’utilisation d’un identifiant non défini
 * * -1 en cas de dépassement de la capacité de la mémoire
 * * 1 en cas de fichier introuvable ou sans les permissions d’écriture
 * * 2 si aucun fichier n’a été passé en argument
 * * 3 si une des lignes du fichier fait + de 100 caractères
 * * 4 en cas d’erreur de syntaxe
 *
 * Le langage compilé, inventé pour l’occasion et nommé Yet Another Stupid
 * Language, est en notation préfixée
 *
 * Syntaxe du langage :
 *      Les commentaires commencent par # et terminent par un retour-ligne
 *      Les littéraux sont :
 *          * int : un nombre
 *          * char : un caractère (ex: 'c')
 *      = identifiant valeur
 *      = identifiant identifiant2
 *          assigne la valeur `valeur` à l’identifiant `identifiant`, ou copie
 *          la valeur de `identifiant2` dans `identifiant`
 *      =+ identifiant1 identifiant2 identifiant3 (ou valeur2 valeur3)
 *          assigne la somme `identifiant2+identifiant3` à l’identifiant
 *          `identifiant1`
 *      =* identifiant1 identifiant2 identifiant3 (ou valeur2 valeur3)
 *          assigne le produit `identifiant2*identifiant3` à l’identifiant
 *          `identifiant1`
 *      =% identifiant1 identifiant2 identifiant3 (ou valeur2 valeur3)
 *          assigne le modulo `identifiant2%identifiant3` à l’identifiant
 *          `identifiant1`
 *      =/ identifiant1 identifiant2 identifiant3 (ou valeur2 valeur3)
 *          assigne le quotient (entier) `identifiant2/identifiant3` à
 *          l’identifiant `identifiant1`
 *      . valeur
 *      . identifiant
 *          affiche une valeur ou un identifiant
 *      : valeur
 *      : identifiant
 *          affiche le caractère ASCII correspondant à la valeur ou
 *          l’identifiant
 *      ;
 *          affiche un retour-ligne
 *      !
 *          arrête le programme (pas obligatoire en fin de fichier)
 */
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define TAILLE_MAX_ID 100  // limite de 100 caractères pour un identifiant
#define TAILLE_MAX_LIGNE 100  // limite de 100 caractères pour une ligne

/* Affiche l’en-tête d’une erreur dans stderr */
void affiche_en_tete_erreur(int numero_ligne) {
    fprintf(stderr, "Error: line %d: ", numero_ligne);
}

/* Affiche une erreur de syntaxe dans stderr */
void erreur_syntaxe(int numero_ligne) {
    affiche_en_tete_erreur(numero_ligne);
    fprintf(stderr, "syntax error\n");
}

/*
 * Renvoie l’adresse dans [0, 1023] de l’identifiant `identifiant`, à l’aide
 * du tableau de symboles `tab_symboles`.
 *
 * Si `definition` est à `true`, crée éventuellement un nouvel identifiant dans
 * le tableau de symboles, ou renvoie -1 s’il n’y avait plus de place.
 *
 * Si `definition` est à false et que l’identifiant n’est pas dans le tableau
 * de symboles, renvoie -2.
 *
 * En cas d’erreur, écrit l’erreur dans stderr : on a besoin du numéro de
 * la ligne dans numero_ligne pour afficher un message d’erreur utile.
 * L’erreur n’est pas affichée si `quiet` est à `true`.
 *
 * Note : dans le tableau de symboles, un espace libre est signalé par la
 * chaîne "" ('\0'), et un espace réservé est signalé par la chaîne
 * "(reserve)"
 */
int id_vers_adresse(
        char* identifiant, char (*tab_symboles)[TAILLE_MAX_ID],
        bool definition, int numero_ligne, bool quiet
) {
    int i = 0;
    int premiere_case_vide = 1024;

    for (; i <= 1023; i++) {
        if (strcmp(identifiant, tab_symboles[i]) == 0)
            return i;
        if (premiere_case_vide == 1024 && strcmp("", tab_symboles[i]) == 0)
            premiere_case_vide = i;
    }

    if (i == 1024) {  // non défini
        if (!definition) {
            if (!quiet) {
                affiche_en_tete_erreur(numero_ligne);
                fprintf(stderr, "%s is undefined\n", identifiant);
            }
            return -2;
        }
        if (premiere_case_vide == 1024) {
            if (!quiet) {
                affiche_en_tete_erreur(numero_ligne);
                fprintf(stderr, "memory capacity exceeded\n");
            }
            return -1;
        }
        strcpy(tab_symboles[premiere_case_vide], identifiant);
        return premiere_case_vide;
    }

    return i;  /* en principe cette ligne ne s’exécute jamais, mais GCC râle
                * si on ne la met pas (-Wall -Wextra -Werror --pedantic-errors)
                */
}

/*
 * Initialise tab_symboles avec des symboles vides.
 */
void initialiser_tab_symboles(char (*tab_symboles)[TAILLE_MAX_ID]) {
    int i;
    for (i = 0; i <= 1023; i++) {
        strcpy(tab_symboles[i], "");
    }
}

/*
 * Réserve l’espace mémoire d’indice i pour autre chose qu’une variable. Ne
 * vérifie pas qu’un espace mémoire est libre.
 */
void reserver_espace_memoire(char (*tab_symboles)[TAILLE_MAX_ID], int i) {
    assert(0 <= i && i < 1024);
    strcpy(tab_symboles[i], "(reserve)");
}

/*
 * teste les fonctions id_vers_adresse, initialiser_tab_symboles et
 * reserver_espace_memoire
 */
void teste_id_vers_adresse_init_reserver() {
    char tab_symboles[1024][TAILLE_MAX_ID];
    int i;
    initialiser_tab_symboles(tab_symboles);
    for (i = 0; i <= 1023; i++) {
        assert(strcmp(tab_symboles[i], "") == 0);
    }
    reserver_espace_memoire(tab_symboles, 12);
    assert(strcmp(tab_symboles[12], "(reserve)") == 0);

    assert(id_vers_adresse("a", tab_symboles, false, 1, true) == -2);
    assert(id_vers_adresse("a", tab_symboles, true, 1, true) == 0);
    assert(strcmp(tab_symboles[0], "a") == 0);
    assert(id_vers_adresse("a", tab_symboles, true, 1, true) == 0);

    assert(id_vers_adresse("b", tab_symboles, true, 1, true) == 1);
    assert(id_vers_adresse("c", tab_symboles, true, 1, true) == 2);
    assert(id_vers_adresse("d", tab_symboles, true, 1, true) == 3);
    assert(id_vers_adresse("e", tab_symboles, true, 1, true) == 4);
    assert(id_vers_adresse("f", tab_symboles, true, 1, true) == 5);
    assert(id_vers_adresse("g", tab_symboles, true, 1, true) == 6);
    assert(id_vers_adresse("h", tab_symboles, true, 1, true) == 7);
    assert(id_vers_adresse("i", tab_symboles, true, 1, true) == 8);
    assert(id_vers_adresse("j", tab_symboles, true, 1, true) == 9);
    assert(id_vers_adresse("k", tab_symboles, true, 1, true) == 10);
    assert(id_vers_adresse("l", tab_symboles, true, 1, true) == 11);
    assert(id_vers_adresse("m", tab_symboles, true, 1, true) == 13);
    for (i = 14; i <= 1022; i++) {
        reserver_espace_memoire(tab_symboles, i);
        assert(strcmp(tab_symboles[i], "(reserve)") == 0);
    }
    assert(id_vers_adresse("n", tab_symboles, true, 1, true) == 1023);
    assert(id_vers_adresse("o", tab_symboles, true, 1, true) == -1);
}

/* Regarde s’il y a un identifiant sur la ligne `ligne` de longueur `len_ligne`
 * à partir du caractère d’indice la valeur pointée par `c`. S’il y en a un,
 * renvoie 0 et le stocke dans `identifiant`. Sinon, renvoie 1
 */
int enregistrer_identifiant(
    char* identifiant, char* ligne, int len_ligne, int* c
) {
    strcpy(identifiant, "");
    int pos_depart = *c;
    for (; *c < TAILLE_MAX_ID && *c < len_ligne; (*c)++) {
        if (
            ('a' <= ligne[*c] && ligne[*c] <= 'z') ||
            ('A' <= ligne[*c] && ligne[*c] <= 'Z') ||
            ligne[*c] == '_'
        ) {
            identifiant[*c-pos_depart] = ligne[*c];
        } else if ('0' <= ligne[*c] && ligne[*c] <= '9') {
            if (*c == pos_depart)
                return 1;
            identifiant[*c-pos_depart] = ligne[*c];
        } else {
            if (*c == pos_depart)
                return 1;
            break;
        }
    }
    if (strlen(identifiant) == 0)
        return 1;
    return 0;
}

/* Regarde s’il y a une valeur (int ou char) sur la ligne `ligne` de longueur
 * `len_ligne` à partir du caractère d’indice la valeur pointée par `c`. S’il y
 * en a une, renvoie 0 et la stocke dans la valeur pointée par `valeur`. Sinon,
 * renvoie 1
 */
int enregistrer_valeur(int* valeur, char* ligne, int len_ligne, int* c) {
    int pos_depart = *c;
    int valeur_en_cours_denregistrement = 0;
    int negatif = 1;

    if (ligne[*c] == '\'') {  // caractère
        (*c)++;
        if (*c == len_ligne)
            return 1;

        char chr = ligne[*c];
        (*c)++;
        if (*c == len_ligne || ligne[*c] != '\'')
            return 1;
        (*c)++;

        *valeur = (int)chr;
        return 0;
    }

    // nombre
    if (ligne[*c] == '-') {
        negatif = -1;
        pos_depart++;
        (*c)++;
    }
    for (; *c < len_ligne && ligne[*c] != ' '; (*c)++) {
        if ('0' <= ligne[*c] && ligne[*c] <= '9') {
            valeur_en_cours_denregistrement *= 10;
            valeur_en_cours_denregistrement += ligne[*c]-0x30;
        } else {
            break;
        }
    }
    if (valeur_en_cours_denregistrement == 0 && *c == pos_depart) {
        return 1;
    }
    *valeur = negatif * valeur_en_cours_denregistrement;
    return 0;
}

/*
 * Traite un égale sur la ligne `ligne` de numéro `numero_ligne`, de longueur
 * `len_ligne` à partir du caractère d’indice la valeur pointée par `c`.
 * Nécessite la table des symboles `tab_symboles`
 * Renvoie :
 * * 0 si tout s’est bien passé
 * * -1 en cas de dépassement de la capacité de la mémoire
 * * -2 en cas d’identifiant non défini
 * * 4 en cas d’erreur de syntaxe
 */
int egale(char* ligne, int numero_ligne, int* c, int len_ligne,
          char (*tab_symboles)[TAILLE_MAX_ID]) {
    int adresse_id;
    int adresse_id2;
    int adresse_id3;
    (*c)++;
    if (*c == len_ligne) {
        erreur_syntaxe(numero_ligne);
        return 4;
    }

    int equal_type;
    /* types d’égal :
     * 0  : assignation (=)
     * 3  : addition (=+)
     * 5  : multiplication (=*)
     * 9  : modulo (=%)
     * 10 : division (=/)
     */
    if (ligne[*c] == '+') {
        equal_type = 3;
        (*c)++;
    } else if (ligne[*c] == '*') {
        equal_type = 5;
        (*c)++;
    } else if (ligne[*c] == '/') {
        equal_type = 10;
        (*c)++;
    } else if (ligne[*c] == '%') {
        equal_type = 9;
        (*c)++;
    } else if (ligne[*c] == ' ') {
        equal_type = 0;
    } else {
        erreur_syntaxe(numero_ligne);
        return 4;
    }

    if (*c == len_ligne || ligne[*c] != ' ') {
        erreur_syntaxe(numero_ligne);
        return 4;
    }
    (*c)++;
    if (*c == len_ligne) {
        erreur_syntaxe(numero_ligne);
        return 4;
    }

    char identifiant[TAILLE_MAX_ID] = "";
    if (enregistrer_identifiant(identifiant, ligne, len_ligne, c) == 1) {
        erreur_syntaxe(numero_ligne);
        return 4;
    }

    adresse_id = id_vers_adresse(identifiant, tab_symboles, true, numero_ligne,
                                 false);
    if (adresse_id < 0) {
        return adresse_id;
    }

    if (*c == len_ligne || ligne[*c] != ' ') {
        erreur_syntaxe(numero_ligne);
        return 4;
    }
    (*c)++;
    if (*c == len_ligne) {
        erreur_syntaxe(numero_ligne);
        return 4;
    }

    if (('a' <= ligne[*c] && ligne[*c] <= 'z') ||
        ('A' <= ligne[*c] && ligne[*c] <= 'Z') ||
        (ligne[*c] == '_'))
    {
        char identifiant2[TAILLE_MAX_ID] = "";
        if (enregistrer_identifiant(identifiant2, ligne, len_ligne, c) == 1) {
            erreur_syntaxe(numero_ligne);
            return 4;
        }

        adresse_id2 = id_vers_adresse(
            identifiant2, tab_symboles, false, numero_ligne, false
        );
        if (adresse_id2 < 0) {
            return adresse_id2;
        }
        if (equal_type == 0) {
            printf("2 0 0 3 0 %d %d\n", adresse_id2, adresse_id);
            return 0;
        }
    } else {
        int valeur2;
        if (enregistrer_valeur(&valeur2, ligne, len_ligne, c) == 1) {
            erreur_syntaxe(numero_ligne);
            return 4;
        }

        if (equal_type == 0) {
            printf("2 %d %d\n", adresse_id, valeur2);
            return 0;
        }

        // on stocke la valeur à l’adresse 0, puis on additionne l’adresse 0
        // avec l’adresse du premier identifiant
        printf("2 0 %d\n", valeur2);
        adresse_id2 = 0;
    }

    (*c)++;
    if (*c == len_ligne) {
        erreur_syntaxe(numero_ligne);
        return 4;
    }

    if (('a' <= ligne[*c] && ligne[*c] <= 'z') ||
        ('A' <= ligne[*c] && ligne[*c] <= 'Z') ||
        (ligne[*c] == '_'))
    {
        char identifiant3[TAILLE_MAX_ID] = "";
        if (enregistrer_identifiant(identifiant3, ligne, len_ligne, c) == 1) {
            erreur_syntaxe(numero_ligne);
            return 4;
        }

        adresse_id3 = id_vers_adresse(
            identifiant3, tab_symboles, false, numero_ligne, false
        );
        if (adresse_id3 < 0) {
            return adresse_id3;
        }

    } else {
        // pas un identifiant : valeur
        int valeur3;
        if (enregistrer_valeur(&valeur3, ligne, len_ligne, c) == 1) {
            erreur_syntaxe(numero_ligne);
            return 4;
        }
        // on stocke la valeur à l’adresse 1, puis on additionne l’adresse 1
        // avec l’adresse du premier identifiant
        printf("2 1 %d\n", valeur3);
        adresse_id3 = 1;
    }
    printf("%d %d %d %d\n", equal_type, adresse_id2, adresse_id3,
            adresse_id);
    return 0;
}

/*
 * Affiche la valeur ou l’identifiant se trouvant après le caractère d’indice
 * la valeur pointée dar `c` sur la ligne `ligne` numéro `numero_ligne`
 * de longueur `len_ligne`.
 * Nécessite la table des symboles `tab_symboles`
 * Renvoie :
 * * 0 si tout s’est bien passé
 * * -2 en cas d’identifiant non défini
 * * 4 en cas d’erreur de syntaxe
 */
int affiche(char* ligne, int numero_ligne, int* c, int len_ligne,
            char (*tab_symboles)[TAILLE_MAX_ID]) {
    bool affiche_caractere;
    int adresse_id;

    if (ligne[*c] == '.') {
        affiche_caractere = false;
    } else if (ligne[*c] == ':') {
        affiche_caractere = true;
    } else {
        erreur_syntaxe(numero_ligne);
        return 4;
    }

    do {
        (*c)++;
        if (*c == len_ligne) {
            erreur_syntaxe(numero_ligne);
            return 4;
        }
    } while (ligne[*c] == ' ');

    if (('a' <= ligne[*c] && ligne[*c] <= 'z') ||
        ('A' <= ligne[*c] && ligne[*c] <= 'Z') ||
        (ligne[*c] == '_'))
    {
        char identifiant[TAILLE_MAX_ID] = "";
        if (enregistrer_identifiant(identifiant, ligne, len_ligne, c) == 1) {
            erreur_syntaxe(numero_ligne);
            return 4;
        }

        adresse_id = id_vers_adresse(
            identifiant, tab_symboles, true, numero_ligne, false
        );
        if (adresse_id < 0) {
            return adresse_id;
        }
    } else {
        // pas un identifiant : valeur
        int valeur;
        if (enregistrer_valeur(&valeur, ligne, len_ligne, c) == 1) {
            erreur_syntaxe(numero_ligne);
            return 4;
        }
        // on stocke la valeur à l’adresse 0, puis on additionne l’adresse 0
        // avec l’adresse du premier identifiant
        printf("2 0 %d\n", valeur);
        adresse_id = 0;
    }
    if (affiche_caractere) {
        printf("8 %d\n", adresse_id);
    } else {
        printf("7 %d\n", adresse_id);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    /* TESTS */
    teste_id_vers_adresse_init_reserver();
    /* ----- */

    FILE *fptr;
    char tab_symboles[1024][TAILLE_MAX_ID];
    char ligne[TAILLE_MAX_LIGNE];
    int numero_ligne = 0;
    int len_ligne;
    int c;
    bool comment;
    int resultat;

    if (argc > 1) {
        fptr = fopen(argv[1], "r+");
    } else {
        fprintf(stderr, "Error: no file provided\n");
        return 2;
    }
    if (fptr == NULL) {
        fprintf(stderr, "Error: unable to open file: %s\n", argv[1]);
        return 1;
    }

    initialiser_tab_symboles(tab_symboles);
    // on réserve les cases 0 et 1 pour d’éventuels calculs rapides
    reserver_espace_memoire(tab_symboles, 0);
    reserver_espace_memoire(tab_symboles, 1);
    printf("1024\n"); // taille de la mémoire

    while (fgets(ligne, TAILLE_MAX_LIGNE, fptr)) {
        numero_ligne++;
        len_ligne = strlen(ligne);
        if (len_ligne == 99 && ligne[99] != '\n') {
            affiche_en_tete_erreur(numero_ligne);
            fprintf(stderr, "please limit lines to %d characters\n",
                    TAILLE_MAX_LIGNE);
            return 3;
        }

        comment = false;
        for (c = 0; c < len_ligne; c++) {
            if (ligne[c] == '#') {
                comment = true;
                break;
            } else if (ligne[c] == '\n' || ligne[c] == ' ') {
                continue;
            } else if (ligne[c] == ';') { // affiche un retour-ligne
                printf("2 0 10 8 0\n");
            } else if (ligne[c] == '!') { // termine le programme : affiche '4'
                printf("4\n");
            } else if (ligne[c] == '.') {
                resultat = affiche(ligne, numero_ligne, &c, len_ligne,
                                   tab_symboles);
                if (resultat != 0)
                    return resultat;
                c--;  // on a avancé d’un caractère de trop
            } else if (ligne[c] == ':') {
                resultat = affiche(ligne, numero_ligne, &c, len_ligne,
                                   tab_symboles);
                if (resultat != 0)
                    return resultat;
                c--;  // on a avancé d’un caractère de trop
            } else if (ligne[c] == '=') { // un signe égale
                resultat = egale(ligne, numero_ligne, &c, len_ligne,
                                 tab_symboles);
                if (resultat != 0)
                    return resultat;
                c--;  // on a avancé d’un caractère de trop
            } else {
                affiche_en_tete_erreur(numero_ligne);
                fprintf(
                    stderr,
                    "unknown char %c in this context\n", ligne[c]
                );
                return 4;
            }
        }
        if (comment)
            continue;

    }
    printf("4\n");
    return 0;
}

