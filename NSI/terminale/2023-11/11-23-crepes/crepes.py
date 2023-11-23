#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import random


def tirage(n: int):
    """ renvoie une chaîne de caractères contenant la taille et l’état de chaque crêpe.
        La première est la plus au-dessus.
    """
    crepes = [str(i) + random.choice(("M", "B")) for i in range(1, n+1)]
    random.shuffle(crepes)
    chaine = "".join(crepes)
    return chaine


def retourne(crepes: str, k: int):
    """ retourne les k premières crêpes """
    crepes_provisoires = ""
    for i in range(k):
        crepe = crepes[i*2:i*2+2]
        if crepe == "":
            break
        if crepe[1] == "M":
            crepe = crepe[0] + "B"
        else:
            crepe = crepe[0] + "M"
        crepes_provisoires = crepe + crepes_provisoires
    return crepes_provisoires + crepes[k*2:]


def trouver_plus_grande(crepes: list[tuple]):
    """ renvoie l’indice de la plus grande crêpe """
    if len(crepes) == 0:
        return None
    indice = 0
    plus_grande = crepes[0][0]
    for i, e in enumerate(crepes):
        if e[0] >= plus_grande:
            indice = i
            plus_grande = e[0]
    return indice


def crepes_vers_liste(crepes: str):
    """ renvoie une liste de crepes """
    t = []
    for i in range(len(crepes)-1):
        crepe = crepes[i*2:i*2+2]
        if crepe == "":
            break
        t.append((int(crepe[0]), crepe[1]))
    return t


def resoudre(crepes: str, debug = False):
    """ Trie les crepes dans l’ordre croissant et dans le bon sens """
    nombre_de_crepes = len(crepes)//2
    for i in range(nombre_de_crepes):
        if debug:
            print(i, crepes)
        
        plus_grande = trouver_plus_grande(crepes_vers_liste(crepes)[:nombre_de_crepes-i])
        if debug:
            print(f"   plus grande: {plus_grande}")
        
        if plus_grande is None:
            continue
        else:
            plus_grande += 1
        
        crepes = retourne(crepes, plus_grande)
        if debug:
            print("   après retournement 1: " + crepes)
        
        if crepes[1] == "B":
            if debug:
                print("   mauvais côté")
            crepes = retourne(crepes, 1)
        
        crepes = retourne(crepes, nombre_de_crepes-i)
        if debug:
            print("   après retournement 2: " + crepes)
    return crepes


def pprint(pile):
    """ Écrit par Mistera, sans aucune garantie de marcher.
    Jean Dubois ne saurait être tenu reponsable de cette fonction. """
    a = []
    for i, n in enumerate([int(n) for n in pile[::2]]):
        color = "\033[92m" if pile[1::2][i] == "B" else "\033[91m"
        leading_spaces = (int(max(pile[::2])) - (n - 1)) * " "
        equals = (n - 1) * "="
        letter = pile[1::2][i]
        a.append(f"{color}{leading_spaces}{equals}{n}{letter}{equals}\033[0m\n")
    print("".join(a))


crepes_test = tirage(9)
pprint(crepes_test)
pprint(resoudre(crepes_test))
