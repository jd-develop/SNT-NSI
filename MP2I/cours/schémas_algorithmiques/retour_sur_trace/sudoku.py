#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from pprint import pprint

# GRILLE: list[list[int | None]] = [[None]*9 for _ in range(9)]


GRILLE = [
    [None, None, None, None, None, None, None,    4, None],
    [   4, None, None, None,    1,    8, None, None, None],
    [None,    6,    2, None, None, None,    5, None,    3],

    [   2, None,    3, None,    5, None, None, None, None],
    [None,    5, None, None, None,    4, None,    1,    8],
    [   8, None,    9, None,    6, None, None, None, None],

    [None,    2,    1, None, None, None,    3, None,    4],
    [   6, None, None, None,    4,    1, None, None, None],
    [None, None, None, None, None, None, None,    5, None]
]


def check(grille: list[list[int | None]]):
    for ligne in grille:
        occurences = {i: 0 for i in range(1, 10)}
        for i in ligne:
            if i is None: continue
            if occurences[i] == 0:
                occurences[i] = 1
            else:
                return False

    for j in range(9):
        occurences = {i: 0 for i in range(1, 10)}
        for i in range(9):
            valeur = grille[i][j]
            if valeur is None: continue
            if occurences[valeur] == 0:
                occurences[valeur] = 1
            else:
                return False

    for offset_i in range(3):
        for offset_j in range(3):
            occurences = {i: 0 for i in range(1, 10)}
            for i in range(3):
                for j in range(3):
                    valeur = grille[3*offset_i+i][3*offset_j+j]
                    if valeur is None: continue
                    if occurences[valeur] == 0:
                        occurences[valeur] = 1
                    else:
                        return False

    return True


def est_plein(grille: list[list[int | None]]):
    for i in range(9):
        for j in range(9):
            if grille[i][j] is None:
                return False, i, j
    return True, 0, 0


def backtrack(grille: list[list[int | None]]):
    #pprint(grille)
    if not check(grille):
        return None
    plein, i, j = est_plein(grille)
    if plein:
        return grille

    for n in range(1, 10):
        grille_2 = [l.copy() for l in grille]
        grille_2[i][j] = n
        b = backtrack(grille_2)
        if b is not None:
            return b
    return None


pprint(backtrack(GRILLE))
