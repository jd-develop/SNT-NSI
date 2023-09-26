#!/usr/bin/env python3
# coding:utf-8

#%% Première phase
class Chrono1:
    def __init__(self, temps: int = 0):
        self.temps = temps

    def __str__(self):
        return f"{self.temps}s"

    def avancer(self, t):
        """Avancer de t secondes"""
        self.temps += t


#%% deuxième phase
import time


class Chrono2:
    def __init__(self):
        self.temps = 0
        self.t_zero = int(time.time())

    def __str__(self):
        self.actualiser()
        return f"{self.temps}s"

    def actualiser(self):
        """Actualise le chronomètre en fonction du timer de l’ordinateur"""
        self.temps = int(time.time()) - self.t_zero


#%% troisième phase
import time


class Chrono3:
    def __init__(self):
        self.temps = 0
        self.t_zero = int(time.time())
        self.suspendu = False
        self.t_suspension = 0
        self.t_total_suspendu = 0

    def __str__(self):
        self.actualiser()
        return f"{self.temps}s"

    def actualiser(self):
        """Actualise le chronomètre en fonction du timer de l’ordinateur"""
        if not self.suspendu:
            self.temps = int(time.time()) - self.t_zero - self.t_total_suspendu

    def suspendre(self):
        self.actualiser()
        self.suspendu = True
        self.t_suspension = int(time.time())

    def reprendre(self):
        self.suspendu = False
        self.t_total_suspendu += int(time.time()) - self.t_suspension
        self.t_suspension = 0

    def zero(self):
        # À noter qu’on ne remet pas à zéro la suspension.
        # Comme ça, on peut le mettre à zéro et le lancer quand on veut.
        self.temps = 0
        self.t_zero = int(time.time())
        self.t_suspension = int(time.time())
        self.t_total_suspendu = 0
