#!/usr/bin/env ocaml

(* renvoie la somme des éléments de `liste` *)
let rec somme (l: int list) : int = match l with
    | [] -> 0
    | e :: q -> e + somme q

(* Renvoie true si l’élément `x` est contenu dans `liste` *)
let rec recherche (l: 'a list) (x: 'a) : bool = match l with
    | [] -> false
    | a :: q -> a = x || recherche q x

(* Concatène les listes l1 et l2 *)
let rec concatener (l1: 'a list) (l2: 'a list) : 'a list = match l1 with
    | [] -> l2
    | x::q -> x::(concatener q l2)

(* Renvoie la concaténation de toutes les listes contenues dans l *)
let rec multi_concat (l: 'a list list) : 'a list = match l with
    | [] -> []
    | x::q -> concatener x (multi_concat q)

(*
 * Renvoie une liste contenant comme éléments le résultat de chaque élément de
 * l par f
 *)
let rec map (f: 'a -> 'b) (l: 'a list) : 'b list = match l with
    | [] -> []
    | x::q -> (f x)::(map f q)

(*
 * Renverse l1 dans l2, et renvoie le résultat.
 * Exemple : rev_concat [1; 2; 3] [4; 5; 6] = [3; 2; 1; 4; 5; 6]
 *)
let rec rev_concat (l1: 'a list) (l2: 'a list) : 'a list = match l1 with
    | [] -> l2
    | x::q -> rev_concat q (x::l2)

(*
 * Renverse l’ordre de la liste l, et renvoie le résultat.
 *)
let rev (l: 'a list) : 'a list = rev_concat l []


(*
 * Ajoute tous les entiers entre i et n-1 inclus au début de la liste
 * l et renvoie le résultat
 *)
let rec add_to_start_of_list (l: int list) (i: int) (n: int) : int list =
    if i = n then l
    else i::(add_to_start_of_list l (i+1) n)

(*
 * Renvoie la liste contenant tous les entiers entre 0 inclus et n-1 inclus
 *)
let range (n: int) : int list = add_to_start_of_list [] 0 n


let test () =
    assert (somme [] = 0);
    assert (somme [1] = 1);
    assert (somme [1; 2] = 3);
    assert (somme [1; 2; 1234567] = 1234570);
    assert (recherche [2] 2);
    assert (recherche [1; 2] 2);
    assert (not (recherche [1; 3] 2));
    assert (not (recherche [] 2));
    assert (not (recherche [] "coucou"));
    assert (recherche ["coucou"; "bonjour"] "coucou");
    assert (not (recherche ["hello"; "bonjour"] "coucou"));
    assert (concatener [1; 2; 3] [4; 5; 6] = [1; 2; 3; 4; 5; 6]);
    assert (concatener [1; 2; 3] [] = [1; 2; 3]);
    assert (concatener [] [1; 2; 3] = [1; 2; 3]);
    assert (concatener [] [] = []);
    assert (multi_concat [] = []);
    assert (multi_concat [[]] = []);
    assert (multi_concat [[]; []] = []);
    assert (multi_concat [[1;2;3]; [4;5]; [6]] = [1; 2; 3; 4; 5; 6]);
    assert (multi_concat [[]; [1;2]; []; [3;4]; [5]; [6]; []] =
                [1; 2; 3; 4; 5; 6]);
    assert (map (fun x -> x*x) [2; 3; 4] = [4; 9; 16]);
    assert (map (fun x -> x*x) [] = []);
    assert (multi_concat (map (multi_concat) [[[1]; [2; 3]]; []; [[4; 5]; []; [6]]]) = [1; 2; 3; 4; 5; 6]);
    assert (rev_concat [1; 2; 3] [4; 5; 6] = [3; 2; 1; 4; 5; 6]);
    assert (rev_concat [] [4; 5; 6] = [4; 5; 6]);
    assert (rev_concat [1; 2; 3] [] = [3; 2; 1]);
    assert (rev [1; 2; 3] = [3; 2; 1]);
    assert (add_to_start_of_list [4; 1] 3 10 = [3; 4; 5; 6; 7; 8; 9; 4; 1]);
    assert (range 10 = [0; 1; 2; 3; 4; 5; 6; 7; 8; 9]);
    assert (range 0 = []);
    print_endline "Tous les tests de l’exercice 1 ont réussi."
