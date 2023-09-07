# liste des 20 premiers carrés
squares = [i**2 for i in range(20)]
print(squares)

# add up the elements of this list
# 2 solutions
# builtin
print(sum(squares))
# loop
sum_squares = 0
for sq in squares:
    sum_squares += sq
assert sum_squares == sum(squares)

# valeurs cumulées
stat = [2, 5, 6, 7, 8, 9, 7, 8]


def cumul(tab: list[int | float]):
    """
    Renvoie le même tableau, mais chaque valeur est remplacée par la somme des premiers éléments du tableau jusqu’à
    l’élément courant
    """
    tab = tab.copy()  # on ne modifie pas le tableau d’origine
    for i in range(1, len(tab)):
        tab[i] += tab[i-1]
    return tab


assert cumul(stat) == [2, 7, 13, 20, 28, 37, 44, 52]
