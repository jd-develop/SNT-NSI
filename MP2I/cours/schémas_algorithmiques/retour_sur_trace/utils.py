#!/usr/bin/env python3
# -*- coding:utf-8 -*-
# Note: all of this code was written and published by Misureta under
# WTFPL. I modified some of the parts and release it under GNU GPL v3.0
from os import get_terminal_size


taille_terminal = get_terminal_size()


def centrer_texte(texte: str) -> str:
    """
    Centre le texte horizontalement par rapport à la taille du terminal,
    même si le texte est stylisé (couleur, gras…)
    """
    taille_terminal = get_terminal_size()
    colonnes = taille_terminal.columns
    longueur = len(texte)
    # Il ne faut pas compter les caractères invisibles
    # qui servent à styliser le texte
    invisible = False
    for caractère in texte:
        if invisible:
            longueur -= 1
            if caractère == "m":
                invisible = False
        elif caractère == "\x1b":
            invisible = True
            longueur -= 1
    espaces = (colonnes - longueur) // 2
    return " " * espaces + texte + " " * (espaces - 1)


def affichage_case(case: int | None):
    """
    Renvoie la chaîne de caractères qui correspond à une case
    """
    return str(case) if isinstance(case, int) else " "


def afficher_grille(
    grille: list[list[int | None]] | None,
    ligne_sélectionnée: int = -1,
    colonne_sélectionnée: int = -1,
    possibilités: int = 0,
    total_max: int = 0
):
    """
    Affiche la grille en cours
    """
    if grille is None:
        print("Pas de solution !")
        return
    global taille_terminal
    print("\x1b[H\x1b[?25l")
    print()
    print()
    taille_terminal_vieux = taille_terminal
    taille_terminal = get_terminal_size()

    if taille_terminal != taille_terminal_vieux:
        # On efface l’écran si la taille a changé et on met à jour la taille
        print("\x1bc")

    largeur = taille_terminal.columns - 2
    hauteur = taille_terminal.lines - 7
    # La taille est au minimum 1 grâce à ajuster_taille_terminal()
    # Elle est définie comme étant le plus grand carré de taille multiple de 9
    taille = min(largeur // 18, hauteur // 9)
    # Pour chaque ligne du tableau…
    for i, ligne in enumerate(grille):
        # …pour chaque fois qu’on va devoir répéter les lignes…
        # (chaque case du tableau peut en réalité prendre plusieurs lignes du
        # terminal, si le terminal est grand)
        for mult_ligne in range(taille):
            # On centre le tableau (mais pas les nombres sur le côté)
            print(" " * ((largeur - 18 * taille) // 2 - 1), end="")
            # …pour chaque case…
            for j, case in enumerate(ligne):
                # Une case sur deux horizontalement et verticalement, on change
                # son fond en gris (pour obtenir un damier)
                if j//3 in [0, 2] and i//3 in [0, 2] or i//3 == j//3 == 1:
                    if (i+j)%2 == 0:
                        # Case grisée
                        print("\x1b[100m", end="")
                    else:
                        print("\x1b[48;5;244m\x1b[30m", end="")
                elif (i+j)%2 == 0:
                    print("\x1b[48;5;237m", end="")
                # Si la case est la case sélectionnée,
                # on change son fond en rouge
                sélectionnée = (
                    i == ligne_sélectionnée
                    and j == colonne_sélectionnée
                )
                # Si la case est la case sélectionnée, on change son fond en
                # la couleur de sélection du terminal (généralement blanc)
                if sélectionnée:
                    print("\x1b[49m\x1b[39m\x1b[7m", end="")
                # On affiche le pion seulement sur les cases du milieu de la
                # case verticalement, sinon on met des espaces.
                # De plus, on centre horizontalement le pion dans la case
                print(
                    f"{' ' * ((taille - 1) // 2) * 2} "
                    f"{affichage_case(case) if mult_ligne == taille // 2 else ' '}"
                    f"{' ' * (taille // 2) * 2}",
                    end="",
                )
                # On désactive la couleur de sélection si elle était activée
                # plus tôt
                if sélectionnée:
                    print("\x1b[27m\x1b[39m", end="")
                if j//3 in [0, 2] and i//3 in [0, 2] or i//3 == j//3 == 1 \
                        or (i+j)%2 == 0:
                    # On revient à une couleur d’arrière-plan et de texte
                    # normale
                    print("\x1b[49m\x1b[39m", end="")
            print()

    if total_max != 0:
        print(f"{possibilités*100/total_max:4f} %")
        barre_chargement_largeur = int((possibilités/total_max)*largeur)
        print("[" + barre_chargement_largeur*">" + (largeur - barre_chargement_largeur)*" " + "]")
