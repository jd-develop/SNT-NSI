#!/usr/bin/env python3
# -*- coding=utf-8 -*-

def maxliste(liste):
    if len(liste) == 0:
        return None
    maximum = liste[0]
    for e in liste:
        if e > maximum:
            maximum = e
    return maximum


assert maxliste([]) is None
assert maxliste([98, 12, 104, 23, 131, 9]) == 131
assert maxliste([-27, 24, -3, 15]) == 24
