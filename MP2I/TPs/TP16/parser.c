#include "parser.h"
#include "graphe.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

graphe_t* lire_graphe(char* filename){
    FILE* f = fopen(filename, "r");

    // nombre de sommets et d'arêtes
    int n, m;
    fscanf(f, "%d %d", &n, &m);
    fscanf(f, "\n");

    // lecture des sommets
    char** sommets = malloc(n*sizeof(char*));
    for (int i = 0; i < n; ++i)
    {
        sommets[i] = NULL;
        size_t mem_size=0;
        int l = getline(&sommets[i], &mem_size, f);
        // enlever l'éventuel retour à la ligne
        if (sommets[i][l-1] == '\n'){
            sommets[i][l-1] = '\0';
        }
    }

    graphe_t* g = graphe_vide(sommets, n);

    // lecture des arêtes
    char* ligne = NULL; // pour stocker la ligne lue
    size_t mem_size=0; // taille de la ligne lue (nécessaire pour utiliser getline)
    for (int j = 0; j < m; ++j)
    {
        int l = getline(&ligne, &mem_size, f);
        // printf("[%s]\n", ligne);
        if (l < 0){
            perror("A l'aide");
            exit(1);
        }
        if (ligne[l-1] == '\n'){
            ligne[l-1] = '\0';
        }

        // chercher les positions des deux signes $
        int fst_dollar=-1, snd_dollar=-1;
        for (int i = 0; i < l; ++i)
        {
            if (ligne[i] == '$'){
                if (fst_dollar == -1){
                    fst_dollar = i;
                } else {
                    assert(snd_dollar == -1);
                    snd_dollar = i;
                    break;
                }
            }
        }
        assert(fst_dollar >= 0 && snd_dollar >= 0);

        // plutôt que de recopier les trois parties de la ligne dans des chaînes à part,
        // on remplace les $ par des caractères nuls. On a alors coupé ligne en 3 parties:
        // partie de u \0 partie de v \0 partie du poids de l'arête \0.
        // De plus, 0, fst_dollar+1 et snd_dollar+1 indiquent l'adresse de début de chacune 
        // des trois chaînes.
        ligne[fst_dollar] = '\0';
        ligne[snd_dollar] = '\0';

        char* u = ligne;
        char* v = ligne+fst_dollar+1;
        float w = atof(ligne+snd_dollar+1); // atof: transforme un string en flottant

        ajouter_arc(g, u, v, w);
    }
    free(ligne);

    fclose(f);
    return g;
}
