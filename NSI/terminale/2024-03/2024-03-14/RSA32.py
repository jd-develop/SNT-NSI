#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Simple implementation of the RSA algorithm
import random


def prochain_premier(n: int):
    """Renvoit le premier nombre premier qui suit n"""
    p = n+1
    while not est_premier(p):
        p += 1
    return p


def est_premier(n: int):
    """Trouve si le nombre n est premier"""
    if n == 0 or n == 1:
        return False
    if n == 2:
        return True
    if n%2 == 0:
        return False
    for i in range(3, min(n, 2**16+1), 2):
        if n%i == 0:
            return False
    return True


def euclide_généralisé(a: int, b: int) -> tuple[int, int, int]:
    """Renvoit pgcd, u, v où pgcd est le PGCD de a et b, et ua+vb=r"""
    if a < b:
        a, b = b, a
    q = a//b
    r = a%b
    if r == 0:
        return b, 0, 1
    pgcd, u, v = euclide_généralisé(b, r)
    return pgcd, v, u-v*q


for i in range(1000):
    a, b = random.randint(2, 1000), random.randint(2, 1000)
    if a < b:
        a, b = b, a
    r, u, v = euclide_généralisé(a, b)
    assert r == u*a + b*v

def génère_clé():
    """
    * Tire au hasard deux nombres entre 2^31 et 2^32, et trouve avec
      `prochain_premier`, deux nombres premiers p et q.
    * Prend un nombre premier e, diviseur ni de p-1 ni q-1
    * Calcule d et b tel que de + b(p-1)(q-1) = 1
    """
    a = random.randint(2**31, 2**32)
    b = random.randint(2**31, 2**32)
    p, q = prochain_premier(a), prochain_premier(b)

    e = random.randint(2*31, 2**32)
    e = prochain_premier(e)
    while e%(p-1) == 0 or e%(q-1) == 0:
        e = random.randint(2*31, 2**32)
        e = prochain_premier(e)
    
    if e > (p-1)*(q-1):
        pgcd, d, b = euclide_généralisé(e, (p-1)*(q-1))
        assert pgcd == 1 == d*e + b*(p-1)*(q-1)
    else:
        pgcd, d, b = euclide_généralisé((p-1)*(q-1), e)
        assert pgcd == 1 == b*e + d*(p-1)*(q-1)
    d = d % ((p-1)*(q-1))
    e = e % ((p-1)*(q-1))
    
    return p*q, d, e


# TODO: à recoder
# def puissance_modulaire(M: int, e: int, pq: int) -> int:
#     res = 1
#     while e != 0:
#         if e%2 == 1:
#             res = M%pq
#         M **= 2
#         M %= pq
#         res *= M
#         res %= pq
#         e //= 2
#     return res
# 
# 
# def coder(M: int, clé: tuple[int, int, int]):
#     pq, _, e = clé
#     return puissance_modulaire(M, e, pq)
# 
# 
# def décoder(M: int, clé: tuple[int, int, int]):
#     pq, d, _ = clé
#     return puissance_modulaire(M, d, pq)
