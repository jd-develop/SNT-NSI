#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# This document is licensed under the GNU-GPL v3 or later.
import random
from typing import Sequence


def maximum_liste(liste: Sequence[int | float]):
    if len(liste) == 0:
        return None
    maximum = liste[0]
    for elt in liste:
        if elt > maximum:
            maximum = elt
    return maximum


def somme_liste(liste: Sequence[int | float]):
    somme = 0
    for elt in liste:
        somme += elt
    return somme


def produit_liste(liste: Sequence[int | float]):
    produit = 1
    for elt in liste:
        produit *= elt
    return produit


liste = [random.randint(-100, 100) for _ in range(random.randint(10, 100))]
assert maximum_liste(liste) == max(liste)
assert somme_liste(liste) == sum(liste)
assert produit_liste([1, 5, -3, 10]) == -150
