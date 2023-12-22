#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from __future__ import annotations
# from pprint import pprint

# Énoncé :
# Un pont qui ne peut être traversé que par deux personnes maximum.
# C’est la nuit, il faut une lanterne pour traverser
# A peut traverser en 1 minute
# B                en 2 minutes
# C                en 5 minutes
# D                en 10 minutes
# L désigne la lanterne
# un état est un nombre sous la forme 0bXXXXX
#           où chaque bit représente si ABCDL a traversé ou non
# Le but est de passer de 00000 à 11111

temps = {
    "A": 1,
    "B": 2,
    "C": 5,
    "D": 10
}


def dict_etat(etat: int):
    assert 0 <= etat <= 0b11111
    return {
        "ABCDL"[i]: "gauche" if (etat & 2**(4-i)) == 0 else "droite" for i in range(5)
    }
    # The following commented code is doing the same thing as the line just above
    # {
    #     "A": "gauche" if (etat & 0b10000) == 0 else "droite",
    #     "B": "gauche" if (etat & 0b01000) == 0 else "droite",
    #     "C": "gauche" if (etat & 0b00100) == 0 else "droite",
    #     "D": "gauche" if (etat & 0b00010) == 0 else "droite",
    #     "L": "gauche" if (etat & 0b00001) == 0 else "droite",
    # }


def temps_entre_deux_etats(e1: int, e2: int):
    """Renvoie le temps pour passer d’un état à un autre"""
    assert 0 <= e1 <= 0b11111
    assert 0 <= e2 <= 0b11111
    dict1 = dict_etat(e1)
    dict2 = dict_etat(e2)
    # CAS 1: LA LANTERNE N’A PAS TRAVERSÉ
    if dict1["L"] == dict2["L"]:
        # print("La lanterne n’a pas traversé")
        return None
    ont_traverse = ""
    for c in "ABCD":
        if dict1[c] != dict2[c]:
            if dict1[c] != dict1["L"]:
                # CAS 2: QUELQU’UN A TRAVERSÉ DANS L’AUTRE SENS QUE LA LANTERNE
                # print(f"{c} a traversé sans la lanterne")
                return None
            ont_traverse += c
    if len(ont_traverse) == 0 or len(ont_traverse) > 2:
        # CAS 3: LA LANTERNE A VOYAGÉ TOUTE SEULE OU PLUS DE DEUX PERSONNES ONT TRAVERSÉ
        # print(f"{len(ont_traverse)} personne(s) ont traversé")
        return None
    return max(temps[c] for c in ont_traverse)


class Nœud:
    def __init__(self, numéro: int, coût: int, père: int | None):
        self.numéro = numéro
        self.coût = coût
        self.père = père

    def __lt__(self, other: Nœud):
        return self.coût < other.coût
    
    def __repr__(self):
        numéro_bin = bin(self.numéro)[2:]
        numéro_bin = "0"*(5-len(numéro_bin)) + numéro_bin
        return str([numéro_bin, self.coût, self.père])
    
    def __str__(self):
        return str(self.__repr__())



def dijkstra():
    tableRoutage: dict[int, Nœud] = {}
    ouvert: list[int] = []
    début = Nœud(0, 0, None)
    waiting: list[Nœud] = [début]
    while len(waiting) > 0:
        nœud = waiting.pop(0)
        if nœud.numéro in ouvert:
            continue
        ouvert.append(nœud.numéro)
        tableRoutage[nœud.numéro] = nœud
        for i in range(32):
            coût = temps_entre_deux_etats(nœud.numéro, i)
            if coût is None:
                continue
            nouveau_nœud = Nœud(i, coût+nœud.coût, nœud.numéro)
            waiting.append(nouveau_nœud)
        waiting.sort()
    return tableRoutage


res = dijkstra()
num = 31
while num is not None:
    fils = res[num]
    print(fils)
    num = fils.père


assert temps_entre_deux_etats(0b00000, 0b11111) is None
assert temps_entre_deux_etats(0b00000, 0b11110) is None
assert temps_entre_deux_etats(0b00000, 0b11000) is None
assert temps_entre_deux_etats(0b00000, 0b00001) is None
assert temps_entre_deux_etats(0b00000, 0b11001) == 2
assert temps_entre_deux_etats(0b00000, 0b01101) == 5
assert temps_entre_deux_etats(0b00000, 0b10011) == 10
assert temps_entre_deux_etats(0b10001, 0b00000) == 1
assert temps_entre_deux_etats(0b01101, 0b11111) is None
assert temps_entre_deux_etats(0b01100, 0b11111) == 10
assert temps_entre_deux_etats(0b10011, 0b01100) is None

# print(dict_etat(0b00000))
# print(dict_etat(0b00011))
# print(dict_etat(0b11010))
