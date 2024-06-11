#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from __future__ import annotations


def combinaison(k: int, n: int):
    """Calcule récursivement k parmi n, sans double appel"""
    return ligne_pascal(n, k)[0]


def ligne_pascal(n: int, a: int, b: int | None = None) -> list[int]:
    if a < 0 and (b is None or b < 0):
        return []
    if a < 0:
        a = 0
    if b is None:
        b = a
    résultat: list[int] = []
    if n == -1:
        ligne_précédente = [0]*(b-a)
    else:
        if a > 0:
            ligne_précédente = ligne_pascal(n-1, 0, b+1)
        else:
            ligne_précédente = ligne_pascal(n-1, a-1, b+1)
    for i in range(a, b+1):
        if i < 0 or i > n:
            résultat.append(0)
        elif i == 0 or i == n:
            résultat.append(1)
        else:
            résultat.append(ligne_précédente[i] + ligne_précédente[i-1])
    return résultat


class Arbre:
    def __init__(self, valeur: int, droite: Arbre | None = None, gauche: Arbre | None = None):
        self.valeur = valeur
        self.droite = droite
        self.gauche = gauche

    def est_present(self, valeur: int) -> bool:
        if self.valeur == valeur:
            return True
        elif valeur < self.valeur:
            if self.gauche is None:
                return False
            return self.gauche.est_present(valeur)
        else:
            if self.droite is None:
                return False
            return self.droite.est_present(valeur)
        
    def maximum(self) -> int:
        if self.droite is None:
            return self.valeur
        return self.droite.maximum()
    
    def minimum(self) -> int:
        if self.gauche is None:
            return self.valeur
        return self.gauche.minimum()
    
    def taille(self) -> int:
        taille = 1
        if self.gauche is not None:
            taille += len(self.gauche)
        if self.droite is not None:
            taille += len(self.droite)
        return taille
    
    def __len__(self):
        return self.taille()
    
    def profondeur(self) -> int:
        if self.gauche is None:
            prof_gauche = 0
        else:
            prof_gauche = self.gauche.profondeur()
        if self.droite is None:
            prof_droite = 0
        else:
            prof_droite = self.droite.profondeur()
        return 1 + max(prof_droite, prof_gauche)
    
    def ajoute(self, valeur: int):
        if self.valeur == valeur:
            return
        elif valeur < self.valeur:
            if self.gauche is None:
                self.gauche = Arbre(valeur)
            else:
                self.gauche.ajoute(valeur)
        elif valeur > self.valeur:
            if self.droite is None:
                self.droite = Arbre(valeur)
            else:
                self.droite.ajoute(valeur)
