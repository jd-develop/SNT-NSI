#!/usr/bin/env python3
# -*- coding=utf-8 -*-
from typing import Any


def liste2dict(liste: list[Any]):
    dict_to_return = {e: 0 for e in liste}
    for elt in liste:
        dict_to_return[elt] += 1
    return dict_to_return


assert liste2dict([1, 2, 1, 3, 4]) == {1: 2, 2: 1, 3: 1, 4: 1}
assert liste2dict(["salut", print, 12.3, print, "coucou", "salut"]) == {"salut": 2, print: 2, 12.3: 1, "coucou": 1}


def liste2indexdict(liste: list[Any]):
    dict_to_return: dict[Any, tuple[int, ...]] = {e: tuple() for e in liste}
    for i, elt in enumerate(liste):
        dict_to_return[elt] += (i,)
    return dict_to_return


assert liste2indexdict([1, 2, 1, 3, 4]) == {1: (0, 2), 2: (1,), 3: (3,), 4: (4,)}
assert liste2indexdict(["salut", print, 12.3, print, "coucou", "salut"]) == {"salut": (0, 5), print: (1, 3), 12.3: (2,), "coucou": (4,)}
