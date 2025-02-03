#!/usr/bin/env ocaml

(* Sépare la liste l en deux listes de tailles égales (à un près) *)
let rec separer (l: 'a list) : 'a list * 'a list = match l with
    | [] -> [], []
    | x::[] -> x::[], []
    | x::y::q -> let (l1, l2) = separer q in x::l1, y::l2

(* Fusionne les deux listes l1 et l2 triées en une seule liste triée *)
let rec fusion (l1: 'a list) (l2: 'a list) : 'a list = match (l1, l2) with
    | [], _ -> l2
    | _, [] -> l1
    | x1::q1, x2::q2 -> if x1 <= x2 then x1::(fusion q1 l2)
                        else x2::(fusion l1 q2)

(* Trie la liste l dans l’ordre crossant, grâce à l’algo de tri fusion *)
let rec merge_sort (l: 'a list) : 'a list = match l with
    | [] -> []
    | x::[] -> x::[]
    | _ -> let (l1, l2) = separer l in fusion (merge_sort l1) (merge_sort l2)

