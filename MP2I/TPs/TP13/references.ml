#!/usr/bin/env ocaml

(* fait la somme des éléments de l et l’ajoute à la valeur contenue dans r *)
let rec ajout (l: int list) (r: int ref) : unit =
  match l with
  | [] -> ()
  | x::q -> r := !r + x; ajout q r


(* Numérote les éléments de l à partir de l’indice i *)
let rec numeroter_a_partir_de (l: 'a list) (i: int) : (int * 'a) list =
  match l with
  | [] -> []
  | x::q -> (i, x)::(numeroter_a_partir_de q (i+1))

(*
 * Numérote les éléments de l. Par exemple,
 * numeroter ['A'; 'B'; 'C'] renvoie [(0, 'A'); (1, 'B'); (2, 'C')]
 *)
let numeroter_v1 (l: 'a list) : (int * 'a) list =
  numeroter_a_partir_de l 0


(* Idem que numeroter *)
let numeroter (l: 'a list) : (int * 'a) list =
  let i = ref 0 in
  (* Numérote la liste l à partir de la valeur stockée dans i *)
  let rec numeroter_ref (l: 'a list) : (int * 'a) list =
    match l with
    | [] -> []
    | x::q -> let index = !i in i := !i + 1; (index, x)::(numeroter_ref q)
  in
  numeroter_ref l


type 'a arbre = V | N of 'a * 'a arbre * 'a arbre


(* Ajoute sur chaque nœud son numéro dans l’ordre préfixe *)
let num_prefixe (a: 'a arbre) : (int * 'a) arbre =
  let i = ref 0 in
  let rec num_prefixe_ref (a: 'a arbre) : (int * 'a) arbre =
    match a with
    | V -> V
    | N(x, g, d) -> let index = !i in
                    i := !i+1;
                    let g' = num_prefixe_ref g in
                    let d' = num_prefixe_ref d in
                    N((index, x), g', d')
  in
  num_prefixe_ref a


let test() =
  assert (numeroter_v1 ['A'; 'B'; 'C'] = [(0, 'A'); (1, 'B'); (2, 'C')]);
  assert (numeroter ['A'; 'B'; 'C'] = [(0, 'A'); (1, 'B'); (2, 'C')])
