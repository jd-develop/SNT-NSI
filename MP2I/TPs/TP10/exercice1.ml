#!/usr/bin/env ocaml

(* renvoie la somme des éléments de `liste` *)
let rec somme (l: int list) : int = match l with
    | [] -> 0
    | e :: q -> e + somme q


(* Renvoie true si l’élément `x` est contenu dans `liste` *)
let rec contient (x: 'a) (l: 'a list) : bool = match l with
    | [] -> false
    | a :: q -> a = x || contient x q


let test () =
    assert (somme [] = 0);
    assert (somme [1] = 1);
    assert (somme [1; 2] = 3);
    assert (somme [1; 2; 1234567] = 1234570);
    assert (contient 2 [2]);
    assert (contient 2 [1; 2]);
    assert (not (contient 2 [1; 3]));
    assert (not (contient 2 []));
    assert (not (contient "coucou" []));
    assert (contient "coucou" ["coucou"; "bonjour"]);
    assert (not (contient "coucou" ["hello"; "bonjour"]));
    print_endline "Tous les tests ont réussi"
