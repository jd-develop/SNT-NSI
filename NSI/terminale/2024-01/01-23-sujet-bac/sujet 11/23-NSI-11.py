## Exercice 2

liste = [9, 5, 8, 4, 0, 2, 7, 1, 10, 3, 6]
liste_triée_pour_tester = sorted(liste)


def tri_insertion(tab):
    n = len(tab)
    for i in range(1, n):
        valeur_insertion = tab[i]
        # la variable j sert à déterminer où placer la valeur à ranger
        j = i
        # tant qu'on a pas trouvé la place de l'élément à insérer
        # on décale les valeurs du tableau vers la droite
        while j > 0 and valeur_insertion < tab[j-1]:
            tab[j] = tab[j-1]
            j -= 1
        tab[j] = valeur_insertion


tri_insertion(liste)
assert liste == liste_triée_pour_tester

liste = []
tri_insertion(liste)
assert liste == []

import random
for i in range(1000):
    liste = [random.randint(-100, 100) for _ in range(random.randint(0, 100))]
    liste_triée = sorted(liste)
    tri_insertion(liste)
    assert liste == liste_triée
