#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from math import log2
from matplotlib import pyplot as plt

with open("valeurs.txt", "r", encoding="UTF-8") as fp:
    contenu = fp.readlines()

nb_elements: list[int] = []
temps_tri_rapide: list[float] = []
temps_tri_insertion: list[float] = []
grand_o_de_n_carré: list[float] = []
grand_o_de_n_log_n: list[float] = []

for line in contenu:
    if line == "\n": continue
    line = line[:-1]
    line = line.split()
    n = int(line[0])
    rapide = float(line[1])
    lent = float(line[2])
    nb_elements.append(n)
    temps_tri_rapide.append(rapide)
    temps_tri_insertion.append(lent)
    grand_o_de_n_log_n.append(rapide / n*log2(n))  # *1.5*1e-8)

# plt.plot(nb_elements, temps_tri_rapide, label="Tri rapide")  # type: ignore
plt.plot(nb_elements, grand_o_de_n_log_n, label="Temps d’exécution / O(n log n)")  # type: ignore
plt.legend()  # type: ignore
plt.show()  # type: ignore
plt.plot(nb_elements, temps_tri_rapide, label="Tri rapide")  # type: ignore
plt.plot(nb_elements, temps_tri_insertion, label="Tri par insertion")  # type: ignore
plt.legend()  # type: ignore
plt.show()  # type: ignore
