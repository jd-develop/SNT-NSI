#!/usr/bin/env python3
# -*- coding=utf-8 -*-
import random


class TicTacToe:
    def __init__(self):
        self.grille = [[0]*3 for _ in range(3)]
        self.joueur = 1

    def __repr__(self):
        str_to_return = "    0   1   2\n"
        str_to_return += "  ╭───┬───┬───╮\n"
        for i in range(3):
            str_to_return += (
                f"{i} │ a │ b │ c │\n"
                .replace("a", self._n2c(self.grille[i][0], False))
                .replace("b", self._n2c(self.grille[i][1], False))
                .replace("c", self._n2c(self.grille[i][2], False))
            )
            if i != 2:
                str_to_return += "  ├───┼───┼───┤\n"
        str_to_return += "  ╰───┴───┴───╯"
        return str_to_return

    def jouer(self, ligne: int, colonne: int):
        if not 0 <= ligne < 3:
            return "Ligne invalide"
        if not 0 <= colonne < 3:
            return "Colonne invalide"
        if self.grille[ligne][colonne] != 0:
            return "Case non libre"
        self.grille[ligne][colonne] = self.joueur
        self.joueur = int(not bool(self.joueur-1))+1

    def _n2c(self, x: int, couleur: bool = False):
        if not couleur:
            return " " if x == 0 else "X" if x == 1 else "O"
        if x == 0:
            return " "
        if x == 1:
            return "\033[91mX\033[0m"
        return "\033[32mO\033[0m"
    
    def afficher(self, jeu: list[list[int]] | None = None, couleur: bool = True):
        if jeu is None:
            jeu = self.grille
        print("    0   1   2")
        print("  ╭───┬───┬───╮")
        for i in range(3):
            print(
                f"{i} │ a │ b │ c │"
                .replace("a", self._n2c(jeu[i][0], couleur))
                .replace("b", self._n2c(jeu[i][1], couleur))
                .replace("c", self._n2c(jeu[i][2], couleur))
            )
            if i != 2:
                print("  ├───┼───┼───┤")
        print("  ╰───┴───┴───╯")
    
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

    def cases_vides(self) -> list[tuple[int, int]]:
        """Renvoie tous les couples (l, c) de cases vides"""
        if self.grille_pleine():
            return []
        list_to_return: list[tuple[int, int]] = []
        for i in range(3):
            for j in range(3):
                if self.grille[i][j] == 0:
                    list_to_return.append((i, j))
        return list_to_return
    
    def jeu2num(self, jeu: list[list[int]] | None = None) -> int:
        """Renvoie le jeu sous forme de nombre (conversion en base 3, retour en base 10)"""
        if jeu is None:
            jeu = self.grille
        num = 0
        for i in range(3):
            for j in range(3):
                num *= 3
                num += jeu[i][j]
        return num
    
    def num2jeu(self, num: int) -> list[list[int]]:
        """Renvoie une grille"""
        assert num < 3**10
        jeu = [[0]*3 for _ in range(3)]
        for i in range(2, -1, -1):
            for j in range(2, -1, -1):
                q, r = divmod(num, 3)
                num = q
                jeu[i][j] = r
        return jeu
    
    def tourne(self, jeu: list[list[int]] | None = None):
        """Renvoie la grille tournée d’un quart de tour, sans la modifier."""
        if jeu is None:
            jeu = self.grille
        nouvelle_grille = [[0]*3 for _ in range(3)]
        for i in range(3):
            for j in range(3):
                nouvelle_grille[i][j] = jeu[j][2-i]
        return nouvelle_grille

    def symétrie(self, jeu: list[list[int]] | None = None):
        """Renvoie la symétrie de la grille"""
        if jeu is None:
            jeu = self.grille
        nouvelle_grille = [[0]*3 for _ in range(3)]
        for i in range(3):
            for j in range(3):
                nouvelle_grille[i][j] = jeu[i][2-j]
        return nouvelle_grille
    
    def petit_num(self, jeu: list[list[int]] | None = None):
        """Renvoie le plus petit numéro des 8 équivalents du jeu"""
        if jeu is None:
            jeu = self.grille
        liste_jeux: list[int] = []
        for _ in range(4):
            liste_jeux.append(self.jeu2num(jeu))
            liste_jeux.append(self.jeu2num(self.symétrie(jeu)))
            jeu = self.tourne(jeu)
        return min(liste_jeux), liste_jeux

jeu = TicTacToe()
display_next = True
while True:
    if display_next:
        jeu.afficher()
    else:
        display_next = True
    if jeu.partie_nulle():
        print("Partie nulle.")
        jeu.afficher()
        break
    gagné = jeu.gagné()
    if gagné is not None:
        if gagné == 2:
            print("L’ordinateur a gagné !")
        else:
            print("Vous avez gagné !")
        jeu.afficher()
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
    