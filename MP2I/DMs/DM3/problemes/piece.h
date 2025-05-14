#ifndef PIECE_H
#define PIECE_H

/* structure des pièces sans rotation et sans symétrie */
typedef struct {
    char nom;
    int n_ligne;
    int n_col;
    int n_rot;
    int tab[4][4];
} Piece;

/* liste des pièces */
extern int n_pieces;
extern Piece pieces[];

/* Renvoie la rotation de p (sens trigonométrique) */
Piece rotation(Piece p);

/* Renvoie la symétrie de p (axe vertical) */
Piece symetrie(Piece p);
