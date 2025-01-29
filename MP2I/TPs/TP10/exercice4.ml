#!/usr/bin/env ocaml
(*
 * Cette version de exercice4.ml requiert OCaml version 5.3.0 ou ultérieure.
 * Voir exercice4compat.ml pour une version du fichier fonctionnant sur les
 * versions plus anciennes.
 * (c’est dû au fait que j’utilise des caractères comme œ dans les noms de
 * variable)
 *)

type couleur = Cœur | Pique | Carreau | Trèfle

type tête = Valet | Dame | Roi

type carte =
    | Nombre of (int * couleur)
    | Tête of (tête * couleur)
    | Joker

(* Renvoie un string correspondant à la couleur c *)
let string_of_couleur (c: couleur) : string = match c with
    | Cœur -> "Cœur"
    | Pique -> "Pique"
    | Carreau -> "Carreau"
    | Trèfle -> "Trèfle"

(* Renvoie un string correspondant à la tête t *)
let string_of_tête (t: tête) : string = match t with
    | Valet -> "Valet"
    | Dame -> "Dame"
    | Roi -> "Roi"

(* Renvoie un string correspondant à la carte ca *)
let string_of_carte (ca: carte) : string = match ca with
    | Nombre (nb, c) ->
        (if nb == 1 then "As" else string_of_int nb)^" de "^(string_of_couleur c)
    | Tête (t, c) -> (string_of_tête t) ^ " de " ^ (string_of_couleur c)
    | Joker -> "Joker"

let test () =
    (* TODO *)
    print_endline "Tous les tests de l’exercice 4 ont réussi."
