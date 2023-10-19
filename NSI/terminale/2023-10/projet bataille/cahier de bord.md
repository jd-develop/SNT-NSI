# Projet Bataille
* Durée&nbsp;: 3×2h
* But&nbsp;: créer un jeu de bataille

## Étape 1&nbsp;: Règles du jeu
* Bataille à deux joueurs

Un paquet de 52 cartes est distribué entre deux joueurs, qui ne prennent
pas connaissance des cartes de leur paquet.

Les joueurs sont des **Files**, la donne est constituée de deux **Piles**.

**Donne**&nbsp;: À chaque tour, chaque joueur retourne la carte au sommet de son
paquet. Le joueur qui pose la carte la plus haute (en suivant l’ordre 2-3-4-…-roi-as)
gagne la manche et place toutes les cartes sur la table dans son jeu.

**Bataille**&nbsp;: Si les cartes posées ont la même valeur, il y a
«&nbsp;bataille&nbsp;»&nbsp;: les joueurs posent la première carte de leur paquet
face cachée, puis de nouveau la première carte face visible. C’est encore une fois
le joueur avec la carte la plus haute qui récupère la donne. Si les deux cartes sont
à nouveau les mêmes, on recommence une bataille.

**Fin de partie**&nbsp;: Le joueur ayant toutes les cartes gagne. Si un joueur pose
sa dernière carte face cachée lors d’une bataille, ou que lorsqu’il la pose cela crée
une bataille, la partie est nulle.

## To-do list
### À faire
* Créer la boucle de jeu
* (s’il reste du temps) adapter pour plus de 2 joueurs
* (s’il reste du temps) faire une interface graphique

### En cours

### À tester

### Fait et testé
* Créer une classe `Card` pour représenter une carte. **Cette classe nous servira de chaînon.**
* Créer une classe `Queue` pour le paquet du joueur
* Créer une classe `Stack` pour la donne
* Créer une fonction qui créée les cartes, les mélange puis les distribue entre les joueurs
