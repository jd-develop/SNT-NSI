#!/usr/bin/env ocaml

(* Renvoie la somme des éléments de t, ou 0 si t est vide *)
let somme_tableau (t: int array) : int =
  let somme = ref 0 in
  for i = 0 to (Array.length t)-1 do
    somme := !somme + t.(i)
  done;
  !somme


(* Renvoie l’indice de l’élément maximum du tableau t entre les indices 0 et
 * j inclus *)
let indice_max (t: 'a array) (j: int) : int =
  let imax = ref 0 in
  for i = 0 to j do
    if t.(i) > t.(!imax) then
      imax := i
  done;
  !imax

(* Trie le tableau t dans l’ordre croissant par sélection *)
let selection_sort (t: 'a array) : 'a array =
  let n = Array.length t in
  for i = 0 to n-1 do
    let imax = indice_max t (n-i-1) in
    let emax = t.(imax) in
    t.(imax) <- t.(n-i-1);
    t.(n-i-1) <- emax;
  done;
  t

(* Trie le tableau t dans l’ordre croissant par insertion *)
let insertion_sort (t: 'a array) : 'a array =
  let n = Array.length t in
  for i = 0 to n-1 do
    let j = ref i in
    while !j > 0 && t.(!j-1) > t.(!j) do
      let c = t.(!j) in
      t.(!j) <- t.(!j-1);
      t.(!j-1) <- c;
      j := !j-1
    done;
  done;
  t


(* Renvoie un tableau contenant les éléments de l *)
let list_to_array (l: 'a list) : 'a array =
  (* Ajoute les éléments de l à partir de l’indice i du tableau t *)
  let rec list_to_array_a_partir_de (l: 'a list) (t: 'a array) (i: int) : 'a array =
    match l with
    | [] -> t
    | x::q -> t.(i) <- x; (list_to_array_a_partir_de q t (i+1))
  in
  match l with
  | [] -> [||]
  | x::_ ->
    begin
      let n = List.length l in
      let t = Array.make n x in
      list_to_array_a_partir_de l t 0
    end


(* Renvoie une liste contenant les éléments de t *)
let array_to_list (t: 'a array) : 'a list =
  let l = ref [] in
  for i = Array.length t - 1 downto 0 do
    l := (t.(i))::(!l)
  done;
  !l


let test () =
  assert (somme_tableau [||] == 0);
  assert (somme_tableau [|3; 4; 5|] == 12);
  assert (selection_sort [|4; 7; 2; 9; 1; 90; -1|] = [|-1; 1; 2; 4; 7; 9; 90|]);
  assert (selection_sort [||] = [||]);
  assert (insertion_sort [|4; 7; 2; 9; 1; 90; -1|] = [|-1; 1; 2; 4; 7; 9; 90|]);
  assert (insertion_sort [||] = [||]);
  assert (list_to_array [] = [||]);
  assert (list_to_array [3; 4; 5; 8; 1] = [|3; 4; 5; 8; 1|]);
  assert (list_to_array ["chocolatine"; "MP2 tous des dieux"] = [|"chocolatine"; "MP2 tous des dieux"|]);
  assert (array_to_list [|3; 4; 5; 8; 1|] = [3; 4; 5; 8; 1]);
  assert (array_to_list [|"chocolatine"; "MP2 tous des dieux"|] = ["chocolatine"; "MP2 tous des dieux"])
