#!/usr/bin/env python3
# -*- coding=utf-8 -*-
from typing import SupportsIndex, Any


def taille(arbre: dict[str, list[str]], sommet: str) -> int:
    if sommet == "":
        return 0
    return 1 + taille(arbre, arbre[sommet][0]) + taille(arbre, arbre[sommet][1])


a = {'F':['B','G'],
     'B':['A','D'],
     'A':['',''],
     'D':['C','E'],
     'C':['',''],
     'E':['',''],
     'G':['','I'],
     'I':['','H'],
     'H':['','']}

assert taille(a, "F") == 9
assert taille(a, "B") == 5
assert taille(a, "I") == 2


def echange(tab: list[Any], i: SupportsIndex, j: SupportsIndex):
    '''Echange les éléments d'indice i et j dans le tableau tab.'''
    temp = tab[i]
    tab[i] = tab[j] 
    tab[j] = temp
    # ou bien tab[i], tab[j] = tab[j], tab[i]


def tri_selection(tab: list[int | float]):
    '''Trie le tableau tab dans l'ordre croissant
    par la méthode du tri par sélection.'''
    N = len(tab)
    for k in range(N): 
        imin = k
        i = k
        for i in range(k, N): 
            if tab[i] < tab[imin]: 
                imin = i
        echange(tab, k, imin)


tab: list[int | float] = [41, 55, 21, 18, 12, 6, 25]
tab_trié = sorted(tab.copy())
tri_selection(tab)
assert tab == tab_trié

import random
for i in range(100):
    tab = [random.randint(-100, 100) for _ in range(random.randint(0, 10))]
    tab_trié = sorted(tab.copy())
    tri_selection(tab)
    assert tab == tab_trié
