#!/usr/bin/env python3
# -*- coding=utf-8 -*-
# this code is under the GNU GPL 3.0.
# import random


class Jeu:
    def __init__(self):
        self.grille: list[list[int | None]] = [[None]*9 for _ in range(9)]
        self.grille = [
            [1, 2, 3, 4, 5, 6, 7, 8, 9],
            [4, 5, 6, 7, 8, 9, 1, 2, 3],
            [7, 8, 9, 1, 2, 3, 4, 5, 6],

            [2, 3, 4, 5, 6, 7, 8, 9, 1],
            [5, 6, 7, 8, 9, 1, 2, 3, 4],
            [8, 9, 1, 2, 3, 4, 5, 6, 7],

            [3, 4, 5, 6, 7, 8, 9, 1, 2],
            [6, 7, 8, 9, 1, 2, 3, 4, 5],
            [9, 1, 2, 3, 4, 5, 6, 7, 8]
        ]

    def __repr__(self):
        return str(self)
    
    def __str__(self):
        str_to_return = "╔" + ("═══╤"*2 + "═══╦")*2 + "═══╤"*2 + "═══╗\n"
        for i, row in enumerate(self.grille):
            str_to_return += "║" + ("   │"*2 + "   ║")*2 + "   │"*2 + "   ║\n"
            for j in range(3):
                str_to_return += f"║ {row[j*3] if row[j*3] is not None else " "} "
                str_to_return += f"│ {row[j*3+1] if row[j*3+1] is not None else " "} "
                str_to_return += f"│ {row[j*3+2] if row[j*3+2] is not None else " "} "
            str_to_return += "║\n"
            if i%3 == 2 and i != 8:
                str_to_return += "╠" + ("═══╪"*2 + "═══╬")*2 + "═══╪"*2 + "═══╣\n"
            elif i != 8:
                str_to_return += "╟" + ("───┼"*2 + "───╫")*2 + "───┼"*2 + "───╢\n"

        str_to_return += "╚" + ("═══╧"*2 + "═══╩")*2 + "═══╧"*2 + "═══╝"
        return str_to_return

    def remplissage_aléatoire(self):
        """Remplit aléatoirement la grille tout en étant valide"""
        # for i in range(9):
        #     for j in range(9):
        #         random_number = random.randint(1, 9)

    def vérifie_grille(self):
        """Renvoie True si la grille est valide, False sinon"""
        ...

    def vérifie_ligne(self):
        for row in self.grille:
            counter = [0]*9
            for case in row:
                if case is None:
                    continue
                counter[case-1] += 1
            if any([c>1 for c in counter]):
                return False
        return True
    
    def vérifie_colonne(self):
        for j in range(9):
            counter = [0]*9
            for i in range(9):
                case = self.grille[i][j]
                if case is None:
                    continue
                counter[case-1] += 1
            if any([c>1 for c in counter]):
                return False
        return True

    def vérifie_carrés(self):
        ...
        # for i in range(3):
        #     for j in range(3):
        #         counter = [0]*9
                
