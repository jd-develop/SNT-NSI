#!/usr/bin/env python3
# coding:utf-8
import random

# ex19
# définir en compréhension la liste des chiffres impairs
impairs = [x for x in range(10) if x % 2 != 0]
print(impairs)

# définir en compréhension l'alphabet en minuscules
alphabet_lower = [chr(ord_) for ord_ in range(0x61, 0x61+26)]
print(alphabet_lower)


# écrire une fonction `diviseurs(n)` qui retourne la liste des diviseurs entiers du naturel n passé en paramètre
def diviseurs(n):
    if n <= 0:
        return None
    if n == 1:
        return [1]
    diviseurs_ = [1]
    for x in range(2, int(n/2 + 1)):
        if n % x == 0:
            diviseurs_.append(x)
    diviseurs_.append(n)
    return diviseurs_


print(diviseurs(1))
print(diviseurs(25))
print(diviseurs(60))
print(diviseurs(192))


# À l'aide d'une boucle et de l'instruction de commutation a, b = b, a`, écrire une fonction `reverse(list)` qui inverse
# l'ordre des éléments de la liste passée en paramètre.
def reverse(liste):
    res = liste.copy()
    for i in range(int(len(liste)/2)):
        res[i], res[-(i+1)] = res[-(i+1)], res[i]
    return res


print(reverse([]))
print(reverse([1]))
print(reverse([1, 2]))
print(reverse([1, 2, 3]))
print(reverse([1, 2, 3, 4]))
print(reverse([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]))
print(reverse([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]))
print(reverse([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]))


# Écrire une fonction `reverse2(liste)` qui retourne une liste construite en compréhension dont les éléments sont dans
# l'ordre inverse de ceux de la liste passée en paramètre
def reverse2(liste):
    return [liste[-i] for i in range(1, len(liste)+1)]


print(reverse2([]))
print(reverse2([1]))
print(reverse2([1, 2]))
print(reverse2([1, 2, 3]))
print(reverse2([1, 2, 3, 4]))
print(reverse2([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]))
print(reverse2([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]))
print(reverse2([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]))

for i_ in range(100):
    random_list = [i for i in range(random.randint(10, 100))]
    assert reverse(random_list) == reverse2(random_list), f"\n          {random_list=}" \
                                                          f"\n {reverse(random_list)=}" \
                                                          f"\n{reverse2(random_list)=}"
