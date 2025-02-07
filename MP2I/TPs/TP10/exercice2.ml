(*
 * Renvoie la concaténation de toutes les chaînes de caractères contenues dans
 * l.
 *)
let rec string_cat (l: string list) : string = match l with
    | [] -> ""
    | x::q -> x^(string_cat q)

(*
 * « concatène » la liste l avec comme fonction de concaténation f, avec
 * b comme élément représentant une liste vide (par exemple "" dans le cas
 * d’une concaténation de chaînes de caractères)
 *)
let rec fold (f: 'a -> 'b -> 'c) (l: 'a list) (b: 'b) : 'b = match l with
    | [] -> b
    | x::q -> f x (fold f q b)

(* Renvoie le nombre d’éléments de la liste l *)
let taille (l: 'a list) : int = fold (fun x y -> 1+y) l 0

(* renvoie la somme des éléments de `liste` *)
let somme (l: int list) : int = fold (+) l 0

(* Renvoie true si l’élément `a` est contenu dans `liste` *)
let recherche (l: 'a list) (a: 'a) : bool = fold (fun x y -> (x=a) || y) l false

(* Concatène les listes l1 et l2 *)
let concatener (l1: 'a list) (l2: 'a list) : 'a list =
    fold (fun x y -> x::y) l1 l2

(* Renvoie la concaténation de toutes les listes contenues dans l *)
let multi_concat (l: 'a list list) : 'a list = fold concatener l []

(*
 * Renvoie une liste contenant comme éléments le résultat de chaque élément de
 * l par f
 *)
(* Version sans fold écrite dans l’exo 1 *)
let map (f: 'a -> 'b) (l: 'a list) : 'b list = fold (fun x y -> (f x)::y) l []

(*
 * Renvoie une liste contenant tous les éléments de l dont le résultat par f
 * est true
 *)
let rec filter (l: 'a list) (f: 'a -> bool) : 'a list = match l with
    | [] -> []
    | x::q -> if f x then x::(filter q f) else filter q f

(* Version avec fold de filter *)
let filter_fold (l: 'a list) (f: 'a -> bool) : 'a list =
    fold (fun x y -> if f x then x::y else y) l []

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

(* Renvoie la somme des carrés des diviseurs de n (n non nul) *)
let sum_div (n: int) : int = assert (n != 0);
    let divise_n (x: int) = x != 0 && n mod x = 0 in
    let liste_diviseurs = filter (range (n+1)) divise_n in
    let liste_carres = map (fun x -> x*x) liste_diviseurs in
    fold (+) liste_carres 0

let test () =
    assert (taille [] = 0);
    assert (taille [1] = 1);
    assert (taille ["coucou"; "bonjour"] = 2);
    assert (taille (multi_concat [[2; 5; 8]; []; [9; 1; 2]]) = 6);
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
    assert (string_cat ["lorem "; "ipsum "; "dolor "; "sit "; "amet"] =
        "lorem ipsum dolor sit amet");
    assert (string_cat ["bonjour"] = "bonjour");
    assert (string_cat [""] = "");
    assert (string_cat [] = "");
    assert (string_cat (multi_concat [
        ["lorem "; "ipsum"];
        [" "];
        [];
        ["dolor sit "];
        ["amet"; ""];
        [""];
        []
    ]) = "lorem ipsum dolor sit amet");

    assert (fold (fun x y -> x^y) ["Vive"; " "; "OCaml"; " "; "!"] "" = "Vive OCaml !");
    assert (fold (^) ["Vive"; " "; "OCaml"; " "; "!"] "" = "Vive OCaml !");
    assert (fold (+) [1; 2; 3; 4] 0 = 10);
    assert (fold (fun x l -> x::l) [1; 2; 3; 4] [] = [1; 2; 3; 4]);

    assert (map (fun x -> x*x) [2; 3; 4] = [4; 9; 16]);
    assert (map (fun x -> x*x) [] = []);
    assert (multi_concat (map (multi_concat) [[[1]; [2; 3]]; []; [[4; 5]; []; [6]]]) = [1; 2; 3; 4; 5; 6]);

    assert (filter [1;2;3;4;2;3;4] (fun x -> x mod 2 = 0) = [2; 4; 2; 4]);
    assert (filter [] (fun x -> x mod 2 = 0) = []);
    assert (filter_fold [1;2;3;4;2;3;4] (fun x -> x mod 2 = 0) = [2; 4; 2; 4]);
    assert (filter_fold [] (fun x -> x mod 2 = 0) = []);
    assert (sum_div 1 == 1);
    assert (sum_div 2 == 5);
    assert (sum_div 3 == 10);
    assert (sum_div 4 == 21);
    assert (sum_div 5 == 26);
    assert (sum_div 6 == 1+4+9+36);
    assert (sum_div 7 == 50);
    assert (sum_div 8 == 0b1010101); (* 0b1² + 0b10² + 0b100² + 0b1000² *)
    assert (sum_div 9 == 91);
    assert (sum_div 10 == 130);
    print_endline "Tous les tests de l’exercice 2 ont réussi."
