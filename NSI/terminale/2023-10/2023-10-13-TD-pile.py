#!/usr/bin/env python3
# -*- coding: utf-8 -*-


class Chainon:
    def __init__(self, valeur, suivant):
        self.valeur = valeur
        self.suivant = suivant

    def __repr__(self):
        return f"Chainon({self.valeur})"

    def __str__(self):
        return f"Chainon({self.valeur})"


# class File:
#     def __init__(self):
#         self.tete = None
#         self.queue = None
#
#     def est_vide(self):
#         return self.tete is None and self.queue is None
#
#     def enfiler(self, valeur):
#         nouveau_chainon = Chainon(valeur, None)
#         if self.est_vide():
#             self.tete = self.queue = nouveau_chainon
#         else:
#             if self.tete.suivant is None:
#                 self.tete.suivant = self.queue
#             self.queue.suivant = nouveau_chainon
#             self.queue = nouveau_chainon
#
#     def defiler(self):
#         valeur_ancienne_tete = self.tete.valeur
#         self.tete = self.tete.suivant
#         if self.tete is None:
#             self.queue = None
#         return valeur_ancienne_tete
#
#     def consulter(self):
#         if self.est_vide():
#             return None
#         return self.tete.valeur
#
#     def vider(self):
#         self.tete = self.queue = None
#
#     def taille(self):
#         if self.est_vide():
#             return 0
#
#         taille = 1
#         chainon_actuel = self.tete
#
#         while chainon_actuel.suivant is not None:
#             taille += 1
#             chainon_actuel = chainon_actuel.suivant
#
#         return taille

class File:
    def __init__(self):
        self.tete = None
        self.queue = None
        self._taille = 0

    def est_vide(self):
        return self.tete is None and self.queue is None

    def enfiler(self, valeur):
        nouveau_chainon = Chainon(valeur, None)
        if self.est_vide():
            self.tete = self.queue = nouveau_chainon
        else:
            if self.tete.suivant is None:
                self.tete.suivant = self.queue
            self.queue.suivant = nouveau_chainon
            self.queue = nouveau_chainon
        self._taille += 1

    def defiler(self):
        valeur_ancienne_tete = self.tete.valeur
        self.tete = self.tete.suivant
        if self.tete is None:
            self.queue = None
        self._taille -= 1
        return valeur_ancienne_tete

    def consulter(self):
        if self.est_vide():
            return None
        return self.tete.valeur

    def vider(self):
        self.tete = self.queue = None
        self._taille = 0

    def taille(self):
        return self._taille


def test_file(file):
    assert file.est_vide()

    file.enfiler(1)
    assert file.consulter() == 1
    assert not file.est_vide()

    file.enfiler(2)
    assert file.consulter() == 1

    assert file.defiler() == 1
    assert file.consulter() == 2
    assert file.defiler() == 2

    assert file.est_vide()

    for i in range(10):
        file.enfiler(i)

    assert file.consulter() == 0
    file.vider()
    assert file.est_vide()
    assert file.consulter() is None

    assert file.taille() == 0

    file.enfiler("hello world")
    assert file.taille() == 1

    file.enfiler([1, 2])
    assert file.taille() == 2

    file.enfiler(None)
    assert file.taille() == 3

    for i in range(100):
        file.enfiler(i)
    assert file.taille() == 103

    assert file.defiler() == "hello world"
    assert file.taille() == 102

    for i in range(100):
        file.defiler()
    assert file.taille() == 2

    file.vider()
    assert file.taille() == 0


test_file(File())

# Étant donné que la méthode taille parcourt une fois chaque chaînon,
# la complexité de la méthode taille est de O(n)

# Il faut modifier les méthodes `__init__`, `enfiler`, `défiler` et `vider`
# La nouvelle complexité de la méthode taille est de O(1), étant donné
# qu’on ne fait que consulter une valeur.
