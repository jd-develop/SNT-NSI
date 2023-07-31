# coding:utf-8
import random


def recherche(v, tab, n):
    for i in range(n):
        if tab[i] == v:
            return i
    return -1


def recherche_plus_simple(v, tab: list):
    if v not in tab:
        return -1
    else:
        return tab.index(v)


random_list = [random.randint(0, 1000) for i in range(random.randint(100, 1000))]
value_we_search_in_the_list = random.choice(random_list)
value_we_search_maybe_in_the_list = random.randint(0, 1000)
value_we_search_not_in_the_list = random.randint(1001, 9999)

print(recherche(value_we_search_in_the_list, random_list, len(random_list)))
print(recherche_plus_simple(value_we_search_in_the_list, random_list))

print(recherche(value_we_search_maybe_in_the_list, random_list, len(random_list)))
print(recherche_plus_simple(value_we_search_maybe_in_the_list, random_list))

print(recherche(value_we_search_not_in_the_list, random_list, len(random_list)))
print(recherche_plus_simple(value_we_search_not_in_the_list, random_list))
