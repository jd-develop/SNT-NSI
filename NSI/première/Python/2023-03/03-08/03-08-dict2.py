#!/usr/bin/env python3
# coding:utf-8

frontaliers = [
    {"Nom": "Belgique",   "Superficie": 30.5,  "Population": 11.5,  "Membre": True},
    {"Nom": "Luxembourg", "Superficie": 2.6,   "Population": 0.6,   "Membre": True},
    {"Nom": "Allemagne",  "Superficie": 357,   "Population": 83.1,  "Membre": True},
    {"Nom": "Suisse",     "Superficie": 41.3,  "Population": 8.6,   "Membre": False},
    {"Nom": "Italie",     "Superficie": 301.2, "Population": 60.5,  "Membre": True},
    {"Nom": "Monaco",     "Superficie": 0.002, "Population": 0.039, "Membre": False},
    {"Nom": "Andorre",    "Superficie": 0.468, "Population": 0.077, "Membre": False},
    {"Nom": "Espagne",    "Superficie": 506,   "Population": 47.3,  "Membre": True}
]

# question 1
print(frontaliers[4])

# question 2
print(frontaliers[6]["Nom"])

# question 3
print(frontaliers[7]["Superficie"])


# question 4
def liste_membres(frontaliers_):
    membres = []
    for pays in frontaliers_:
        if pays['Membre']:
            membres.append(pays["Nom"])
    return membres


print(liste_membres(frontaliers))


# question 5
def pays_avec_population(population):
    for pays in frontaliers:
        if pays["Population"] == population:
            return pays["Nom"]
    return None


print(pays_avec_population(47.3))  # Espagne
print(pays_avec_population(56.8))  # None


# question 6
def plus_dense(frontaliers_):
    density_max = 0
    max_nom = ""
    for pays in frontaliers_:
        density_pays = pays["Population"] / pays["Superficie"]
        if density_pays > density_max:
            max_nom = pays["Nom"]
            density_max = density_pays
    return max_nom


print(plus_dense(frontaliers))


# question 7
def affiche(frontaliers_: list[dict]):
    for key in frontaliers_[0].keys():
        print(f"{key:<15}", end='')
    print()
    for pays in frontaliers_:
        for value in pays.values():
            print(f"{value:<15}", end='')
        print()


affiche(frontaliers)
