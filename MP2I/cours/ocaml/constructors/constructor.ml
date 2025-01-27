#!/usr/bin/env ocaml
(* Note: requires OCaml >=5.3 *)

type couleur =
    | Rouge
    | Vert
    | Bleu
    | Noir
    | QuatreCouleurs

type fourniture =
    | Gomme
    | Stylo of couleur (* couleur *)
    | Règle of int * bool (* longueur et centrée ou non *)


let s1 = Stylo Rouge
let s2 = Stylo Bleu
let r1 = Règle (8, true)
let g1 = Gomme

let print_couleur (c: couleur): unit = match c with
    | Rouge -> print_string "rouge"
    | Vert -> print_string "vert"
    | Bleu -> print_string "bleu"
    | Noir -> print_string "noir"
    | QuatreCouleurs -> print_string "quatre couleurs"

let rec print_trousse (trousse: fourniture list) : unit = match trousse with
    | [] -> ()
    | Gomme::q -> print_endline "Une gomme"; print_trousse q
    | Stylo s::q -> print_string "Un stylo "; print_couleur s; print_newline ();
        print_trousse q
    | Règle (l, c)::q -> print_string
        (if c then "Une règle centrée de " else "Une règle non centrée de de ");
        print_int l; print_endline " centimètres"; print_trousse q
