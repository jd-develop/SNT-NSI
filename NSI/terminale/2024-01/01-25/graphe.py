#!/usr/bin/env python3
# -*- coding=utf-8 -*-
"""
Consigne :
Un graphe est donné sous la forme d’un dictionnaire de voisins.

Écrire 3 fonctions :
est_connexe -> bool
possede_un_cycle -> bool
cycle_eulerien -> bool[False] | liste des nœuds
"""

graphe_connexe_cyclique = {
    1: [2, 3],
    2: [1, 4],
    3: [1, 4],
    4: [2, 3]
}

graphe_connexe_non_cyclique = {
    1: [2, 3],
    2: [1],
    3: [1, 4],
    4: [3]
}

graphe_cyclique_non_connexe = {
    1: [2],
    2: [1],
    3: [4, 5],
    4: [3, 5],
    5: [3, 4]
}

grahpe_cyclique_non_hamiltonien = {
    1: [2, 2, 3],
    2: [1, 1, 3, 4, 4],
    3: [1, 2, 4],
    4: [2, 2, 3]
}


arbre = {
    1: [2, 3, 4],
    2: [1, 5, 6],
    3: [1, 9, 10],
    4: [1, 14, 15],
    5: [2],
    6: [2, 7, 8],
    7: [6],
    8: [6],
    9: [3, 11],
    10: [3],
    11: [9, 12, 13],
    12: [11],
    13: [11],
    14: [4, 16],
    15: [4],
    16: [14]
}

pseudo_arbre = {
    1: [2, 3, 4],
    2: [1, 5, 6],
    3: [1, 9, 10],
    4: [1, 14, 15],
    5: [2],
    6: [2, 7, 8],
    7: [6],
    8: [6],
    9: [3, 11],
    10: [3],
    11: [9, 12, 13],
    12: [11, 15],
    13: [11],
    14: [4, 16],
    15: [4, 12],
    16: [14]
}

foret = {
    2: [5, 6],
    3: [9, 10],
    4: [14, 15],
    5: [2],
    6: [2, 7, 8],
    7: [6],
    8: [6],
    9: [3, 11],
    10: [3],
    11: [9, 12, 13],
    12: [11, 15],
    13: [11],
    14: [4, 16],
    15: [4, 12],
    16: [14]
}


def parcours(graphe: dict[int, list[int]], sommet_depart: int = 1):
    file = [sommet_depart]
    deja_visites: list[int] = []
    while len(file) != 0:
        sommet_courant = file.pop(0)
        if sommet_courant in deja_visites:
            continue
        deja_visites.append(sommet_courant)
        file.extend(graphe[sommet_courant])
    return deja_visites


# print(parcours(grahpe_cyclique_non_hamiltonien))
# print(parcours({"A": ["E"], "B": ["E"], "C": ["E"], "D": ["E"], "E": ["A","B","C","D"]}, "A"))


def est_connexe(graphe: dict[int, list[int]], sommet_depart: int = 1):
    parcours_graphe = parcours(graphe, sommet_depart)
    for nœud in graphe.keys():
        if nœud not in parcours_graphe:
            return False
    return True


assert est_connexe(graphe_connexe_cyclique)
assert est_connexe(graphe_connexe_non_cyclique)
assert not est_connexe(graphe_cyclique_non_connexe)
assert est_connexe(grahpe_cyclique_non_hamiltonien)
assert est_connexe(arbre)
assert est_connexe(pseudo_arbre)
assert not est_connexe(foret, 2)


def possede_un_cycle(graphe: dict[int, list[int]], sommet_depart: int = 1):
    if not est_connexe(graphe):
        raise ValueError("please provide a connex graph.")
    file: list[tuple[int, None | int]] = [(sommet_depart, None)]
    deja_visites: list[int] = []
    while len(file) != 0:
        sommet_courant, parent = file.pop(0)
        if sommet_courant in deja_visites:
            return True
        deja_visites.append(sommet_courant)
        voisins = graphe[sommet_courant]
        for voisin in voisins:
            if voisin != parent:
                file.append((voisin, sommet_courant))
    return False


assert possede_un_cycle(graphe_connexe_cyclique)
assert not possede_un_cycle(graphe_connexe_non_cyclique)
try:  # we check that it crashes correctly
    possede_un_cycle(graphe_cyclique_non_connexe)
    possede_un_cycle(foret, 2)
    assert False
except ValueError:
    assert True
assert possede_un_cycle(grahpe_cyclique_non_hamiltonien)
assert not possede_un_cycle(arbre)
assert possede_un_cycle(pseudo_arbre)


def cycle_eulerien(graphe: dict[int, list[int]]):
    ...
