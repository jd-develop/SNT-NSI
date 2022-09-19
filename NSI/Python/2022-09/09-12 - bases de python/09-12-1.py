#!/usr/bin/env python3
# -*- coding:utf-8 -*-


def max_(a, b):
    """Retourne le plus grand des deux nombres a et b."""
    return a if a > b else b


# exercice 4
def min_(a, b):
    """Retourne le plus petit des deux nombres a et b."""
    return a if a < b else b


# exercice 5
def division(a, b):
    """Retourne le quotient et le reste de la division de a par b."""
    quotient = a//b
    reste = a % b
    assert quotient*b + reste == a
    return quotient, reste


# exercice 6
import math


def distance(x_a, y_a, x_b, y_b):
    # distance(1, 3, 5, 6) = 5.0
    return math.sqrt((x_b - x_a)**2 + (y_b - y_a)**2)


# exercice 12
d, e, f = 0, 1, 2


def g():
    d = 3
    print(d, e, f)


def h():
    e = 4
    global f
    f = 5
    print(d, e, f)


g()
h()
print(d, e, f)


# I/O
# name = input("Name: ")
# age = int(input("Age: "))
# taille = int(input("Taille: "))
# print(f"Nom: {name}, Age: {age}, Taille: {taille}")


# exercice 13
def estPair(n):
    return n % 2 == 0


def estImpair(n):
    return not estPair(n)


# exercice 14
def is_leap_year(year):
    if year % 400 == 0:
        return True
    elif year % 4 == 0 and year % 100 != 0:
        return True
    else:
        return False


# exercice 15
def min3(a, b, c):
    """Retourne le plus petit des 3 nombres a, b et c."""
    if a < b and a < c:
        return a
    elif b < a and b < c:
        return b
    else:
        return c


# exercice 17
print("Chiffres pairs: ", end=" ")
for i in range(0, 10, 2):
    print(i, end=" ")
print()


# exercice 18
def somme(n):
    """Retourne 1+2+3+...+n. On part du principe que n ≤ 1"""
    # somme(10) = 55
    s = 0
    for i_ in range(1, n+1):
        s += i_
    return s


assert somme(10) == 55


# exercice 19
def factorielle(n):
    """Retourne n!. On part du principe que n ≤ 1"""
    f_ = 1
    for i_ in range(1, n + 1):
        f_ *= i_
    return f_


assert factorielle(5) == 120


# exercice 20
def puissance(a, n):
    """Retourne a ** n à l'aide d'une boucle 'for'"""
    b = 1
    for i_ in range(n):
        b *= a
    return b


assert puissance(165, 234) == 165 ** 234


# exercice 21
def riz():
    """Retourne le nombre de grains de riz que le roi Belkib dû offrir à Sissa (inventeur du jeu d'échecs)
    Sissa lui a demandé 1 grain sur la 1ere case, 2 sur la deuxième, 4 sur la troisième et ainsi de suite en doublant
    à chaque case."""
    grains = 0
    for i_ in range(64):
        grains += 2**i_
    return grains


print(riz())


# break
def premier_diviseur(n):
    i_ = n
    for i_ in range(2, n+1):
        if n % i_ == 0:
            break
    return i_


assert premier_diviseur(851) == 23


# exercice 22
def rebonds(hauteur):
    rebonds_ = 0
    while hauteur >= 1:
        rebonds_ += 1
        hauteur *= 3/4
    return rebonds_


# exercice 23
def nombreDeChiffres(n: int):
    return len(str(abs(n)))
