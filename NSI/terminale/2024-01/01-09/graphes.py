#!/usr/bin/env python3
# -*- coding:utf-8 -*-


def liste_sommets_vers_matrice_adjacents(liste_sommets: dict[str, list[str]]) -> tuple[list[str], list[list[int]]]:
    """Convertit une liste de sommets en une matrice d’adjacents"""
    nom_sommets: list[str] = []
    for sommet, voisins in liste_sommets.items():
        nom_sommets.append(sommet)

    matrice = [[0]*len(nom_sommets) for i in range(len(nom_sommets))]
    for sommet, voisins in liste_sommets.items():
        indice_sommet = nom_sommets.index(sommet)
        for voisin in voisins:
            indice = nom_sommets.index(voisin)
            matrice[indice_sommet][indice] += 1

    return nom_sommets, matrice


def matrice_adjacents_to_latex(matrice: list[list[int]]) -> list[str]:
    """Renvoie le code LaTeX pour générer cette matrice"""
    latex = ["\\left(\n", "\\begin{matrix}\n"]
    for line in matrice:
        current_line = ""
        for number in line:
            current_line += str(number) + " & "
        current_line = current_line[:-2] + "\\\\ \n"
        latex.append(current_line)
    latex.append("\\end{matrix}\n")
    latex.append("\\right)\n")
    return latex


dict_sommets = {
    "A": ["B", "B", "D"],
    "B": ["A", "A", "C", "C", "D"],
    "C": ["B", "B", "D"],
    "D": ["A", "B", "C"]
}
sommets, matrice = liste_sommets_vers_matrice_adjacents(dict_sommets)
print(sommets, matrice)
latex_lines = matrice_adjacents_to_latex(matrice)
print(latex_lines)
with open("matrice.tex", "w+", encoding="utf-8") as texf:
    texf.writelines(latex_lines)

