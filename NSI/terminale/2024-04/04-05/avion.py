#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Créé le 4 avril 2024

@author: Pierre Vanicat
Complété par jd-develop

Principe de surréservation et non-présentation :
   * tous les passagers qui ont réservé une place ne se présentent pas
     à l'embarquement. la probalité qu'il ne présente pas est notée
                non-présentation
   * pour compenser ce phénomène, les compagnies vendent plus de réservation
     qu'il n'y place dans l'avion
   * si un passager n'a de ce fait pas de place dans un avion, il est proritaire
     sur l'avion suivant. Si cet avion suivant décolle le lendemain matin, la
     compagine doit lui payer une nuit d'hôtel

exemple :
    surréservation = 0.05  (5 %)
    nonprésentation = 0.1  (10 %)
    pour un avion de 200 places, on vend 210 réservations car 210=200*(1+0.05)
    et il se présentera en moyenne 189 passagers car 189 = 210 * ( 1 - 0.1 )
    cela devrai passer…
    De plus, sur les 210 réservations mises en vente, toutes ne seront pas achetées

exemple de tirage au sort d'un passager :

    if random() < nonprésentation:
        print("le passager ne s'est pas présenté")
    else:
        print("le passager s'est présenté")
"""
from random import random
from statistics import mean


def randbinom(n: int, p: float):
    return sum(random() < p for _ in range(n))


def remplirAvion(nbplaces: int, nbresa: int, reliquat: int, nonprésentation: float) -> tuple[int, int]:
    """
    remplit un avion
    entrée :
      - nbplaces : nombre de places de l'avion
      - nbresa   : nombre de réservations pour ce vol
      - reliquat  : nombre de passagers en attente des vols précédents
      - nonprésentation : probalitité qu'un passager réservé ne se présente pas
    sortie :
      - nbpassagers : nombre de passagers qui ont embarqué
      - nbreste     : nombre de passagers qui n'ont pas pu embarquer
    """
    passagers_se_présentant = 0
    for _ in range(nbresa):
        if random() >= nonprésentation:
            passagers_se_présentant += 1

    if reliquat >= nbplaces:
        return nbplaces, (reliquat-nbplaces) + passagers_se_présentant
    nbplaces_restantes = nbplaces - reliquat
    nbreste = passagers_se_présentant - nbplaces_restantes
    if nbreste <= 0:
        return reliquat + passagers_se_présentant, 0
    return nbplaces, nbreste


assert remplirAvion(100, 50, 50, 0) == (100, 0)
assert remplirAvion(100, 75, 25, 0) == (100, 0)
assert remplirAvion(100, 99, 10, 0) == (100, 9)
assert remplirAvion(100, 50, 49, 0) == (99, 0)
assert remplirAvion(100, 100, 100, 0) == (100, 100)


def journée(nbavions: int, tailleavion: int, surréservation: float, nonprésentation: float):
    """
    simule une journée
    entrée :
      - nbavions    : nombre d'avions dans une journée
      - tailleavion : nombre de places dans un avion
      - surréservation : taux de surréservation
      - nonprésentation : probalitité qu'un passager réservé ne se presente pas
    sortie :
      - tauxremplissage : pourcentage des sièges occupés
      - nbreporté       : nombre de passagers qui ont prit l'avion suivant
      - nbhotel         : nombre de passagers qui ont dormi à l'hotel
    """
    reliquat = 0
    liste_taux_remplissage: list[float] = []
    liste_reliquats: list[int] = []
    nb_réservations = int(tailleavion*(1+surréservation))
    for _ in range(nbavions):
        places_remplies, reliquat = remplirAvion(tailleavion, nb_réservations, reliquat, nonprésentation)
        liste_taux_remplissage.append(places_remplies/tailleavion)
        liste_reliquats.append(reliquat)
    return mean(liste_taux_remplissage), sum(liste_reliquats) - reliquat, reliquat
    

if __name__ == '__main__':
    print("Journées avec 10 avions de 180 places, 5% d’overbooxing et 10% de no-show.")
    for _ in range(10):
        remp, nbrep, nbhot = journée(10, 180, 0.05, 0.10)
        print(f"{remp*100:5.2f}%, {nbrep}, {nbhot}")
    print("Journées avec 25 avions de 200 places, 10% d’overbooxing et 8% de no-show.")
    for _ in range(10):
        remp, nbrep, nbhot = journée(25, 200, 0.10, 0.08)
        print(f"{remp*100:5.2f}%, {nbrep}, {nbhot}")
