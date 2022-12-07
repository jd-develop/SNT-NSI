#!/usr/bin/env python3
# coding:utf-8
# TODO: faire tomber la pièce en bas de la grille

def grille_vide() -> list[list[int]]:
    """Retourne une grille vide taille 6x7"""
    return [[0] * 7 for _ in range(6)]


def coup_possible(grille, ligne_, colonne_):
    """Retourne True s'il est possible de jouer dans cette case"""
    return grille[ligne_][colonne_] == 0


def jouer(grille, ligne_, colonne_, joueur):
    """Joue avec le numéro du joueur"""
    grille[ligne_][colonne_] = joueur


def colonne(grille, joueur):
    """Retourne True si le joueur a gagné dans une colonne, False sinon"""
    tab_renverse = [[0]*6 for _ in range(7)]
    for index_colonne in range(7):
        for index_ligne in range(6):
            tab_renverse[index_colonne][index_ligne] = grille[index_ligne][index_colonne]

    for colonne_ in tab_renverse:
        n = len(colonne_)
        if any([[joueur]*4 == colonne_[i:i+n] for i in range(len(colonne_)-n)]):
            # pour chaque index entre 0 et len(colonne_)-n-1 :
            # on vérifie si ligne[i:i+n] (c'est-à-dire quatre caractères de la colonne à partir de l'index)
            # est égal à 4 fois le numéro du joueur.
            # any() renvoie True si l'un des éléments est True, False sinon.
            return True
    return False


def ligne(grille, joueur):
    """Retourne True si le joueur a gagné dans une ligne, False sinon"""
    for ligne_ in grille:
        n = len(ligne_)
        if any([[joueur]*4 == ligne_[i:i+n] for i in range(len(ligne_)-n)]):
            # pour chaque index entre 0 et len(ligne_)-n-1 :
            # on vérifie si ligne[i:i+n] (c'est-à-dire quatre caractères de la ligne à partir de l'index)
            # est égal à 4 fois le numéro du joueur.
            # any() renvoie True si l'un des éléments est True, False sinon.
            return True
    return False


def diagonale(grille, joueur):
    """Retourne True si le joueur a gagné dans une diagonale, False sinon"""
    return False  # TODO: implémenter ça


def grille_pleine(grille):
    """Retourne True si la grille est pleine (partie nulle), False sinon"""
    for x in range(6):
        for y in range(7):
            if grille[x][y] == 0:
                return False
    return True


def reinitialiser(grille):
    """Remet toutes les cases de la grille à 0. Ne retourne rien"""
    for x in range(6):
        for y in range(7):
            grille[x][y] = 0


def print_grille(grille):
    #       0   1   2   3   4   5   6
    #     ┌───┬───┬───┬───┬───┬───┬───┐
    # (1) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (2) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (3) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (4) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (5) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (6) │ R │ J │ R │ J │ R │ J │ R │
    #     └───┴───┴───┴───┴───┴───┴───┘

    print("       0   1   2   3   4   5   6")
    print("     ┌───┬───┬───┬───┬───┬───┬───┐")
    for i, ligne_ in enumerate(grille):
        print("     ", end="│")
        for colonne_ in ligne_:
            print(" R " if colonne_ == 1 else " J " if colonne_ == 2 else "   ", end="│")
        print()
        if i != 5:
            print("     ├───┼───┼───┼───┼───┼───┼───┤")
    print("     └───┴───┴───┴───┴───┴───┴───┘")


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
        if not 0 <= x <= 6 or not 0 <= y <= 6:
            print("Veuillez entrer des entiers entre 0 et 6")
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
