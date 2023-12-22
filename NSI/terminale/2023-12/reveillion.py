#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import random


class Convive:
    def __init__(self):
        self.couvert_droit = False
        self.couvert_gauche = False
        self.fini = False
    
    def manger(self):
        assert not self.fini
        assert self.couvert_droit
        assert self.couvert_gauche
        self.couvert_droit = False
        self.couvert_gauche = False
        self.fini = True

    def peut_manger(self):
        return self.couvert_droit and self.couvert_gauche

    def prendre_couvert_droit(self):
        self.couvert_droit = True

    def prendre_couvert_gauche(self):
        self.couvert_gauche = True

    def __str__(self):
        return "c" if self.couvert_droit else "" + "f" if self.couvert_gauche else "" + "miam" if self.fini else ""

    def __repr__(self):
        return self.__str__()


NOMBRE_CONVIVES = 8
convives = [Convive() for _ in range(NOMBRE_CONVIVES)]


def voisin_de_droite(indice_convive: int):
    return (indice_convive+1) % len(convives)


def voisin_de_gauche(indice_convive: int):
    return (indice_convive-1) % len(convives)


# Aaahhh ça marche pas
tout_le_monde_mange = 0
for i in range(100):  # 100 repas
    interlocks_or_finished = 0
    finished = interlocks = 0
    counter = 0
    while not (finished == NOMBRE_CONVIVES or interlocks == NOMBRE_CONVIVES):
        counter += 1
        if counter == 300:
            break
        interlocks_or_finished = 0
        interlocks = 0
        finished = 0
        for i, convive in enumerate(convives):
            if convive.fini:
                interlocks_or_finished += 1
                finished += 1
                continue
            if convive.peut_manger():
                convive.manger()
                interlocks_or_finished += 1
                finished += 1
                continue
            if random.randint(0, 1) == 0:
                droite = True
                voisin = convives[voisin_de_droite(i)]
            else:
                droite = False
                voisin = convives[voisin_de_gauche(i)]
            if droite and voisin.couvert_gauche:
                interlocks_or_finished += 1
                interlocks += 1
                continue
            if not droite and voisin.couvert_droit:
                interlocks_or_finished += 1
                interlocks += 1
                continue
            if droite:
                convive.prendre_couvert_droit()
            else:
                convive.prendre_couvert_gauche()
        # print(convives)
    if finished == NOMBRE_CONVIVES:
        tout_le_monde_mange += 1

print(tout_le_monde_mange)
