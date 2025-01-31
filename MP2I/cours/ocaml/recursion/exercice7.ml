#!/usr/bin/env ocaml

(* QUESTION 1 *)

(* Renvoie la longueur de la liste l, plus r *)
let rec longueur_plus (l: 'a list) (r: int) : int = match l with
    | [] -> r
    | x::q -> longueur_plus q (r+1)

(* Renvoie la longueur de la liste l *)
let longueur (l: 'a list) : int = longueur_plus l 0


(* QUESTION 2 *)

(* Renvoie la liste l renversée, suivie des éléments contenus dans l' (dans
 * l’ordre)
 *)
let rec reverse_concat (l: 'a list) (l': 'a list) : 'a list = match l with
    | [] -> l'
    | x::q -> reverse_concat q (x::l')

(* Renvoie la liste l renversée *)
let reverse (l: 'a list) : 'a list = reverse_concat l []

(* QUESTION 3 *)

(* Renvoie la liste contenant les images des éléments de l par f *)
let map (f: 'a -> 'b) (l: 'a list) : 'b list =
    (* Renvoie la liste renversée contenant les images des éléments de l par f,
     * suivie des éléments contenus dans la liste l' *)
    let rec map_concat (l: 'a list) (l': 'b list) : 'b list = match l with
        | [] -> l'
        | x::q -> map_concat q ((f x)::l')
    in
    reverse (map_concat l [])

(* QUESTION 4 *)

(* Calcule le n-ième terme de la suite de Fibonacci (où le terme 0 est 1 et
 * le terme 1 est 1) *)
let fibonacci (n: int) : int =
    (* Calcule les i termes suivants de la suite de Fibonacci, sachant le
     * dernier terme t1 et l’avant-dernier terme t2
     *)
    let rec fibo_suiv (i: int) (t1: int) (t2: int) : int = match i with
        | 0 -> t1
        | _ -> (fibo_suiv (i-1) (t1+t2) t1)
    in
    fibo_suiv n 1 0
