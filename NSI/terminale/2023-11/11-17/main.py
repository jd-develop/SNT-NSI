#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import random


# factorielle récursive
def factorial(n: int) -> int:
    if n == 0:
        return 1
    return n * factorial(n - 1)


assert factorial(0) == factorial(1) == 1
assert factorial(6) == 720


# tri fusion
def merge_sort(tab: list, log=False, depth=0, discriminant=0):
    if len(tab) <= 1:
        if log:
            print(f"[{depth}][{discriminant}] longueur: {len(tab)}, donc retour sans rien faire")
        return tab
    middle = int(len(tab) // 2)
    left_tab = tab[:middle]
    right_tab = tab[middle:]
    if log:
        print(f"[{depth}][{discriminant}] Tentative de tri de {tab}, séparation en {left_tab}, {right_tab}.")

    left_tab = merge_sort(left_tab, log, depth+1, 1)
    right_tab = merge_sort(right_tab, log, depth+1, 2)

    if log:
        print(f"[{depth}][{discriminant}] Retour sur la tentative de tri de {tab}.")
        print(f"[{depth}][{discriminant}] Left a été trié en {left_tab}.")
        print(f"[{depth}][{discriminant}] Right a été trié en {right_tab}.")
        print(f"[{depth}][{discriminant}] Fusionnons.")
        print(f"[{depth}][{discriminant}] {len(left_tab)=} {len(right_tab)=}")

    final_tab = []
    i_left, i_right = 0, 0
    while len(left_tab) != i_left or len(right_tab) != i_right:
        if len(left_tab[i_left:]) == 0:
            if log:
                print(f"[{depth}][{discriminant}] Left est vide! Extension de final_tab avec right_tab")
            final_tab.extend(right_tab[i_right:])
            break
        elif len(right_tab[i_right:]) == 0:
            if log:
                print(f"[{depth}][{discriminant}] Right est vide! Extension de final_tab avec left_tab")
            final_tab.extend(left_tab[i_left:])
            break
        if left_tab[i_left] < right_tab[i_right]:
            if log:
                print(f"[{depth}][{discriminant}] {left_tab[i_left]} < {right_tab[i_right]}")
            final_tab.append(left_tab[i_left])
            i_left += 1
        else:
            if log:
                print(f"[{depth}][{discriminant}] {left_tab[i_left]} >= {right_tab[i_right]}")
            final_tab.append(right_tab[i_right])
            i_right += 1
        if log:
            print(f"[{depth}][{discriminant}]  Left: {left_tab[i_left:]}")
            print(f"[{depth}][{discriminant}] Right: {right_tab[i_right:]}")
            print(f"[{depth}][{discriminant}] Final: {final_tab}")
    if log:
        print(f"[{depth}][{discriminant}] Final renvoyé: {final_tab}")
    return final_tab


print(merge_sort([12, 56, -4, 2, 10]))
print(merge_sort([12, 56, -4, 2, 10, 12]))
print(merge_sort([0]))
print(merge_sort([]))

random_list = list(range(1000))
random.shuffle(random_list)
assert merge_sort(random_list) == list(range(1000))
