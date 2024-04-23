#!/usr/bin/env python3
# -*- coding=utf-8 -*-
# Recherche dichotomique
# Sous licence GNU GPL 3.0 ou ultérieur
# Voir <https://gnu.org/licences/>
import random


def recherche_dichotomique(val: int, tab: list[int], verbose: bool = False):
    """Recherche dichotomiquement une valeur entière dans un tableau d’entiers."""
    if len(tab) == 0:
        return -1
    début = 0
    fin = len(tab)-1
    milieu = (début + fin) // 2
    if verbose: print(début, milieu, fin)
    while début <= fin:
        milieu = (début + fin) // 2
        if tab[milieu] == val:
            return milieu
        if tab[milieu] < val:
            début = milieu + 1
        elif tab[milieu] > val:
            fin = milieu - 1
        if verbose: print(début, milieu, fin)
    return -1


def recherche_dichotomique_recursif_sous_liste(
    val: int, tab: list[int], verbose: bool = False, verbose_level: int = 0
) -> int:
    """Recherche dichotomiquement une valeur entière dans un tableau d’entiers.
    Méthode récursive, avec sous-liste."""
    if len(tab) == 1:
        if tab[0] == val: return 0
        else: return -1
    elif len(tab) == 0: return -1
    milieu = len(tab)//2
    if verbose:
        print(" "*verbose_level + f"{tab=}, {milieu=}, {tab[milieu:]=}, {tab[:milieu]=}")
    if tab[milieu] == val:
        return milieu
    if tab[milieu] < val:
        ajouter_milieu = True
        index_sous_liste = recherche_dichotomique_recursif_sous_liste(
            val, tab[milieu:], verbose, verbose_level+1
        )
    else:
        ajouter_milieu = False
        index_sous_liste = recherche_dichotomique_recursif_sous_liste(
            val, tab[:milieu], verbose, verbose_level+1
        )
    if index_sous_liste == -1:
        return -1
    if ajouter_milieu:
        return milieu + index_sous_liste
    return index_sous_liste


def recherche_dichotomique_recursif_indice(
        val: int, tab: list[int], index_start: int | None = None, index_end: int | None = None,
        verbose: bool = False, verbose_level: int = 0
) -> int:
    if len(tab) == 0: return -1
    if index_start is None: index_start = 0
    if index_end is None: index_end = len(tab)
    milieu = (index_start + index_end) // 2
    if tab[milieu] == val: return milieu
    if index_end-index_start <= 1: return -1
    if verbose:
        print(" "*verbose_level + f"{tab=}, {index_start=}, {index_end=}, {milieu=}, {tab[milieu:index_end]=}, {tab[index_start:milieu]=}")
    if tab[milieu] < val:
        idx = recherche_dichotomique_recursif_indice(
            val, tab, milieu, index_end, verbose, verbose_level+1
        )
    else:
        idx = recherche_dichotomique_recursif_indice(
            val, tab, index_start, milieu, verbose, verbose_level+1
        )
    return idx


tests: list[tuple[int, list[int], int]] = [
    (14, [1, 2, 5, 8, 90, 125], -1),
    (14, [1, 2, 5, 8, 9, 90, 125], -1),
    (14, [1, 2, 5, 8, 14, 90, 125], 4),
    (14, [1, 2, 5, 8, 13, 14, 90, 125], 5),
    (14, [1, 2, 5, 8, 14, 15, 90, 125], 4),
    (125, [1, 2, 5, 8, 14, 15, 90, 125], 7),
    (125, [1, 2, 5, 8, 14, 90, 125], 6),
    (1, [1, 2, 5, 8, 14, 90, 125], 0),
    (1, [1], 0),
    (125, [1], -1),
    (125, [1, 125], 1),
    (125, [], -1),
]


for idx, (val, tab, expected_result) in enumerate(tests):
    assert recherche_dichotomique(val, tab) == expected_result, (val, tab, expected_result, idx)
    assert recherche_dichotomique_recursif_sous_liste(val, tab) == expected_result, (val, tab, expected_result, idx)
    assert recherche_dichotomique_recursif_indice(val, tab) == expected_result, (val, tab, expected_result, idx)


for _ in range(100):
    tab_random = [random.randint(0, 2000) for _ in range(1000)]
    tab_random.sort()
    value = random.randint(0, 2000)
    if value not in tab_random:
        assert recherche_dichotomique(value, tab_random) == -1
        assert recherche_dichotomique_recursif_sous_liste(value, tab_random) == -1
        assert recherche_dichotomique_recursif_indice(value, tab_random) == -1
    else:
        idx = recherche_dichotomique(value, tab_random)
        idx2 = recherche_dichotomique_recursif_sous_liste(value, tab_random)
        idx3 = recherche_dichotomique_recursif_indice(value, tab_random)
        assert tab_random[idx] == value
        assert tab_random[idx2] == value
        assert tab_random[idx3] == value
