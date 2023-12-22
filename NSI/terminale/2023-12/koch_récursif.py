#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import turtle as tl


def face(tortue: tl.Turtle, longueur: int | float, récursion: int):
    if récursion == 0:
        tortue.forward(longueur)
        return
    face(tortue, longueur/3, récursion-1)
    tortue.left(60)
    face(tortue, longueur/3, récursion-1)
    tortue.right(120)
    face(tortue, longueur/3, récursion-1)
    tortue.left(60)
    face(tortue, longueur/3, récursion-1)


def flocon(longueur_face: int | float = (3**5)*2, récursion: int = 1):
    tortue = tl.Turtle()
    if récursion > 3:
        tortue.speed(0)
    tortue.penup()
    tortue.goto(-250, 160)
    tortue.pendown()
    face(tortue, longueur_face, récursion)
    tortue.right(120)
    face(tortue, longueur_face, récursion)
    tortue.right(120)
    face(tortue, longueur_face, récursion)
    tortue.right(120)


flocon(récursion=4)
tl.exitonclick()
