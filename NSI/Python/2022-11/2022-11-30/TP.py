#!/usr/bin/env python3
# coding:utf-8

# ┌─┬┐  ╔═╦╗  ╓─╥╖  ╒═╤╕
# │ ││  ║ ║║  ║ ║║  │ ││
# ├─┼┤  ╠═╬╣  ╟─╫╢  ╞═╪╡
# └─┴┘  ╚═╩╝  ╙─╨╜  ╘═╧╛
# ┌───────────────────┐
# │  ╔═══╗ Some Text  │▒
# │  ╚═╦═╝ in the box │▒
# ╞═╤══╩══╤═══════════╡▒
# │ ├──┬──┤           │▒
# │ └──┴──┘           │▒
# └───────────────────┘▒
#  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒

def grille_vide() -> list[list[int]]:
    """Retourne une grille vide taille 3x3"""
    return [[0] * 3 for _ in range(3)]


def coup_possible(grille, ligne_, colonne_):
    """Retourne True s'il est possible de jouer dans cette case"""
    return grille[ligne_][colonne_] == 0


def jouer(grille, ligne_, colonne_, joueur):
    """Joue avec le numéro du joueur"""
    grille[ligne_][colonne_] = joueur


def colonne(grille, joueur):
    """Retourne True si le joueur a gagné dans une colonne, False sinon"""
    for index_colonne in range(3):
        produit_colonne = 1
        for index_ligne in range(3):
            produit_colonne *= grille[index_ligne][index_colonne]
        if produit_colonne == joueur**3:
            return True
    return False


def ligne(grille, joueur):
    """Retourne True si le joueur a gagné dans une ligne, False sinon"""
    for index_ligne in range(3):
        produit_ligne = 1
        for index_colonne in range(3):
            produit_ligne *= grille[index_ligne][index_colonne]
        if produit_ligne == joueur**3:
            return True
    return False


def diagonale(grille, joueur):
    """Retourne True si le joueur a gagné dans une diagonale, False sinon"""
    produit_diagonale = grille[0][0] * grille[1][1] * grille[2][2]
    if produit_diagonale == joueur ** 3:
        return True
    produit_diagonale2 = grille[0][2] * grille[1][1] * grille[2][0]
    if produit_diagonale2 == joueur ** 3:
        return True
    return False


def grille_pleine(grille):
    """Retourne True si la grille est pleine (partie nulle), False sinon"""
    for x in range(3):
        for y in range(3):
            if grille[x][y] == 0:
                return False
    return True


def reinitialiser(grille):
    """Remet toutes les cases de la grille à 0. Ne retourne rien"""
    for x in range(3):
        for y in range(3):
            grille[x][y] = 0


def print_grille(grille):
    #      0   1   2
    # 0  | X | O | X |
    # 1  | X | O | X |
    # 2  | X | O | X |
    print("      0   1   2")
    for i, ligne_ in enumerate(grille):
        print(" " + str(i) + "  ", end="|")
        for colonne_ in ligne_:
            print(" X " if colonne_ == 1 else " O " if colonne_ == 2 else "   ", end="|")
        print()


def main():
    """Main loop"""
    grille = grille_vide()
    nom_joueur1 = input("Nom du joueur 1 : ")
    nom_joueur2 = input("Nom du joueur 2 : ")

    tour_joueur = 1

    while True:
        print_grille(grille)

        print(f"C'est à {nom_joueur1 if tour_joueur == 1 else nom_joueur2} de jouer.")
        try:
            x, y = eval(input("Jouer dans quelle case ? ligne, colonne : "))
        except Exception:
            print("Erreur")
            continue
        if not 0 <= x <= 2 or not 0 <= y <= 2:
            print("Veuillez entrer des entiers entre 0 et 2")
            continue
        if not coup_possible(grille, x, y):
            print("Vous ne pouvez pas jouer ici")
            continue
        jouer(grille, x, y, tour_joueur)
        if colonne(grille, tour_joueur) or ligne(grille, tour_joueur) or diagonale(grille, tour_joueur):
            print(f"{nom_joueur1 if tour_joueur == 1 else nom_joueur2} a gagné !")
            print("Nouvelle partie.")
            reinitialiser(grille)
            tour_joueur = 1
            continue
        if grille_pleine(grille):
            print("Match nul...")
            print("Nouvelle partie.")
            reinitialiser(grille)
            tour_joueur = 1
            continue
        tour_joueur = 1 if tour_joueur == 2 else 2


main()
