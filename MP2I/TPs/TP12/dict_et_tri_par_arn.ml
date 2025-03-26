#!/usr/bin/env ocaml

type couleur = Rouge | Noir

type ('k, 'v) noeud_arn =
  | Feuille of 'k * 'v  (* clef, valeur *)
  | N of couleur * 'k * ('k, 'v) noeud_arn * ('k, 'v) noeud_arn

type ('k, 'v) dico = ('k, 'v) noeud_arn option


(* Renvoie un dictionnaire vide *)
let empty () : ('k, 'v) dico = None


(* Corrige l’arbre a après une insertion, d’après les 4 cas possibles. En
 * sortie : un arbre rouge-noir relaxé de même hauteur noire. *)
let correctionARN (a: ('k, 'v) noeud_arn) : ('k, 'v) noeud_arn =
  match a with
  | N(Noir, z, N(Rouge, y, N(Rouge, x, a, b), c), d)
  | N(Noir, z, N(Rouge, x, a, N(Rouge, y, b, c)), d)
  | N(Noir, x, a, N(Rouge, z, N(Rouge, y, b, c), d))
  | N(Noir, x, a, N(Rouge, y, b, N(Rouge, z, c, d)))
    -> N(Rouge, y, N(Noir, x, a, b), N(Noir, z, c, d))
  | _ -> a


(* Ajoute l’association (k, v) à d, et renvoie le résultat sous forme
 * d’arbre rouge-noir relaxé. Remplace l’ancienne valeur *)
let rec insertionARNrelax (k: 'k) (v: 'v) (d: ('k, 'v) noeud_arn) : ('k, 'v) noeud_arn =
  match d with
  | Feuille (kf, vf) when k = kf -> Feuille (k, v)
  | Feuille (kf, vf) when k < kf -> N(Rouge, k, Feuille (k, v), Feuille (kf, vf))
  | Feuille (kf, vf) when k > kf -> N(Rouge, kf, Feuille (kf, vf), Feuille (k, v))
  | N(c, x, g, d) when k <= x -> correctionARN (N(c, x, insertionARNrelax k v g, d))
  | N(c, x, g, d) when k > x -> correctionARN (N(c, x, g, insertionARNrelax k v d))
  | _ -> d


(* set d k v ajoute l’association (k, v) à d. Remplace l’ancienne valeur *)
let set (d: ('k, 'v) dico) (k: 'k) (v: 'v) : ('k, 'v) dico = match d with
  | None -> Some(Feuille(k, v))
  | Some(a) -> begin match (insertionARNrelax k v a) with
    | Feuille (k, v) -> Some(Feuille(k, v))
    | N(_, x, g, d) -> Some(N(Noir, x, g, d))
    end


(* Renvoie le dictionnaire construit durant le test pour pouvoir être utilisé
 * pour d’autres tests *)
let test_set () : (int, int) dico =
  let d = empty () in
  let d = set d 20 1 in
  let d = set d 17 2 in
  let d = set d 22 3 in
  let d = set d 9 4 in
  let d = set d 3 5 in
  let d = set d 25 6 in
  let d = set d 15 7 in
  let d = set d 30 8 in
  let d = set d 17 9 in
  let d = set d 23 10 in
  let d = set d 8 11 in
  let d = set d 6 12 in
  let d = set d 24 13 in
  assert (d = Some (
    N (Noir, 20,
     N (Noir, 9,
      N (Rouge, 6,
       N (Noir, 3, Feuille (3, 5), Feuille (6, 12)),
       N (Noir, 8, Feuille (8, 11), Feuille (9, 4))),
      N (Noir, 17, N (Rouge, 15, Feuille (15, 7), Feuille (17, 9)), Feuille (20, 1))),
     N (Noir, 23, N (Noir, 22, Feuille (22, 3), Feuille (23, 10)),
      N (Noir, 25, N (Rouge, 24, Feuille (24, 13), Feuille (25, 6)), Feuille (30, 8))))));
  d


(* get_arn d k renvoie la valeur v associée à k dans d, ou None si k n’est pas
 * dans d *)
let rec get_arn (a: ('k, 'v) noeud_arn) (k: 'k) : 'v option = match a with
  | Feuille (kf, vf) when kf = k -> Some(vf)
  | Feuille (kf, vf) -> None
  | N (_, kn, g, d) when k <= kn -> get_arn g k
  | N (_, kn, g, d) -> get_arn d k


(* get d k renvoie la valeur v associée à k dans d, ou None si k n’est pas dans
 * d *)
let get (d: ('k, 'v) dico) (k: 'k) : 'v option = match d with
  | None -> None
  | Some(a) -> get_arn a k


(* d est le dictionnaire construit lors de test_set *)
let test_get (d: (int, int) dico) =
  assert (get d 17 = Some(9));
  assert (get d 20 = Some(1));
  assert (get d 30 = Some(8));
  assert (get d 24 = Some(13));
  assert (get d 0 = None);
  assert (get d 100 = None);
  assert (get None 100 = None)


(* Renconstruit une liste triée à partir d’un noeud_arn d’occurences *)
let lister_arn (a: ('a, int) noeud_arn) : 'a list =
  (* Idem, et concatène la liste obtenue avec l *)
  let rec lister_arn_concat (a': ('a, int) noeud_arn) (l: 'a list) : 'a list =
    match a' with
    | Feuille (valeur, 0) -> l
    | Feuille (valeur, occurences) -> (lister_arn_concat (Feuille(valeur, occurences-1)) (valeur::l))
    | N (_, _, g, d) -> lister_arn_concat g (lister_arn_concat d l)
  in lister_arn_concat a []


(* Reconstruit une liste triée à partir d’un arbre d’occurences *)
let lister (d: ('a, int) dico) : 'a list = match d with
  | None -> []
  | Some(a) -> lister_arn a
(* Le test de lister est dans la fonction de tests principale *)


(* Renvoie l’arbre d’occurences associée à la liste l *)
let arbrifier (l: 'a list) : ('a, int) dico =
  (* Idem, mais ajoute les éléments le la liste à l’arbre d *)
  let rec arbrifier_concat (l: 'a list) (d: ('a, int) dico) : ('a, int) dico =
    match l with
    | [] -> d
    | x::q -> let n = match (get d x) with | None -> 0 | Some(n) -> n in
              arbrifier_concat q (set d x (n+1))
  in
  arbrifier_concat l (empty ())


let test_arbrifier () =
  assert (arbrifier [] = None);
  assert (arbrifier [1] = Some(Feuille(1, 1)));
  assert (arbrifier [1; 1] = Some(Feuille(1, 2)));
  assert (arbrifier [1; 2] = Some(N(Noir, 1, Feuille(1, 1), Feuille(2, 1))));
  assert (arbrifier [1; 2; 1] = Some(N(Noir, 1, Feuille(1, 2), Feuille(2, 1))));
  assert (arbrifier [1; 2; 2] = Some(N(Noir, 1, Feuille(1, 1), Feuille(2, 2))));
  assert (arbrifier [1; 2; 2; 1] = Some(N(Noir, 1, Feuille(1, 2), Feuille(2, 2))));
  assert (arbrifier [1; 2; 3; 1] = Some(N(Noir, 1, Feuille(1, 2), N(Rouge, 2, Feuille(2, 1), Feuille(3, 1)))));
  assert (arbrifier [1; 2; 3; 3] = Some(N(Noir, 1, Feuille(1, 1), N(Rouge, 2, Feuille(2, 1), Feuille(3, 2)))));
  assert (arbrifier [1; 2; 3; 2] = Some(N(Noir, 1, Feuille(1, 1), N(Rouge, 2, Feuille(2, 2), Feuille(3, 1)))));
  assert (arbrifier [1; 2; 3; 1; 2; 3; 3; 2; 1] = Some(N(Noir, 1, Feuille(1, 3), N(Rouge, 2, Feuille(2, 3), Feuille(3, 3)))))


let tri_arn (l: 'a list) : 'a list =
  let arbre = arbrifier l in
  lister arbre


let test_tri_arn () =
  assert (tri_arn [] = []);
  assert (tri_arn [1] = [1]);
  assert (tri_arn [9; 9; -5; 6; -2; 1; 1; -4; 4; 5] = [-5; -4; -2; 1; 1; 4; 5; 6; 9; 9]);
  assert (tri_arn ["bonjour"; "guten Tag"; "hej"; "adieusiatz"; "goedendag"] = ["adieusiatz"; "bonjour"; "goedendag"; "guten Tag"; "hej"])


(* Renvoie la clef minimale de l’ARN d *)
let rec clef_minimale_arn (d: ('k, 'v) noeud_arn) : 'k = match d with
  | Feuille (k, _) -> k
  | N (_, _, g, _) -> clef_minimale_arn g

(* Renvoie la clef minimale du dictionnaire d (None si le dictionnaire est
 * vide) *)
let clef_minimale (d: ('k, 'v) dico) : 'k option = match d with
  | None -> None
  | Some(a) -> Some(clef_minimale_arn a)


(* d est le dictionnaire construit dans `test_set` *)
let test_clef_minimale (d: (int, int) dico) =
  assert (clef_minimale d = Some(3));
  assert (clef_minimale None = None);
  assert (clef_minimale (Some(Feuille(1, 3))) = Some(1));
  assert (clef_minimale (Some(N(Noir, 4, Feuille(0, 5), Feuille(8, 12)))) = Some(0))

(* Renvoie la liste des clés de d comrises entre a et b *)
let query_range_arn (a: 'k) (b: 'k) (d: ('k, 'v) noeud_arn) : 'k list =
  (* Idem, et concatène la liste obtenue avec l *)
  let rec query_range_concat (a: 'k) (b: 'k) (d: ('k, 'v) noeud_arn) (l: 'k list) : 'k list =
    match d with
    | Feuille (k, _) when k < a || k > b -> l
    | Feuille (k, _) -> k::l
    | N(_, kn, g, d) when kn < a -> query_range_concat a b d l
    | N(_, kn, g, d) when kn >= b -> query_range_concat a b g l
    | N(_, kn, g, d) -> query_range_concat a b g (query_range_concat a b d l)
  in
  query_range_concat a b d []

(* Renvoie la liste des clés de d comrises entre a et b *)
let query_range (a: 'k) (b: 'k) (d: ('k, 'v) dico) : 'k list = match d with
  | None -> []
  | Some(t) -> query_range_arn a b t


(* d est le dictionnaire construit dans `test_set` *)
let test_query_range (d: (int, int) dico) =
  assert (query_range 0 3 None = []);
  assert (query_range 0 3 (Some(Feuille(0, 3))) = [0]);
  assert (query_range 0 3 (Some(Feuille(1, 3))) = [1]);
  assert (query_range 0 3 (Some(Feuille(3, 3))) = [3]);
  assert (query_range 0 3 (Some(Feuille(5, 3))) = []);
  assert (query_range 0 3 (Some(Feuille(-10, 3))) = []);
  assert (query_range 0 3 (Some(N(Noir, 3, Feuille(-10, 3), Feuille(4, 2)))) = []);
  assert (query_range (-10) 3 (Some(N(Noir, 3, Feuille(-10, 3), Feuille(4, 2)))) = [-10]);
  assert (query_range 0 5 (Some(N(Noir, 3, Feuille(-10, 3), Feuille(4, 2)))) = [4]);
  assert (query_range 10 20 d = [15; 17; 20]);
  assert (query_range 0 10 d = [3; 6; 8; 9]);
  assert (query_range 20 30 d = [20; 22; 23; 24; 25; 30]);
  assert (query_range (-10) 40 d = [3; 6; 8; 9; 15; 17; 20; 22; 23; 24; 25; 30]);
  assert (query_range (-10) 0 d = []);
  assert (query_range 30 40 d = [30]);
  assert (query_range 31 40 d = [])


let test () =
  let d = test_set () in
  test_get d;
  assert (lister d = [3; 3; 3; 3; 3; 6; 6; 6; 6; 6; 6; 6; 6; 6; 6; 6; 6; 8; 8; 8; 8; 8; 8; 8; 8; 8; 8; 8; 9; 9; 9; 9; 15; 15; 15; 15; 15; 15; 15; 17; 17; 17; 17; 17; 17; 17; 17; 17; 20; 22; 22; 22; 23; 23; 23; 23; 23; 23; 23; 23; 23; 23; 24; 24; 24; 24; 24; 24; 24; 24; 24; 24; 24; 24; 24; 25; 25; 25; 25; 25; 25; 30; 30; 30; 30; 30; 30; 30; 30]);
  test_arbrifier ();
  test_tri_arn ();
  test_clef_minimale d;
  test_query_range d

