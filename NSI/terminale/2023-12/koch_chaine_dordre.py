#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import turtle as tl


def dessin(étape: int = 1):
    chaîne = "FGGFGGFGG"
    for _ in range(étape):
        chaîne = chaîne.replace("F", "FDFGGFDF")
    # print(chaîne)
    longueur_face = ((3**5)*2)/(3**étape)
    tortue = tl.Turtle()
    if étape > 3:
        tortue.speed(0)
    tortue.penup()
    tortue.goto(-250, -160)
    tortue.pendown()
    for c in chaîne:
        # print(c)
        if c == "F":
            tortue.forward(longueur_face)
        elif c == "G":
            tortue.left(60)
        elif c == "D":
            tortue.right(60)
    

dessin(4)
tl.exitonclick()
