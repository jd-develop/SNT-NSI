#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# This document is licensed under the GNU-GPL v3 or later.

def recherche_dichotomique(liste_triée: list[int | float], valeur_cherchée: int | float):
    if len(liste_triée) == 0:
        return None
    if valeur_cherchée not in liste_triée:
        return None
    index1 = 0
    index2 = len(liste_triée)
    milieu = (index1 + index2) // 2
    while liste_triée[milieu] != valeur_cherchée:
        milieu = (index1 + index2) // 2
        if liste_triée[milieu] < valeur_cherchée:
            index1 = milieu
        else:
            index2 = milieu
    return milieu


assert recherche_dichotomique([-1, 0, 6, 25], 6) == 2
assert recherche_dichotomique([-1, 0, 6, 25], 25) == 3
assert recherche_dichotomique([-1, 0, 6, 25, 60], 6) == 2
assert recherche_dichotomique([-1, 0, 6, 25, 60], 25) == 3
assert recherche_dichotomique([-1, 0, 6, 25, 60], 60) == 4
assert recherche_dichotomique([], 123) == None
assert recherche_dichotomique([1], 123) == None
assert recherche_dichotomique([1], 1) == 0


def recherche_dichotomique_récursive(liste_triée: list[int | float], valeur_cherchée: int | float, index_départ: int = 0, index_max: int = -1) -> int | None:
    if len(liste_triée) == 0:
        return None
    if valeur_cherchée not in liste_triée:
        return None
    if liste_triée[index_départ] == valeur_cherchée:
        return index_départ
    if index_max == -1:
        index_max = len(liste_triée) - 1
    milieu = (index_départ + index_max) // 2
    if liste_triée[milieu] < valeur_cherchée:
        return recherche_dichotomique_récursive(liste_triée, valeur_cherchée, milieu+1, index_max)
    else:
        return recherche_dichotomique_récursive(liste_triée, valeur_cherchée, index_départ, milieu)


assert recherche_dichotomique_récursive([-1, 0, 6, 25], 6) == 2
assert recherche_dichotomique_récursive([-1, 0, 6, 25], 25) == 3
assert recherche_dichotomique_récursive([-1, 0, 6, 25, 60], 6) == 2
assert recherche_dichotomique_récursive([-1, 0, 6, 25, 60], 25) == 3
assert recherche_dichotomique_récursive([-1, 0, 6, 25, 60], 60) == 4
assert recherche_dichotomique_récursive([], 123) == None
assert recherche_dichotomique_récursive([1], 123) == None
assert recherche_dichotomique_récursive([1], 1) == 0
