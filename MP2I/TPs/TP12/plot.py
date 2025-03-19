#!/usr/bin/env python3
# -*- coding:utf-8 -*-
# type: ignore
from matplotlib import pyplot as plt

valeurs_n = [0, 1, 5, 10, 50, 100, 500, 1000, 2000, 4000, 5000, 8000, 10000]
temps_a = [
    2.00000000916134e-06,
    4.00000000411182555e-06,
    5.99999998485145625e-06,
    1.19999999839137672e-05,
    5.30000000082964107e-05,
    0.000511000000003036803,
    0.0108039999999931524,
    0.027006999999969139,
    0.084391000000010763,
    0.323762000000016315,
    0.504221000000001141,
    1.40096299999999019,
    2.2875839999999954,
]
n_carré = [(n**2)/49603174 for n in valeurs_n]

plt.plot(valeurs_n, temps_a, label="Arbres binaires de recherche")
plt.plot(valeurs_n, n_carré, label="O(n²)")
plt.xlabel("Nombre d’éléments")
plt.ylabel("Temps d’exécution")
plt.legend()
plt.grid()
plt.show()

