#!/usr/bin/env ocaml

let rec selection l = match l with
    | [] -> failwith "Liste vide"
    | x::[] -> (x, [])
    | x::q ->
        let (m, q') = selection q in
            if x < m then (x, m::q')
            else (m, x::q')

let rec selection_sort l = match l with
    | [] -> []
    | x::q -> let (m, q') = selection l in m::(selection_sort q')


(*
 * Sépare l en deux listes : la première avec les éléments de l strictement
 * inféreurs au pivot, la deuxième avec les éléments de l supérieurs ou égaux
 * au pivot
 *)
let rec separer l pivot = match l with
    | [] -> ([], [])
    | x::q -> let linf, lsup = (separer q pivot) in if x < pivot then (x::linf, lsup) else (linf, x::lsup)

(*
 * Tri rapide : on choisit un pivot (par ex. le premier élément), on construit
 * deux listes contenant pour la première les éléments < au pivot et pour
 * la deuxième les éléments ⩾ au pivot, puis on les trie récursivement et
 * on concatène
 *)
let rec quicksort l = match l with
    | [] -> []
    | x::[] -> x::[]
    | x::q -> let (linf, lsup) = separer q x in (quicksort linf)@(x::(quicksort lsup))
