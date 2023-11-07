#!/usr/bin/env python3
# -*- coding:utf-8 -*-
"""
Compléter le code ci-dessous :
"""
coeur = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
         [0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0],
         [0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0],
         [0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0],
         [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
         [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
         [0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
         [0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0],
         [0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0],
         [0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0],
         [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
         [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]


def affiche(dessin):
    """
    Affichage d'une grille : les 1 sont représentés par
    des " *", les 0 par deux espaces " ".
    La valeur "" donnée au paramètre end permet de ne pas avoir
    de saut de ligne.
    """
    for ligne in dessin:
        for col in ligne:
            if col == 1:
                print(" *", end="")
            else:
                print("  ", end="")
        print()


def zoomListe(liste_depart, k):
    """Renvoie une liste contenant k fois chaque élément de liste_depart"""
    liste_zoom = []
    for element in liste_depart:
        for i in range(k):
            liste_zoom.append(element)
    return liste_zoom


def zoomDessin(grille, k):
    """Renvoie une grille où les lignes sont zoomées k fois ET répétées k fois"""
    grille_zoom = []
    for element in grille:
        liste_zoom = zoomListe(element, k)
        for i in range(k):
            grille_zoom.append(liste_zoom.copy())
    return grille_zoom


# print("affiche(coeur)")
# affiche(coeur)
# print()
# print("affiche(zoomDessin(coeur, 3))")
# affiche(zoomDessin(coeur, 3))


"""
Résultats à obtenir :
>>> affiche(coeur)

       * *       * *
     *     *   *     *
   *         *         *
   *                   *
   *                   *
     *               *
       *           *
         *       *
           *   *
             *

>>> affiche(zoomDessin(coeur, 3))



                   * * * * * *                   * * * * * *
                   * * * * * *                   * * * * * *
                   * * * * * *                   * * * * * *
             * * *             * * *       * * *             * * *
             * * *             * * *       * * *             * * *
             * * *             * * *       * * *             * * *
       * * *                         * * *                         * * *
       * * *                         * * *                         * * *
       * * *                         * * *                         * * *
       * * *                                                       * * *
       * * *                                                       * * *
       * * *                                                       * * *
       * * *                                                       * * *
       * * *                                                       * * *
       * * *                                                       * * *
             * * *                                           * * *
             * * *                                           * * *
             * * *                                           * * *
                   * * *                               * * *
                   * * *                               * * *
                   * * *                               * * *
                         * * *                   * * *
                         * * *                   * * *
                         * * *                   * * *
                               * * *       * * *
                               * * *       * * *
                               * * *       * * *
                                     * * *
                                     * * *
                                     * * *




"""