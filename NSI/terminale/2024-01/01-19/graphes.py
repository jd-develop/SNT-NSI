#!/usr/bin/env python3
# -*- coding=utf-8 -*-

"""Exercice :
Avec un graphe représenté par un dictionnaire où chaque clé est un sommet et
 chaque valeur est la liste des voisins de ce sommet, renvoyer un parcours en
 largeur et un parcours en profondeur de ce graphe.
"""

graphe: dict[str, list[str]] = {
    "A": ["B", "C", "D"],
    "B": ["A", "F"],
    "C": ["A", "E", "F"],
    "D": ["A", "E", "F", "J"],
    "E": ["C", "D", "F", "I", "J"],
    "F": ["B", "C", "D", "E", "G", "H"],
    "G": ["F", "H"],
    "H": ["F", "G", "I"],
    "I": ["E", "H", "J"],
    "J": ["D", "E", "I"]
}


def parcours_en_largeur(graphe: dict[str, list[str]]):
    """Parcours en largeur"""
    file: list[str] = ["A"]
    visités: list[str] = []
    while len(file) != 0:
        sommet = file.pop(0)
        visités.append(sommet)
        voisins = graphe[sommet]
        for v in voisins:
            if v not in visités and v not in file:
                file.append(v)
    return visités


def parcours_en_profondeur(graphe: dict[str, list[str]]):
    """Parcours en profondeur"""
    pile: list[str] = ["A"]
    visités: list[str] = []
    while len(pile) != 0:
        sommet = pile.pop()
        if sommet in visités:
            continue
        visités.append(sommet)
        voisins = graphe[sommet].copy()
        voisins.reverse()
        for v in voisins:
            if v not in visités:
                pile.append(v)
    return visités


print(parcours_en_largeur(graphe))
print(parcours_en_profondeur(graphe))
