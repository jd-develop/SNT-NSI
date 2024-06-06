#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import random

voisins = [
    [1, 2, 3, 4, 5],
    [0, 2, 3],
    [0, 1, 5],
    [0, 1],
    [0, 2, 3],
    [0, 2]
]


def voisin_aléa(voisins: list[list[int]], s: int):
    return voisins[s][random.randrange(len(voisins[s]))]


def marche_aléa(voisins: list[list[int]], i: int, n: int) -> int:
    if n == 0:
        return i
    return marche_aléa(voisins, voisin_aléa(voisins, i), n-1)


def simule(voisins: list[list[int]], i: int, n_tests: int, n_pas: int):
    result = [0]*len(voisins)
    for _ in range(n_tests):
        result[marche_aléa(voisins, i, n_pas)] += 1

    return [i/n_tests for i in result]


def temps_pour_infecter_réseau(voisins: list[list[int]], i: int):
    """ i est le sommet de départ """
    voisins_infectés: list[int] = [i]
    n = 0
    while len(voisins_infectés) != len(voisins):
        n += 1
        for j in voisins_infectés:
            for voisin in voisins[j]:
                if voisin not in voisins_infectés:
                    voisins_infectés.append(voisin)
    return n
