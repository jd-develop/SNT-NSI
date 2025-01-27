#!/usr/bin/env ocaml

(* on part du principe que a≠0 *)
let n_roots (a, b, c) =
    let delta = b**2. -. 4.*.a*.c in
    if delta > 0. then 2
    else if delta = 0. then 1
    else 0

let nom_chiffre n =
    if n = 2 then "deux"
    else if n = 3 then "trois"
    else if n = 3 then "quatre"
    else if n = 5 then "cinq"
    else ""

let nom_chiffre_match n = match n with
    | 2 -> "deux"
    | 3 -> "trois"
    | 4 -> "quatre"
    | 5 -> "cinq"
    | _ -> ""

let f x y = match (x-1, y) with
    | (0, 0) -> 0
    | (0, _) -> y+1
    | (z, 0) -> z+100
    | _ -> x*y

(*;;
print_int (f 3 5);; print_newline ();;
print_int (f 1 0);; print_newline ();;
print_int (f 1 3);; print_newline ();;
print_int (f 6 0);; print_newline ();; *)

let g x y = match (x-y, x+y) with
    | 0, _ -> 0
    | _, 0 -> 0
    | 1, z -> z*z + 1
    | -1, z -> z*z + 1
    | z, 1 -> z*z - 1
    | z, -1 -> z*z - 1
    | _ -> x*y

let gabu n = match (n mod 3, n mod 5) with
    | (0, _) -> "ga"
    | (_, 0) -> "bu"
    | _ -> string_of_int n

