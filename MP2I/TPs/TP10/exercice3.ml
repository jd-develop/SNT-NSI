#!/usr/bin/env ocaml

(* Décompose la chaîne de caractères s en une liste de caractères, mais
 * uniquement à partir de l’indice i inclus *)
let rec list_of_substring (s: string) (i: int) : char list =
    if i >= String.length s then []
    else (s.[i])::(list_of_substring s (i+1))

(* Décompose la chaîne de caractères s en une liste de caractères *)
let list_of_string (s: string) : char list = list_of_substring s 0

(* Transforme une liste de caractères en string *)
let string_of_list (l: char list) : string =
    String.of_seq (List.to_seq l)

(* Divise la chaîne s en une liste de chaînes selon un caractère de séparation
 * c, à partir de l’indice i avec les caractères lus depuis la dernière
 * occurence stockés dans curr *)
let rec split_from_i (s: string) (sep: char) (i: int) (curr: char list)
    : string list =
    if i >= String.length s then [string_of_list (List.rev curr)]
    else if s.[i] = sep then (string_of_list (List.rev curr))::(split_from_i s sep (i+1) [])
    else split_from_i s sep (i+1) ((s.[i])::curr)

(*
 * Sépare la chaîne s en une liste de chaînes selon un caractère de séparation
 * c
 *)
let split (s: string) (c: char) : string list = split_from_i s c 0 []


let test () =
    assert (list_of_substring "coucou" 1 = list_of_string "oucou");
    assert (list_of_substring "coucou" 5 = ['u']);
    assert (list_of_substring "coucou" 6 = []);
    assert (list_of_string "coucou" = ['c'; 'o'; 'u'; 'c'; 'o'; 'u']);
    assert (list_of_string "a" = ['a']);
    assert (list_of_string "" = []);
    assert (list_of_string "⍼" = ['\226'; '\141'; '\188']); (* ah, OCaml n’est pas Unicode-aware *)

    (* split_on_char *)
    assert (String.split_on_char 'c' "coucou" = [""; "ou"; "ou"]);
    (* split *)
    assert (split "coucou" 'c' = [""; "ou"; "ou"]);
    assert (split "" 'c' = [""]);
    assert (split "toto,tata,tutu" ',' = ["toto"; "tata"; "tutu"]);
    assert (split "Lorem ipsum dolor sit amet" ' ' = ["Lorem"; "ipsum"; "dolor"; "sit"; "amet"]);
    print_endline "Tous les tests de l’exercice 3 ont réussi."

