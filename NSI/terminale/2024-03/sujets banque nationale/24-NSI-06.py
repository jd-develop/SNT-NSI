#!/usr/bin/env python3
# -*- coding=utf-8 -*-
# This program is licenced under the GNU GPL 3.0 or later.

def verifie(tableau: list[int | float]):
    if len(tableau) == 0 or len(tableau) == 1:
        return True
    for i in range(1, len(tableau)):
        if tableau[i-1] > tableau[i]:
            return False
    return True


assert verifie([0, 5, 8, 8, 9])
assert verifie([8, 12, 14])
assert verifie([-1, 4])
assert verifie([])
assert verifie([5])


def depouille(urne: list[str]):
    '''prend en paramètre une liste de suffrages et renvoie un 
    dictionnaire avec le nombre de voix pour chaque candidat'''
    resultat: dict[str, int] = {}
    for bulletin in urne:
        # On utilise ici une particularité de la méthode 'get' qui renvoie None si
        # l’élément n’est pas dans le dictionnaire.
        if resultat.get(bulletin) is not None: 
            resultat[bulletin] += 1
        else:
            resultat[bulletin] = 1
    return resultat


def vainqueurs(election: dict[str, int]):
    '''prend en paramètre un dictionnaire non vide avec le nombre de voix
    pour chaque candidat et renvoie la liste des vainqueurs'''
    nmax = 0
    for candidat in election:
        if election[candidat] > nmax: 
            nmax = election[candidat] 
    liste_finale = [nom for nom in election if election[nom] == nmax] 
    return liste_finale


assert depouille(['A', 'B', 'A']) == {"A": 2, "B": 1}
assert depouille([]) == {}
assert vainqueurs(depouille(['A', 'A', 'A', 'B', 'C', 'B', 'C', 'B', 'C', 'B'])) == ["B"]
assert vainqueurs(depouille(['A', 'A', 'B', 'B', 'C'])) == ["A", "B"]
