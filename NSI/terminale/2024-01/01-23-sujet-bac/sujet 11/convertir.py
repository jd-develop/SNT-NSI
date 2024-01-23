#!/usr/bin/env python3
# -*- coding=utf-8 -*-

def convertir(tab):
    """
    tab est un tableau d'entiers, dont les éléments sont 0 ou 1,
    et représentant un entier écrit en binaire.
    Renvoie l'écriture décimale de l'entier positif dont la
    représentation binaire est donnée par le tableau tab
    """
    decimal = 0
    for i in range(1, len(tab)+1):
        # l’idée va être de parcourir le tableau de la fin vers le début,
        # c’est-à-dire de l’index -1 à l’index 0
        decimal += tab[-i] * 2**(i-1)
    return decimal


assert convertir([1, 0, 1, 0, 0, 1, 1]) == 83
assert convertir([1, 0, 0, 0, 0, 0, 1, 0]) == 130
