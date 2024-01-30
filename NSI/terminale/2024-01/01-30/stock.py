#!/usr/bin/env python3
# -*- coding=utf-8 -*-
class Stock:
    def __init__(self):
        self.qt_farine = 0
        self.nb_oeufs = 0
        self.qt_beurre = 0

    def ajouter_beurre(self, qt: int):
        self.qt_beurre += qt

    def ajouter_farine(self, qt: int):
        self.qt_farine += qt
    
    def ajouter_oeufs(self, qt: int):
        self.nb_oeufs += qt

    def afficher(self):
        print(f"farine : {self.qt_farine}")
        print(f"œuf    : {self.nb_oeufs}")
        print(f"beurre : {self.qt_beurre}")

    def stock_suffisant_brioche(self):
        assez_de_farine = self.qt_farine >= 350
        assez_de_beurre = self.qt_beurre >= 175
        assez_d_oeufs = self.nb_oeufs >= 4
        return assez_de_farine and assez_de_beurre and assez_d_oeufs
    
    def produire(self):
        res = 0
        while self.stock_suffisant_brioche():
            self.qt_beurre = self.qt_beurre - 175
            self.qt_farine = self.qt_farine - 350
            self.nb_oeufs = self.nb_oeufs - 4
            res = res + 1
        return res
