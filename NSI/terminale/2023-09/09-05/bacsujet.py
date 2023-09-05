#!/urs/bin/env python3
# coding:utf-8
import random


def convertir(tab: list[int]):
    """
    tab est un tableau d'entiers, dont les éléments sont 0 ou 1,
    et représentant un entier écrit en binaire.
    Renvoie l'écriture décimale de l'entier positif dont la
    représentation binaire est donnée par le tableau tab
    """
    # current_power = 0
    current_power = len(tab)-1
    result = 0
    for k_ in tab:
        assert k_ in [1, 0], "erreur : l’argument tab doit être une liste de nombres égaux à 0 ou 1."
        result += k_ * 2 ** current_power
        current_power -= 1
    # for i in range(len(tab)-1, -1, -1):
    #     assert tab[i] in [1, 0], "erreur : l’argument tab doit être une liste de nombres égaux à 0 ou 1."
    #     result += tab[i] * 2**current_power
    #     current_power += 1
    return result


assert convertir([0, 1, 0, 0, 1, 1]) == 19, "erreur fonction convertir"
assert convertir([1, 0, 1, 0, 0, 1, 1]) == 83, "erreur fonction convertir"
assert convertir([1, 0, 0, 0, 0, 0, 1, 0]) == 130, "erreur fonction convertir"
assert convertir([]) == 0, "erreur fonction convertir"


def tri_insertion(tab):
    n = len(tab)
    for i in range(1, n):
        valeur_insertion = tab[i]
        # la variable `j` est utilisée pour déterminer où placer la valeur à insérer
        j = i
        # tant qu'on n’a pas trouvé la place de l'élément à insérer,
        # on décale les valeurs du tableau vers la droite
        while j > 0 and valeur_insertion < tab[j-1]:
            tab[j] = tab[j-1]
            j -= 1
        tab[j] = valeur_insertion
    return tab


# basics
liste = [9, 5, 8, 4, 0, 2, 7, 1, 10, 3, 6]
tri_insertion(liste)
assert liste == [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], "erreur tri insertion"
for k in range(10):
    liste = [random.randint(-100, 100) for i in range(50)]
    sorted_list = sorted(liste)
    assert tri_insertion(liste) == sorted_list, "erreur tri insertion"

# edge cases
assert tri_insertion([1]) == [1]
assert tri_insertion([2, 1]) == [1, 2]
assert tri_insertion([1, 1]) == [1, 1]
assert tri_insertion([1, 3, 2]) == [1, 2, 3]
assert tri_insertion([1, 2, 1]) == [1, 1, 2]
assert tri_insertion([1, -2, 1]) == [-2, 1, 1]
assert tri_insertion([2.6 for i in range(100)]) == [2.6 for j in range(100)]
l_ = [random.random()+random.randint(-5, 5) for k in range(100)]
l_sorted = sorted(l_)
assert tri_insertion(l_) == l_sorted
assert tri_insertion([4e10, -3e100, 2e25]) == [-3e100, 4e10, 2e25]
