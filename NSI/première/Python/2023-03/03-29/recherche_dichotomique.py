# coding:utf-8
"""
Recherche dichotomique d'une valeur dans un tableau non vide trié.
On scinde le tableau en deux parties pour déterminer la moitié pouvant contenir cette valeur, puis répéter la démarche
jusqu'à obtenir cette valeur ou une moitié vide traduisant son absence.
"""

tableau1 = list(range(100))
tableau2 = list(range(0, 100, 2))
tableau3 = list(range(1, 100, 2))
tableau4 = ["azerty", 'lorem', 'ipsum', "dolor", "sit", "amet"]
tableau4.sort()

valeur = 9


def dichotomie(v, tab: list, n: int = None) -> int | None:
    """Recherche par dichotomie
    `v` est la valeur cherchée
    `tab` est le tableau dans lequel on cherche
    `n` est la longueur du tableau (laisser vide pour valeur auto.)
    """
    if n is None:
        n = len(tab)

    a = 0
    b = n
    while a <= b:
        m = (a+b)//2
        if v == tab[m]:
            return m
        elif v < tab[m]:
            b = m-1
        else:
            a = m+1
    return None


print(dichotomie(valeur, tableau1))
print(dichotomie(valeur, tableau2))
print(dichotomie(valeur, tableau3))
print(dichotomie("azerty", tableau4))
