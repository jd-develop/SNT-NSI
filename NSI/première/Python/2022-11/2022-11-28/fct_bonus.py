#!/usr/bin/env python3
# coding:utf-8
# consigne: Écrire une fonction `bonus(notes)` qui retourne la liste de notes du paramètre notes supérieures à 13
from typing import Iterable


def bonus(notes: Iterable[int | float]) -> list[int | float]:
    return [x for x in notes if x > 13]


assert bonus([8, 15, 12, 18, 16.5, 13]) == [15, 18, 16.5]
print(bonus([8, 15, 12, 18, 16.5, 13]))

assert bonus([]) == []
print(bonus([]))

assert bonus([12, 11, 13, 0.5]) == []
print(bonus([12, 11, 13, 0.5]))
