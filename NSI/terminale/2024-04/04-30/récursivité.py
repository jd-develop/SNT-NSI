#!/usr/bin/env python3
# -*- coding=utf-8 -*-
# licenced under GNU GPL v3.0 or later

def factorielle(n: int) -> int:
    assert isinstance(n, int), "'n' doit être un entier positif."
    assert n >= 0, "'n' doit être un entier positif."
    if n < 0:
        raise ValueError("'n' doit être un entier positif.")
    if n == 0 or n == 1:
        return 1
    return n * factorielle(n-1)
    

def recherche_dichotomique_sous_liste(liste: list[int], cible: int) -> int:
    """La liste doit être triée. Renvoie un index, -1 si la valeur n’est pas trouvée."""
    if len(liste) == 0:
        return -1
    if len(liste) == 1:
        if liste[0] == cible:
            return 0
        return -1
    
    milieu = len(liste)//2
    if liste[milieu] == cible:
        return milieu

    if liste[milieu] < cible:
        sous_liste = liste[milieu:]
        index_départ = milieu
    else:
        sous_liste = liste[:milieu]
        index_départ = 0

    index_sous_liste = recherche_dichotomique_sous_liste(sous_liste, cible)
    if index_sous_liste == -1:
        return -1
    return index_départ + index_sous_liste
