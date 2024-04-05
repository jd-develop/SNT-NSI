#!/usr/bin/env python3
# -*- coding:utf-8 -*-

"""
Simulation : 300 PC + 10 en réserve
MTBF (mean time between failure) : 5 ans
délai de remise en état : 1 mois
"""
from __future__ import annotations
from random import expovariate
from pprint import pprint


class PC:
    # temps = 0.0

    def __init__(self):
        self.temps_avant_panne = expovariate(0.2)
        self.en_panne = False

    def __gt__(self, other: PC):
        return self.temps_avant_panne > other.temps_avant_panne
    
    def __eq__(self, other: PC):  # type: ignore
        return self.temps_avant_panne == other.temps_avant_panne
    
    def __repr__(self):
        return f"PC qui tombe en panne dans {self.temps_avant_panne}"


def expérience():
    pcs = [PC() for _ in range(310)]
    pcs.sort()
    pprint(pcs)
    # todo: finish
