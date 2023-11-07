#!/usr/bin/env python3
# -*- coding:utf-8 -*-

def moyenne(notes: list[tuple[int | float, int | float]]) -> float | None:
    """Renvoie la moyenne pondérée des notes.

    Le paramètre notes est une liste de tuple, où chaque tuple est composé d’exactement deux nombres (int ou float), le
    premier étant la note en elle-même et le second est un coefficient.
    Si la somme des coefficients est nulle, renvoie None (et non ZeroDivisionError)
    """
    somme_notes = 0
    somme_coefficients = 0
    for note, coefficient in notes:
        somme_notes += note*coefficient
        somme_coefficients += coefficient

    if somme_coefficients == 0:
        return None

    return somme_notes/somme_coefficients


# print(moyenne([(8, 2), (12, 0), (13.5, 1), (5, 0.5)]))
# print(moyenne([(3, 0), (5, 0)]))
