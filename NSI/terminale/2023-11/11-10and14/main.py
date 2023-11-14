#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import random
from tree import Node

with open("liste_mots_francais.txt", "r+", encoding="utf-8") as fp:
    lignes = fp.read().split("\n")

random.shuffle(lignes)
tree = Node(lignes.pop(0))
for ligne in lignes:
    tree.add(ligne)

