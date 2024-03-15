#!/usr/bin/env python3
# -*- coding=utf-8 -*-
from __future__ import annotations
import random


class Individu:
    def __init__(self, liquide: int, biens: list[int]):
        self.liquide = liquide
        self.biens = biens

    def fortune(self):
        """
            Renvoie la fortune totale de l’individu
        """
        return sum(self.biens) + self.liquide

    def transaction(self, other: Individu):
        """
            self et other sont deux individus :
            on tire au sort un bien de other
            on modifie son prix (+ ou - 10%)
            si self a assez de liquide, il achete
            ce bien à other
        """
        if len(other.biens) == 0:
            return
        bien_de_other = random.randint(0, len(other.biens)-1)
        prix_modifié = other.biens[bien_de_other] * random.randint(90, 110) // 100
        if self.liquide >= prix_modifié:
            self.liquide -= prix_modifié
            other.liquide += prix_modifié
            self.biens.append(other.biens.pop(bien_de_other))


def un_jour(population: list[Individu]):
    """
        pour chaque individu de population, on tire
        au sort un autre individu avec lequel on
        fait une transaction
    """
    for individu in population:
        other = random.choice(population)
        while other == individu:
            other = random.choice(population)
        individu.transaction(other)

def décile(population: list[Individu]):
    """
        renvoi les déciles des fortunes des individus
        de population, y compris le min et le max
        donc 11 valeurs
    """
    population_int = [individu.fortune() for individu in population]
    population_int.sort()

    déciles = [population_int[i*len(population_int)//10] for i in range(1, 10)]
    déciles.insert(0, min(population_int))
    déciles.append(max(population_int))
    return déciles


def simulation(population: list[Individu], nb_jours: int = 100):
    for _ in range(nb_jours):
        un_jour(population)
        print(décile(population))


def simulation_matplotlib(population: list[Individu], nb_jours: int = 100):
    from matplotlib import pyplot as plt
    x: list[int] = []
    ys: list[list[int]] = [list() for _ in population]
    for i in range(nb_jours):
        un_jour(population)
        x.append(i+1)
        for j in range(len(population)):
            ys[j].append(population[j].fortune())
    for y in ys:
        plt.plot(x, y, linewidth=0.5)  # type: ignore
    plt.show()  # type: ignore

pop = [Individu(400, [100]*2+[50]*4+[20]*5+[10]*10) for _ in range(1000)]
pop10 = [Individu(400, [100]*2+[50]*4+[20]*5+[10]*10) for _ in range(10)]
pop100 = [Individu(400, [100]*2+[50]*4+[20]*5+[10]*10) for _ in range(100)]
