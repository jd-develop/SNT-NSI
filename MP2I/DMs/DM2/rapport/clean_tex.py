#!/usr/bin/env python3
# -*- coding:utf-8 -*-

"""
Remplace ceci :

\\begin{center}
\\begin{quote}

et ceci :

\\end{quote}
\\end{center}

par les équivalents sans l’environnement quote.
Lit out/rapport.tex et écrit dans out/rapport.tex
"""

with open("out/rapport.tex", "r") as fp:
    rapport = fp.read()

rapport = rapport.replace("\\begin{center}\n\\begin{quote}", "\\begin{center}")
rapport = rapport.replace("\\end{quote}\n\\end{center}", "\\end{center}")

with open("out/rapport.tex", "w") as fp:
    fp.write(rapport)

