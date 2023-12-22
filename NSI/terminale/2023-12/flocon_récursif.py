#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import turtle as tl


def branche(tortue: tl.Turtle, longueur: int | float, récursion: int):
    tortue.forward(longueur)
    if récursion == 0:
        tortue.backward(longueur)
        return
    tortue.backward(longueur/3)
    tortue.left(60)
    branche(tortue, longueur/3, récursion-1)
    tortue.right(60)
    branche(tortue, longueur/3, récursion-1)
    tortue.right(60)
    branche(tortue, longueur/3, récursion-1)
    tortue.left(60)
    tortue.backward(2*longueur/3)


def flocon(longueur_face: int | float = (3**5), récursion: int = 1):
    tortue = tl.Turtle()
    if récursion > 3:
        tortue.speed(0)
    for _ in range(6):
        branche(tortue, longueur_face, récursion)
        tortue.right(60)
    

flocon(récursion=5)
tl.exitonclick()
