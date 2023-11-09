#!/usr/bin/env python3
# -*- coding:utf-8 -*-

def rendu_récursif(somme, pieces):
    if somme == 0:
        return ()

    pieces.sort(reverse=True)

    solutions = []
    for piece in pieces:
        if somme >= piece:
            solutions.append((piece,) + rendu_récursif(somme-piece, pieces))
    meilleure_solution = 0
    longueur_meilleure_solution = len(solutions[0])
    for i, solution in enumerate(solutions):
        if len(solution) < longueur_meilleure_solution:
            meilleure_solution = i
            longueur_meilleure_solution = len(solution)

    return solutions[meilleure_solution]


def rendu_glouton(somme: int, pieces: list[int]):
    solution = ()
    pieces.sort(reverse=True)
    for piece in pieces:
        while somme >= piece:
            solution += (piece,)
            somme -= piece
    return solution


def rendu_mémoire(somme, pieces):
    connus = [None] * (somme+1)
    connus[0] = ()
    appels = 0
    pieces.sort(reverse=True)

    def rendu_mémoire_récursif(somme_, pieces_, connus_):
        nonlocal appels
        appels += 1
        if connus_[somme_] is not None:
            return connus_[somme_]
        solutions = []
        for piece in pieces_:
            if somme_ >= piece:
                solutions.append((piece,) + rendu_mémoire_récursif(somme_-piece, pieces_, connus_))
        meilleure_solution = 0
        longueur_meilleure_solution = len(solutions[0])
        for i, solution in enumerate(solutions):
            if len(solution) < longueur_meilleure_solution:
                meilleure_solution = i
                longueur_meilleure_solution = len(solution)

        return solutions[meilleure_solution]

    s = rendu_mémoire_récursif(somme, pieces, connus)
    return s


print(rendu_mémoire(13, [1, 2, 5]))
