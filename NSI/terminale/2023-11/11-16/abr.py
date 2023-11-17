#!/usr/bin-env python3
# -*- coding:utf-8 -*-

class ABR:
    def __init__(self):
        self.tab = [None]

    def ajoute(self, valeur):
        n = 0
        while n < len(self.tab):
            if self.tab[n] is None:
                self.tab[n] = valeur
                return
            if valeur == self.tab[n]:
                return
            if valeur < self.tab[n]:
                n = 2*n + 1
            else:
                n = 2*n + 2
        self.tab.extend([None]*(len(self.tab) + 1))
        self.tab[n] = valeur
    
    def __contains__(self, valeur):
        n = 0
        while n < len(self.tab):
            if self.tab[n] is None:
                return False
            if self.tab[n] == valeur:
                return True
            if valeur < self.tab[n]:
                n = 2*n + 1
            else:
                n = 2*n + 2


arbreTest = ABR()
arbreTest.ajoute(10)
arbreTest.ajoute(5)
arbreTest.ajoute(3)
arbreTest.ajoute(8)
arbreTest.ajoute(10)
print(arbreTest.tab)
assert 10 in arbreTest
assert 5 in arbreTest
assert 8 in arbreTest
assert 3 in arbreTest
assert 1 not in arbreTest
assert 4 not in arbreTest
assert 6 not in arbreTest
assert 9 not in arbreTest
assert 14 not in arbreTest
assert -25 not in arbreTest
