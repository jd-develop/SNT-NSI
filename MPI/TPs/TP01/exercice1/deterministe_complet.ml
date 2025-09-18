#!/usr/bin/env utop

#use "compagnon_automates.ml";;

(* Renvoie le numéro correspondant à la lettre c, c étant une lettre sans
 * diacritiques de l’alphabet latin (i.e. appartenant à la table ASCII).
 * La numérotation commence à 0 : a->0, b->1, …, z->25 *)
let int_of_letter (c: char) : int =
  if 0x61 <= int_of_char c && int_of_char c <= 0x7a then
    int_of_char c - 0x61
  else
    failwith (
      "int_of_letter: le caractère donné n’est pas une lettre minuscule de " ^
      "l’alphabet latin sans diacritiques."
    )

(* Étant donné un automate a, un état q et une lettre l, renvoie l’état q'
 * atteint grâce à la transition (q, a, q') *)
let delta (a: automate_d) (q: int) (l: char) : int =
  a.trans.(q).(int_of_letter l)

(* Étant donné un automate a, un état q et un mot w, renvoie l’état q'
 * atteint en lisant le mot w en partant de q dans a. *)
let rec delta_etoile (a: automate_d) (q: int) (w: string) : int =
  let n = String.length w in
  if n = 0 then
    q
  else
    delta_etoile a (delta a q w.[0]) (String.sub w 1 (n-1))

(* Étant donné un automate a et un mot w, renvoie true si w est accepté par a
 * et false sinon *)
let accepte (a: automate_d) (w: string) : bool =
  let etat_fin = delta_etoile a 0 w in
  List.mem etat_fin a.fin
