#!/urs/bin/env python3
# coding:utf-8
from typing import Self

COLOR_NAME = ("trèfle", "carreau", "cœur", "pique")
CARD_NAME = ("As", 2, 3, 4, 5, 6, 7, 8, 9, 10, "Valet", "Dame", "Roi")


class Carte:
    def __init__(self, couleur: int, valeur: int):
        assert couleur in range(4), "0 = trèfle, 1 = carreau, 2 = cœur, 3 = pique."
        self.couleur: int = couleur
        assert valeur in range(13), "0 = as, 10 = valet, 11 = dame, 12 = roi."
        self.valeur: int = valeur

    def __str__(self):
        return f"{CARD_NAME[self.valeur]} de {COLOR_NAME[self.couleur]}"

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other: Self):
        """Renvoie si les cartes ont la même VALEUR (roi de pique = roi de trèfle par exemple)"""
        return self.valeur == other.valeur

    def __lt__(self, other: Self):
        """Compare uniquement les VALEURS des cartes"""
        return self.valeur < other.valeur

    def __gt__(self, other: Self):
        """Compare uniquement les VALEURS des cartes"""
        return self.valeur > other.valeur

    def __ge__(self, other: Self):
        """Compare uniquement les VALEURS des cartes"""
        return self.valeur >= other.valeur

    def __le__(self, other: Self):
        """Compare uniquement les VALEURS des cartes"""
        return self.valeur <= other.valeur

    def __ne__(self, other: Self):
        """Compare uniquement les VALEURS des cartes"""
        return self.valeur != other.valeur


assert Carte(1, 9) <= Carte(2, 11)
assert Carte(1, 9) != Carte(2, 12)
assert Carte(1, 9) <= Carte(2, 9)
assert Carte(1, 9) == Carte(2, 9)

jeu = [Carte(couleur, valeur) for couleur in range(4) for valeur in range(13)]
print(jeu)
