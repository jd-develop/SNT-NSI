#!/usr/bin/env ocaml

(* Renvoie la somme des éléments de t, ou 0 si t est vide *)
let somme_tableau (t: int array) : int =
  (* Renvoie la somme des éléments de t à partir de l’indice i inclus, ou 0
   * si l’indice est en dehors du tableau *)
  let rec somme_a_partir_de (t: int array) (i: int) : int =
    if i >= Array.length t then 0
    else t.(i) + somme_a_partir_de t (i+1)
  in somme_a_partir_de t 0


(* range n = [|1; 2; …; n|] *)
let range (n: int) : int array =
  let t = Array.make n 0 in
  (* range_a_partir_de n [|a1, a2, a3, …, an|] =
   * [|a1, …, i+1, i+1, …, n |]
   *          ^ à l’indice i *)
  let rec range_a_partir_de (n: int) (t: int array) (i: int) =
    if i >= Array.length t then t
    else begin
      t.(i) <- i+1;
      range_a_partir_de n t (i+1)
    end
  in
  range_a_partir_de n t 0


let test () =
  assert (somme_tableau [||] == 0);
  assert (somme_tableau [|3; 4; 5|] == 12);
  assert (range 0 = [||]);
  assert (range 10 = [|1; 2; 3; 4; 5; 6; 7; 8; 9; 10|])

