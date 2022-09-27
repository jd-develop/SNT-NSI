#!/usr/bin/env python3
# coding:utf-8
import math


def taille(n):
    """Return the length of a number n in base 10 coded in base 2 (n=45 returns 6 because 2^5 = 32 and 2^6 = 64)"""
    bits = 1
    while 2 ** bits < n:
        bits += 1
    return bits


assert taille(16) == 4
assert taille(32) == 5
assert taille(64) == 6
assert taille(45) == 6


def faster_taille(n):
    """Return the length of a number n in base 10 coded in base 2 (n=45 returns 6 because 2^5 = 32 and 2^6 = 64)"""
    return math.ceil(math.log2(n))


assert faster_taille(16) == 4
assert faster_taille(32) == 5
assert faster_taille(64) == 6
assert faster_taille(45) == 6
