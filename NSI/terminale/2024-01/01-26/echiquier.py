#!/usr/bin/env python3
# -*- coding=utf-8 -*-

def cavalier2dot(n: int) -> str:
    """
    Génère le code dot pour afficher le graphe des déplacements possibles d’un cavalier
    sur un échiquier de taille n×n
    """
    assert n > 0
    assert n <= 26
    # d’abord, générer une matrice de toutes les cases
    cases: list[list[str]] = []
    for i in range(n):
        ligne: list[str] = []
        for j in range(n):
            lettre = chr(ord("A")+i)
            chiffre = str(j+1)
            ligne.append(lettre+chiffre)
        cases.append(ligne)
    # dict des déplacements possibles, sous la forme :
    # {
    #    "A1": ["A2", "A3"]
    # }
    # etc.
    deplacements: dict[str, list[str]] = {}
    for i, ligne in enumerate(cases):
        for j, case in enumerate(ligne):
            deplacements_possibles: list[tuple[int, int]] = [(-1, -2), (-1, 2), (1, -2), (1, 2)]
            deplacements_possibles.extend([(-2, -1), (-2, 1), (2, -1), (2, 1)])
            deplacements[case] = []
            for i_prime, j_prime in deplacements_possibles:
                if i_prime+i < 0 or j_prime+j < 0:
                    continue
                if i_prime+i >= len(cases):
                    continue
                if j_prime+j >= len(ligne):
                    continue
                lettre = chr(ord("A")+i+i_prime)
                chiffre = str(j+1+j_prime)
                deplacements[case].append(lettre+chiffre)
    
    # code dot
    code = "graph G { graph[bgcolor=slategray3]\n\n"
    already_did: list[tuple[str, str]] = []
    for case, _ in deplacements.items():
        code += "\t" + case + "\n"
    code += "\n"
    for case, voisins in deplacements.items():
        did = 0
        for v in voisins:
            if (v, case) in already_did:
                continue
            already_did.append((case, v))
            already_did.append((v, case))
            code += f"\t{case} -- {v}\n"
            did += 1
        if did != 0:
            code += "\n"
    
    code += "}"
    return code
