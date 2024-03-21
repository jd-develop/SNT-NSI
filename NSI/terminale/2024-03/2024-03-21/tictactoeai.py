#!/usr/bin/env python3
# -*- coding=utf-8 -*-
import random

class TicTacToe:
    def __init__(self):
        self.grille = [[0]*3 for _ in range(3)]
        self.joueur = 1
    
    def jouer(self, ligne: int, colonne: int):
        if not 0 <= ligne < 3:
            return "Ligne invalide"
        if not 0 <= colonne < 3:
            return "Colonne invalide"
        if self.grille[ligne][colonne] != 0:
            return "Case non libre"
        self.grille[ligne][colonne] = self.joueur
        self.joueur = int(not bool(self.joueur-1))+1
    
    def afficher(self):
        print("   0 1 2")
        print("  ╭─┬─┬─╮")
        for i, ligne in enumerate(self.grille):
            print(f"{i} │{"│".join(map(lambda x: " " if x == 0 else "X" if x == 1 else "O", ligne))}│")
            if i != 2:
                print("  ├─┼─┼─┤")
            else:
                print("  ╰─┴─┴─╯")
    
    def gagné_en_ligne(self):
        for ligne in self.grille:
            if ligne[0] == ligne[1] == ligne[2] != 0:
                return ligne[0]
        return None
    
    def gagné_en_colonne(self):
        for j in range(3):
            if self.grille[0][j] == self.grille[1][j] == self.grille[2][j] != 0:
                return self.grille[0][j]
        return None
    
    def gagné_en_diagonale(self):
        if self.grille[0][0] == self.grille[1][1] == self.grille[2][2] != 0:
            return self.grille[0][0]
        elif self.grille[0][2] == self.grille[1][1] == self.grille[2][0] != 0:
            return self.grille[0][2]
        return None
    
    def grille_pleine(self):
        for i in range(3):
            for j in range(3):
                if self.grille[i][j] == 0:
                    return False
        return True
    
    def gagné(self):
        gagné_en_ligne = self.gagné_en_ligne()
        gagné_en_colonne = self.gagné_en_colonne()
        gagné_en_diagonale = self.gagné_en_diagonale()
        if gagné_en_ligne is not None:
            return gagné_en_ligne
        if gagné_en_colonne is not None:
            return gagné_en_colonne
        if gagné_en_diagonale is not None:
            return gagné_en_diagonale
        return None
    
    def partie_nulle(self):
        return self.gagné() is None and self.grille_pleine()


jeu = TicTacToe()
display_next = True
while True:
    if display_next:
        jeu.afficher()
    else:
        display_next = True
    if jeu.partie_nulle():
        print("Partie nulle.")
        break
    gagné = jeu.gagné()
    if gagné is not None:
        if gagné == 2:
            print("L’ordinateur a gagné !")
        else:
            print("Vous avez gagné !")
        break
    if jeu.joueur == 1:
        print("C’est à vous de jouer.")
        display_next = False
    else:
        while jeu.jouer(random.randrange(3), random.randrange(3)) is not None:
            continue
        continue
    ligne = input("Ligne : ")
    colonne = input("Colonne : ")
    try:
        ligne = int(ligne)
        colonne = int(colonne)
    except ValueError:
        print("Erreur, veuillez entrer une ligne et une colonne valides.")
        display_next = False
        continue
    jouer = jeu.jouer(ligne, colonne)
    if jouer is not None:
        print(jouer)
        display_next = False
        continue
    