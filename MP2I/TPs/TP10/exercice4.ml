#!/usr/bin/env ocaml
(*
 * Cette version de exercice4.ml requiert OCaml version 5.3.0 ou ultérieure.
 * Voir exercice4compat.ml pour une version du fichier fonctionnant sur les
 * versions plus anciennes.
 * (c’est dû au fait que j’utilise des caractères comme œ dans les noms de
 * variables)
 *)

type couleur = Cœur | Carreau | Pique | Trèfle

type tête = Valet | Dame | Roi

type carte =
    | Nombre of (int * couleur)
    | Tête of (tête * couleur)
    | Joker

(* Renvoie un string correspondant à la couleur c *)
let string_of_couleur (c: couleur) : string = match c with
    | Cœur -> "cœur"
    | Carreau -> "carreau"
    | Pique -> "pique"
    | Trèfle -> "trèfle"

(* Renvoie un string correspondant à la tête t *)
let string_of_tête (t: tête) : string = match t with
    | Valet -> "Valet"
    | Dame -> "Dame"
    | Roi -> "Roi"

(* Renvoie un string correspondant à la carte ca *)
let string_of_carte (ca: carte) : string = match ca with
    | Nombre (nb, c) ->
        (if nb == 1 then "As" else string_of_int nb) ^
        " de " ^
        (string_of_couleur c)
    | Tête (t, c) -> (string_of_tête t) ^ " de " ^ (string_of_couleur c)
    | Joker -> "Joker"

(* Compare deux cartes. Renvoie -1 si la carte c1 est inférieure à la carte c2,
 * 0 si elle est égale et 1 si elle est supérieure.
 * L’ordre est le suivant :
 *   * Les cœurs sont plus petits que les carreaux qui sont plus petits que les
 *     piques qui sont plus petits que les trèfles.
 *   * Au sein d’une couleur, l’ordre est 2, 3, …, 10, valet, dame, roi, as.
 *   * Un joker est inférieur à tout
 *)
let compare_carte (c1: carte) (c2: carte) : int = match c1 with
    | Joker -> if c2 = Joker then 0 else -1
    | Nombre (nb1, couleur1) -> (match c2 with
        | Joker -> 1
        | Nombre (nb2, couleur2) ->
            if couleur1 < couleur2 then -1
            else if couleur1 > couleur2 then 1
            else if nb1 < nb2 then -1
            else if nb1 > nb2 then 1
            else 0
        | Tête (tête2, couleur2) ->
            if couleur2 < couleur1 then 1
            else -1) (* Couleur inférieure ou même couleur mais c1 nombre et c2
                      * tête *)
    | Tête (tête1, couleur1) -> (match c2 with
        | Joker -> 1
        | Nombre (nb2, couleur2) ->
            if couleur1 < couleur2 then -1
            else 1 (* couleur inféreure ou même couleur mais c1 tête et c2
                     * nombre *)
        | Tête (tête2, couleur2) ->
            if couleur1 < couleur2 then -1
            else if couleur1 > couleur2 then 1
            else if tête1 < tête2 then -1
            else if tête1 > tête2 then 1
            else 0)


(* Insère la carte c dans le jeu de cartes jeu supposé trié *)
let rec insert (c: carte) (jeu: carte list) : carte list = match jeu with
    | [] -> c::[]
    | x::q -> if compare_carte c x <= 0 then c::x::q
              else x::(insert c q)

(* Trie le jeu de cartes `jeu` par insertion *)
let rec insert_sort (jeu: carte list) : carte list = match jeu with
    | [] -> []
    | x::q -> insert x (insert_sort q)


let test () =
    assert (string_of_couleur Cœur = "cœur");
    assert (string_of_couleur Carreau = "carreau");
    assert (string_of_couleur Trèfle = "trèfle");
    assert (string_of_couleur Pique = "pique");
    assert (string_of_tête Valet = "Valet");
    assert (string_of_tête Dame = "Dame");
    assert (string_of_tête Roi = "Roi");

    assert (string_of_carte (Nombre (1, Cœur)) = "As de cœur");
    assert (string_of_carte (Nombre (2, Pique)) = "2 de pique");
    assert (string_of_carte (Nombre (5, Trèfle)) = "5 de trèfle");
    assert (string_of_carte (Nombre (10, Carreau)) = "10 de carreau");
    assert (string_of_carte (Tête (Roi, Carreau)) = "Roi de carreau");
    assert (string_of_carte (Tête (Dame, Pique)) = "Dame de pique");
    assert (string_of_carte (Tête (Valet, Trèfle)) = "Valet de trèfle");

    assert (compare_carte Joker Joker = 0);
    assert (compare_carte Joker (Nombre (7, Pique)) = -1);
    assert (compare_carte Joker (Tête (Valet, Trèfle)) = -1);

    assert (compare_carte (Nombre (1, Cœur)) (Nombre (1, Cœur)) = 0);
    assert (compare_carte (Nombre (1, Cœur)) (Nombre (2, Cœur)) = -1);
    assert (compare_carte (Nombre (2, Cœur)) (Nombre (1, Cœur)) = 1);

    assert (compare_carte (Nombre (1, Carreau)) (Nombre (1, Cœur)) = 1);
    assert (compare_carte (Nombre (1, Cœur)) (Nombre (1, Carreau)) = -1);
    assert (compare_carte (Nombre (1, Pique)) (Nombre (1, Carreau)) = 1);
    assert (compare_carte (Nombre (1, Carreau)) (Nombre (1, Pique)) = -1);
    assert (compare_carte (Nombre (1, Trèfle)) (Nombre (1, Pique)) = 1);
    assert (compare_carte (Nombre (1, Pique)) (Nombre (1, Trèfle)) = -1);

    assert (compare_carte (Nombre (10, Carreau)) (Nombre (1, Cœur)) = 1);
    assert (compare_carte (Nombre (10, Cœur)) (Nombre (1, Carreau)) = -1);
    assert (compare_carte (Nombre (10, Pique)) (Nombre (1, Carreau)) = 1);
    assert (compare_carte (Nombre (10, Carreau)) (Nombre (1, Pique)) = -1);
    assert (compare_carte (Nombre (10, Trèfle)) (Nombre (1, Pique)) = 1);
    assert (compare_carte (Nombre (10, Pique)) (Nombre (1, Trèfle)) = -1);

    assert (compare_carte (Nombre (10, Carreau)) (Tête (Valet, Cœur)) = 1);
    assert (compare_carte (Nombre (10, Cœur)) (Tête (Roi, Carreau)) = -1);
    assert (compare_carte (Nombre (10, Pique)) (Tête (Valet, Carreau)) = 1);
    assert (compare_carte (Nombre (10, Carreau)) (Tête (Dame, Pique)) = -1);
    assert (compare_carte (Nombre (10, Trèfle)) (Tête (Valet, Pique)) = 1);
    assert (compare_carte (Nombre (10, Pique)) (Tête (Valet, Trèfle)) = -1);

    assert (compare_carte (Nombre (1, Cœur)) Joker = 1);
    assert (compare_carte (Nombre (10, Pique)) Joker = 1);

    assert (compare_carte (Tête (Valet, Cœur)) Joker = 1);
    assert (compare_carte (Tête (Roi, Pique)) Joker = 1);

    assert (compare_carte (Tête (Valet, Cœur)) (Nombre (3, Pique)) = -1);
    assert (compare_carte (Tête (Valet, Pique)) (Nombre (3, Cœur)) = 1);
    assert (compare_carte (Tête (Roi, Pique)) (Nombre (3, Pique)) = 1);

    assert (compare_carte (Tête (Valet, Cœur)) (Tête (Valet, Pique)) = -1);
    assert (compare_carte (Tête (Valet, Pique)) (Tête (Valet, Cœur)) = 1);
    assert (compare_carte (Tête (Valet, Pique)) (Tête (Roi, Cœur)) = 1);
    assert (compare_carte (Tête (Dame, Pique)) (Tête (Valet, Cœur)) = 1);
    assert (compare_carte (Tête (Dame, Carreau)) (Tête (Valet, Trèfle)) = -1);

    assert (compare_carte (Tête (Dame, Pique)) (Tête (Valet, Pique)) = 1);
    assert (compare_carte (Tête (Valet, Pique)) (Tête (Dame, Pique)) = -1);
    assert (compare_carte (Tête (Roi, Pique)) (Tête (Valet, Pique)) = 1);
    assert (compare_carte (Tête (Valet, Pique)) (Tête (Roi, Pique)) = -1);
    assert (compare_carte (Tête (Roi, Pique)) (Tête (Dame, Pique)) = 1);
    assert (compare_carte (Tête (Dame, Pique)) (Tête (Roi, Pique)) = -1);

    assert (compare_carte (Tête (Dame, Carreau)) (Tête (Valet, Carreau)) = 1);
    assert (compare_carte (Tête (Valet, Carreau)) (Tête (Dame, Carreau)) = -1);
    assert (compare_carte (Tête (Roi, Carreau)) (Tête (Valet, Carreau)) = 1);
    assert (compare_carte (Tête (Valet, Carreau)) (Tête (Roi, Carreau)) = -1);
    assert (compare_carte (Tête (Roi, Carreau)) (Tête (Dame, Carreau)) = 1);
    assert (compare_carte (Tête (Dame, Carreau)) (Tête (Roi, Carreau)) = -1);
    assert (compare_carte (Tête (Dame, Carreau)) (Tête (Roi, Cœur)) = 1);

    assert (insert (Tête (Dame, Carreau)) [] = [Tête (Dame, Carreau)]);
    assert (insert (Nombre (5, Pique)) [
        Nombre (1, Cœur);
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (4, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
    ] = [
        Nombre (1, Cœur);
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
    ]);
    assert (insert (Nombre (5, Pique)) [
        Nombre (1, Cœur);
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
    ] = [
        Nombre (1, Cœur);
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
    ]);
    assert (insert_sort [] = []);
    assert (insert_sort [Joker] = [Joker]);
    assert (insert_sort [Nombre (4, Pique)] = [Nombre (4, Pique)]);
    assert (insert_sort [Tête (Roi, Cœur)] = [Tête (Roi, Cœur)]);
    assert (insert_sort [
        Nombre (4, Pique);
        Nombre (5, Pique);
        Tête (Roi, Trèfle);
        Tête (Valet, Cœur);
        Joker;
        Nombre (6, Pique);
        Nombre (1, Cœur);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
        Nombre (2, Cœur);
        Joker;
        Nombre (6, Pique);
    ] = [
        Joker;
        Joker;
        Nombre (1, Cœur);
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
        Tête (Roi, Trèfle);
    ]);

    print_endline "Tous les tests de l’exercice 4 ont réussi."
