#!/usr/bin/env python3
# coding:utf-8

def grille_vide() -> list[list[int]]:
    """Retourne une grille vide taille 6x7"""
    return [[0] * 7 for _ in range(6)]


def coup_possible(grille, colonne_):
    """Retourne True s'il est possible de jouer dans cette case"""
    for ligne_ in range(5, -1, -1):
        if grille[ligne_][colonne_] == 0:
            return True
    return False


def jouer(grille, colonne_, joueur):
    """Joue avec le numéro du joueur"""
    for ligne_ in range(5, -1, -1):
        if grille[ligne_][colonne_] == 0:
            grille[ligne_][colonne_] = joueur
            break


def colonne(grille, joueur):
    """Retourne True si le joueur a gagné dans une colonne, False sinon"""
    tab_renverse = [[0]*6 for _ in range(7)]
    for index_colonne in range(7):
        for index_ligne in range(6):
            tab_renverse[index_colonne][index_ligne] = grille[index_ligne][index_colonne]

    for colonne_ in tab_renverse:
        if any([[joueur]*4 == colonne_[i:i+4] for i in range(len(colonne_))]):
            # pour chaque index entre 0 et len(colonne_)-1, on vérifie si colonne_[i:i+4] (c'est-à-dire quatre
            #   caractères de la colonne à partir de l'index) est égal à 4 fois le numéro du joueur.
            # any() renvoie True si l'un des éléments est True, False sinon.
            return True
    return False


def ligne(grille, joueur):
    """Retourne True si le joueur a gagné dans une ligne, False sinon"""
    for ligne_ in grille:
        if any([[joueur] * 4 == ligne_[i:i + 4] for i in range(len(ligne_))]):
            # pour chaque index entre 0 et len(ligne_)-1, on vérifie si ligne_[i:i+4] (c'est-à-dire quatre
            #   caractères de la colonne à partir de l'index) est égal à 4 fois le numéro du joueur.
            # any() renvoie True si l'un des éléments est True, False sinon.
            return True
    return False


def diagonale(grille, joueur):
    """Retourne True si le joueur a gagné dans une diagonale, False sinon"""
    # 0 1 2 3 4 5 6
    # 0 1 2 3 4 5 6
    # 0 1 2 3 4 5 6
    # 0 1 2 3 4 5 6
    # 0 1 2 3 4 5 6
    # 0 1 2 3 4 5 6
    for i, ligne_ in enumerate(grille):
        for j, colonne_ in enumerate(ligne_):
            # attention : code très moche
            try:
                if [joueur]*4 == [grille[i+n][j+n] for n in range(4)]:
                    return True
            except IndexError:
                pass

            try:
                if [joueur]*4 == [grille[i+n][j-n] for n in range(4)]:
                    return True
            except IndexError:
                pass

            try:
                if [joueur]*4 == [grille[i-n][j+n] for n in range(4)]:
                    return True
            except IndexError:
                pass

            try:
                if [joueur]*4 == [grille[i-n][j-n] for n in range(4)]:
                    return True
            except IndexError:
                pass
            # fin du code moche
    return False


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
    # (0) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (1) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (2) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (3) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (4) │ R │ J │ R │ J │ R │ J │ R │
    #     ├───┼───┼───┼───┼───┼───┼───┤
    # (5) │ R │ J │ R │ J │ R │ J │ R │
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
            x = input("Jouer dans quelle colonne ? ")
            if x == "exit":
                break
            x = int(x)
        except Exception:
            print("Erreur")
            continue
        if not 0 <= x <= 6:
            print("Veuillez entrer un entier entre 0 et 6")
            continue
        if not coup_possible(grille, x):
            print("Vous ne pouvez pas jouer ici")
            continue
        jouer(grille, x, tour_joueur)
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
