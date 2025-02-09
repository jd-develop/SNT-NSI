
(* Renvoie ture si la liste l est triée dans l’ordre croissant, false sinon *)
let rec est_triee (l: 'a list) : bool = match l with
    | [] -> true
    | x::[] -> true
    | x::y::q -> if x <= y then est_triee (y::q)
                 else false

(*
 * Découpe la liste l en deux listes, la première regroupant tous les éléments 
 * de l ⩽ pivot, la seconde tous les éléments de l > pivot.
 *)
let rec partition (pivot: 'a) (l: 'a list) : 'a list * 'a list =
    match l with
    | [] -> [], []
    | x::q -> let l1, l2 = partition pivot q in
              if x <= pivot then (x::l1), l2
              else l1, (x::l2)

(* Renvoie la concaténation de l1 et l2 *)
let rec concatenation (l1: 'a list) (l2: 'a list) : 'a list = match l1 with
    | [] -> l2
    | x::[] -> x::l2
    | x::q -> x::(concatenation q l2)


(*
 * Renvoie une liste triée dans l’ordre croissant contenant les éléments de l,
 * avec l’algorithme du tri rapide.
 *)
let rec tri_rapide (l: 'a list) : 'a list = match l with
    | [] | _::[] -> l
    | x::q -> let l1, l2 = partition x q in
              let l1t = tri_rapide l1 in
              let l2t = tri_rapide l2 in
              concatenation l1t (x::l2t)

(*
 * Renvoie une liste triée contenant les éléments de l1 et l2. Précondition :
 * l1 et l2 sont triées
 *)
let rec fusion (l1: 'a list) (l2: 'a list) =
    assert (est_triee l1);
    assert (est_triee l2);
    match l1, l2 with
    | _, [] -> l1
    | [], _ -> l2
    | x1::q1, x2::q2 -> if x1 <= x2 then x1::(fusion q1 l2)
                        else x2::(fusion l1 q2)

(*
 * Sépare la liste l en deux parties de tailles égales (à un élément près)
 *)
let rec separe (l: 'a list) : 'a list * 'a list = match l with
    | [] -> [], []
    | x::[] -> [x], []
    | x::y::q -> let l1, l2 = separe q in x::l1, y::l2

(*
 * Renvoie une liste triée dans l’ordre croissant contenant les éléments de l,
 * avec l’algorithme du tri fusion.
 *)
let rec tri_fusion (l: 'a list) : 'a list = match l with
    | [] -> []
    | x::[] -> [x]
    | _::_ -> let l1, l2 = separe l in
              let l1t = tri_fusion l1 in
              let l2t = tri_fusion l2 in
              fusion l1t l2t

let test () : unit =
    assert (est_triee [-14; -14; -7; 0; 1; 1; 2; 8; 9082734]);
    assert (est_triee []);
    assert (est_triee [1]);
    assert (est_triee ["chocolatine"]);
    assert (est_triee [1; 1]);
    assert (est_triee [1; 2]);
    assert (not (est_triee [2; 1]));
    assert (not (est_triee [-14; -15; -7; 0; 1; 1; 2; 8; 9082734]));
    assert (not (est_triee [-14; -15; -7; 0; 2; 1; 2; 8; 9082734]));
    assert (not (est_triee [8; -127; 98; 0; 54; -63]));
    assert (not (est_triee ["lorem"; "ipsum"; "dolor"; "sit"; "amet"]));
    assert (est_triee ["amet"; "dolor"; "ipsum"; "lorem"; "sit"]);

    assert (
        partition 0 [5; 0; 6; -5; 9; -123; 45; 67; 2] =
            ([0; -5; -123], [5; 6; 9; 45; 67; 2])
    );
    assert (
        partition 0 [5; 6; 9; 45; 67; 2] =
            ([], [5; 6; 9; 45; 67; 2])
    );
    assert (
        partition 0 [-5; -9; -123] =
            ([-5; -9; -123], [])
    );
    assert ( partition 0 [] = ([], []));

    assert (concatenation [] [] = []);
    assert (concatenation [1] [] = [1]);
    assert (concatenation [] [1] = [1]);
    assert (concatenation [1] [2] = [1; 2]);
    assert (concatenation [1; 2; 3; 4] [5; 6; 7; 8] = [1; 2; 3; 4; 5; 6; 7; 8]);

    assert (est_triee (tri_rapide []));
    assert (est_triee (tri_rapide [1]));
    assert (est_triee (tri_rapide [1; 2]));
    assert (est_triee (tri_rapide [2; 1]));
    assert (
        est_triee (tri_rapide [5; 6; 0; 6; -5; 9; 5; -123; 45; 0; 67; 2; 2])
    );
    assert (est_triee (tri_rapide ["lorem"; "ipsum"; "dolor"; "sit"; "amet"]));
    assert (est_triee (tri_rapide ["amet"; "dolor"; "ipsum"; "lorem"; "sit"]));

    assert (fusion [] [] = []);
    assert (fusion [1] [] = [1]);
    assert (fusion [] [1] = [1]);
    assert (fusion [1; 3] [] = [1; 3]);
    assert (fusion [] [1; 3] = [1; 3]);
    assert (fusion [1] [2] = [1; 2]);
    assert (fusion [2] [1] = [1; 2]);
    assert (fusion [1; 3] [2] = [1; 2; 3]);
    assert (fusion [2] [1; 3] = [1; 2; 3]);
    assert (fusion [1; 3] [2; 3] = [1; 2; 3; 3]);
    assert (fusion [2; 3] [1; 3] = [1; 2; 3; 3]);
    assert (
        fusion [2; 5; 8; 10; 91; 128] [-1; 10; 60; 81; 100] =
            [-1; 2; 5; 8; 10; 10; 60; 81; 91; 100; 128]
    );
    assert (separe [] = ([], []));
    assert (separe [1] = ([1], []));
    assert (separe [1; 7; 2; 8; 10; 74] = ([1; 2; 10], [7; 8; 74]));
    assert (separe [1; 7; 2; 8; 10; 74; 3] = ([1; 2; 10; 3], [7; 8; 74]));

    assert (est_triee (tri_fusion []));
    assert (est_triee (tri_fusion [1]));
    assert (est_triee (tri_fusion [1; 2]));
    assert (est_triee (tri_fusion [2; 1]));
    assert (
        est_triee (tri_fusion [5; 6; 0; 6; -5; 9; 5; -123; 45; 0; 67; 2; 2])
    );
    assert (est_triee (tri_fusion ["lorem"; "ipsum"; "dolor"; "sit"; "amet"]));
    assert (est_triee (tri_fusion ["amet"; "dolor"; "ipsum"; "lorem"; "sit"]));
    print_endline "Tous les tests de l’exercice 6 ont réussi."
