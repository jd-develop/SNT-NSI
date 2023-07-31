#!/usr/bin/env python3
# coding:utf-8

# question 1
pomme = {
    "couleur": "vert",
    "masse": 176,
    "largeur": 7.2,
    "hauteur": 8.1
}
orange = {
    "couleur": "orange",
    "masse": 210,
    "largeur": 8.2,
    "hauteur": 7.5
}
citron = {
    "couleur": "jaune",
    "masse": 132,
    "largeur": 6.1,
    "hauteur": 8.3
}
kiwi = {
    "couleur": "marron",
    "masse": 98,
    "largeur": 4.1,
    "hauteur": 5.5
}

# question 2
fruits = [pomme, orange, citron, kiwi]

# question 3
print(f"3) {fruits[2]['couleur'] = }")

# question 4
print(f"4) {fruits[3]['largeur'] = }")

# question 5
print("5) fruits[1]['hauteur'] = 7.6")
fruits[1]['hauteur'] = 7.6

# question 6
print("6) Si les index changent, on peut confondre les fruits.")

# question 7
fruits = {"pomme": pomme, "orange": orange, "citron": citron, "kiwi": kiwi}

# question 8
print(f"8) {fruits['orange']['masse'] = }")


# exercice 10
def liste(dictionnaire: dict):
    return list(dictionnaire.keys())


def masse(fruits_):
    somme = 0
    for fruit in fruits_.values():
        somme += fruit["masse"]
    return somme


def affiche(fruits_: dict):
    for nom, fruit in fruits_.items():
        print(f"{nom = }", end="")
        for k, v in fruit.items():
            print(f", {k} = {v}", end="")
        print()


print(liste(fruits))
print(masse(fruits))
affiche(fruits)
