#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import sys
import math
import turtle as tt

LIGNES = 6
COLONNES = 7
LARGEUR = 100

X_MAX = COLONNES * LARGEUR // 2
X_MIN = -X_MAX
Y_MAX = LIGNES * LARGEUR // 2
Y_MIN = -Y_MAX

# default coordinates when the turtle is at the top for column selection
X_TOP = X_MIN + (COLONNES // 2) * LARGEUR + int(LARGEUR / 2)
Y_TOP = Y_MAX + 5

tt.setup(COLONNES * LARGEUR + 40, LIGNES * LARGEUR + 40)


class Game(tt.Turtle):
    def __init__(self):
        super().__init__()
        self.joueur = 1  # switches between 1 and 2
        self.tableau = [[0 for _ in range(LIGNES)] for __ in range(COLONNES)]

        self.speed(0)
        self.penup()

        self.dessine_fond()

        self.goto(X_TOP, Y_TOP)
        self.tiltangle(270)
        self.color(self.get_color())

        self.won = False

    def dessine_fond(self):
        """Dessine un quadrillage de 6 lignes et 7 colones, avec des cases de 100 par 100."""
        self.goto(0, 0)
        x_max = X_MAX
        y_max = Y_MAX
        for x in range(-x_max, x_max + 1, LARGEUR):
            self.goto(x, y_max)
            self.pendown()
            self.goto(x, -y_max)
            self.penup()
        for y in range(-y_max, y_max + 1, LARGEUR):
            self.goto(-x_max, y)
            self.pendown()
            self.goto(x_max, y)
            self.penup()

    def jeton(self, ligne, colonne, couleur):
        """Place un jeton de couleur `couleur` à la ligne `ligne` et colonne `colonne`
        `ligne` min et `colonne` min = 0."""
        x = colonne * LARGEUR + X_MIN + LARGEUR // 2
        y = (LIGNES - ligne) * LARGEUR + Y_MIN - int(LARGEUR * .95)

        self.goto(x, y)

        self.pendown()
        self.color(couleur)
        self.fillcolor(couleur)
        self.begin_fill()

        self.circle(int(LARGEUR * 0.9) // 2)

        self.end_fill()
        self.penup()
        self.color("black")

    def move_right(self):
        if not Y_TOP - 2 <= int(self.ycor()) <= Y_TOP + 2:
            return
        if int(self.xcor() + LARGEUR) > int(X_MAX):
            return
        self.forward(LARGEUR)

    def move_left(self):
        if not Y_TOP - 2 <= int(self.ycor()) <= Y_TOP + 2:
            return
        if int(self.xcor() - LARGEUR) < int(X_MIN):
            return
        self.backward(LARGEUR)

    def switch_player(self):
        self.joueur = 1 if self.joueur == 2 else 2

    def get_color(self):
        return "red" if self.joueur == 1 else "yellow"

    # type_check_winner_one_direction = tuple[int, int, int, int, int] | bool

    def check_winner_column(self):  # -> type_check_winner_one_direction:
        """Vérifie s’il y a un gagnant en colonne"""
        for j, column in enumerate(self.tableau):
            for i in range(LIGNES - 3):
                if 0 != column[i] == column[i+1] == column[i+2] == column[i+3]:
                    return column[i], i, j, i + 3, j
        return False

    def check_winner_line(self):  # -> type_check_winner_one_direction:
        for i in range(LIGNES):
            for j in range(COLONNES-3):
                if 0 != self.tableau[j][i] == self.tableau[j+1][i] == self.tableau[j+2][i] == self.tableau[j+3][i]:
                    return self.tableau[j][i], i, j, i, j+3

    def check_winner_diagonal1(self):  # -> type_check_winner_one_direction:
        for i in range(LIGNES-3):
            for j in range(COLONNES-3):
                win = self.tableau[j][i] == self.tableau[j+1][i+1] == self.tableau[j+2][i+2] == self.tableau[j+3][i+3]
                is_player = self.tableau[j][i] != 0
                if win and is_player:
                    return self.tableau[j][i], i, j, i+3, j+3

    def check_winner_diagonal2(self):  # -> type_check_winner_one_direction:
        for i in range(LIGNES-3):
            for j in range(3, COLONNES):
                win = self.tableau[j][i] == self.tableau[j-1][i+1] == self.tableau[j-2][i+2] == self.tableau[j-3][i+3]
                is_player = self.tableau[j][i] != 0
                if win and is_player:
                    return self.tableau[j][i], i, j, i+3, j-3

    # type_check_winner = tuple[type_check_winner_one_direction, type_check_winner_one_direction,
    #                           type_check_winner_one_direction, type_check_winner_one_direction]

    def check_winner(self):  # -> type_check_winner:  # si ça ne marche pas, enlever le typing
        return (self.check_winner_column(), self.check_winner_line(), self.check_winner_diagonal1(),
                self.check_winner_diagonal2())

    def is_tab_full(self):
        for i in self.tableau:
            for j in i:
                if j == 0:
                    return False
        return True

    def jouer(self):
        """Joue dans la colonne sélectionnée par la tortue."""
        if self.won:  # on ne veut pas jouer si un des joueurs a gagné
            return
        if not Y_TOP - 2 <= int(self.ycor()) <= Y_TOP + 2:
            return

        # la tortue convertit les coordonnées en float, et il y a des arrondis très douteux
        colonne = (int(self.xcor()) + (LARGEUR * COLONNES) // 2 - (LARGEUR // 2) + 2)
        colonne = round(colonne, int(math.log10(LARGEUR)))
        colonne //= LARGEUR

        ligne = -1
        for i, l_ in enumerate(self.tableau[colonne]):
            if l_ == 0:
                ligne = i
        if ligne == -1:
            return

        self.color("black")
        self.jeton(ligne, colonne, self.get_color())
        self.tableau[colonne][ligne] = self.joueur

        self.switch_player()

        self.goto(int(X_TOP), int(Y_TOP))
        self.tiltangle(270)

        self.color(self.get_color())

        winner_column, winner_line, winner_diagonal1, winner_diagonal2 = self.check_winner()
        if winner_column or winner_line or winner_diagonal1 or winner_diagonal2:
            self.won = True
            self.color("black")

            for direction in [winner_column, winner_line, winner_diagonal1, winner_diagonal2]:
                if not direction:
                    continue

                winner, start_line, start_column, end_line, end_column = direction

                x = start_column * LARGEUR + X_MIN + LARGEUR // 2
                y = (LIGNES - start_line) * LARGEUR + Y_MIN - LARGEUR // 2
                self.goto(x, y)

                self.pendown()
                self.width(10)
                x = end_column * LARGEUR + X_MIN + LARGEUR // 2
                y = (LIGNES - end_line) * LARGEUR + Y_MIN - LARGEUR // 2
                self.goto(x, y)

                self.penup()

            self.hideturtle()
        elif self.is_tab_full():
            # match nul
            self.won = True
            self.hideturtle()

    @staticmethod
    def close():
        sys.exit()


game = Game()

tt.onkey(game.move_right, "Right")
tt.onkey(game.move_left, "Left")
tt.onkey(game.close, "q")
tt.onkey(game.jouer, "space")

tt.listen()
# tt.exitonclick()
tt.done()
