#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import time
from utils import afficher_grille


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


def print_grille(grille: list[list[int | None]] | None, highlight: tuple[int, int] | None = None):
    if grille is None:
        print("Pas de solutions !")
        return
    if highlight is None:
        hi, hj = (-1, -1)
    else:
        hi, hj = highlight
    print("┏━┯━┯━┳━┯━┯━┳━┯━┯━┓")
    for i, ligne in enumerate(grille):
        print("┃", end="")
        for j, case in enumerate(ligne):
            if hi == i and hj == j:
                print("X", end="│" if j%3 != 2 else "┃")
            else:
                print(case if case is not None else " ", end="│" if j%3 != 2 else "┃")
        print()
        if i == len(grille)-1:
            print("┗━┷━┷━┻━┷━┷━┻━┷━┷━┛")
        elif i%3 == 2:
            print("┣━┿━┿━╋━┿━┿━╋━┿━┿━┫")
        else:
            print("┠─┼─┼─╂─┼─┼─╂─┼─┼─┨")


def backtrack(grille: list[list[int | None]]) -> list[list[int | None]] | None:
    afficher_grille(grille)
    time.sleep(1/1000)
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


print("\x1bc")
grille: list[list[int | None]] = [[None]*9 for _ in range(9)]
for i in range(9):
    for j in range(9):
        afficher_grille(grille, (i, j))
        case = input()
        if len(case) == 1 and 0x31 <= ord(case) <= 0x39:
            grille[i][j] = ord(case)-0x30


afficher_grille(backtrack(grille))
print("\x1b[?25h")
